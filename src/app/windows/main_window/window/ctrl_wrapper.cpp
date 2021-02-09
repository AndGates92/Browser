/**
 * @copyright
 * @file ctrl_wrapper.cpp
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>
#include <QtWidgets/QShortcut>

#include "app/utility/logger/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/windows/main_window/window/commands.h"
#include "app/windows/main_window/window/ctrl_wrapper.h"
#include "app/windows/main_window/window/ctrl.h"
#include "app/windows/main_window/window/ctrl_tab.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/windows/main_window/tabs/tab_widget.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/widgets/text/line_edit.h"
#include "app/shared/exception.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlWrapperOverall, mainWindowCtrlWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlWrapperUserInput, mainWindowCtrlWrapper.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::CtrlWrapper::CtrlWrapper(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : QWidget(parent), app::main_window::window::Base(core), winctrl(new app::main_window::window::Ctrl(this, core)), tabctrl(new app::main_window::window::CtrlTab(this, core)), savedData({app::main_window::state_e::IDLE, QString()}) {
	// Connect signals and slots
	this->connectSignals();

}

app::main_window::window::CtrlWrapper::~CtrlWrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Main window control wrapper destructor");
}

void app::main_window::window::CtrlWrapper::keyPressEvent(QKeyEvent * event) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperUserInput, "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyPressEvent(event);
	this->tabctrl->keyPressEvent(event);

	this->core->mainWidget->repaint();

}

void app::main_window::window::CtrlWrapper::connectSignals() {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Connect signals");

	// Window state change
	connect(this->winctrl.get(), &app::main_window::window::Ctrl::windowStateChangeRequested, this, &app::main_window::window::CtrlWrapper::changeWindowState);
	connect(this->tabctrl.get(), &app::main_window::window::CtrlTab::windowStateChangeRequested, this, &app::main_window::window::CtrlWrapper::changeWindowState);

	// Controller state save and restore
	connect(this->winctrl.get(), &app::main_window::window::Ctrl::saveCurrentState, this, &app::main_window::window::CtrlWrapper::saveData);
	connect(this->tabctrl.get(), &app::main_window::window::CtrlTab::saveCurrentState, this, &app::main_window::window::CtrlWrapper::saveData);
	connect(this->winctrl.get(), &app::main_window::window::Ctrl::restoreSavedState, this, &app::main_window::window::CtrlWrapper::restoreSavedData);
	connect(this->tabctrl.get(), &app::main_window::window::CtrlTab::restoreSavedState, this, &app::main_window::window::CtrlWrapper::restoreSavedData);

	std::unique_ptr<app::main_window::statusbar::Bar> & statusBar = this->core->bottomStatusBar;
	connect(statusBar.get(), &app::main_window::statusbar::Bar::childFocusIn, this, [this] () {
		this->setAllShortcutEnabledProperty(false);
	});

	connect(statusBar->getUserInput().get(), &app::text_widgets::LineEdit::textChanged, this, &app::main_window::window::CtrlWrapper::setCommandLineArgument);
	connect(statusBar->getUserInput().get(), &app::text_widgets::LineEdit::returnPressed, this, [this] () {
		const app::main_window::state_e windowState = this->core->getMainWindowState();
		this->executeAction(windowState);
	});
	connect(statusBar->getUserInput().get(), &app::text_widgets::LineEdit::escapeReleased, this, [this] () {
		this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::SETUP);
	});
	connect(statusBar->getUserInput().get(), &app::text_widgets::LineEdit::lostFocus, this, [this] (const Qt::FocusReason & reason) {
		if (reason == Qt::ActiveWindowFocusReason) {
			this->saveData();
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::SETUP);
		}
	});
	connect(statusBar->getUserInput().get(), &app::text_widgets::LineEdit::gotFocus, this, [this] (const Qt::FocusReason & reason) {
		if (reason == Qt::ActiveWindowFocusReason) {
			const app::main_window::state_e windowState = this->core->getMainWindowState();
			if (windowState == app::main_window::state_e::IDLE) {
				this->restoreSavedData();
			}
		}
	});

	const app::main_window::window::Commands::action_data_t & commands = this->core->commands->getActions();
	std::for_each(commands.cbegin(), commands.cend(), [&] (const auto & data) {
		const std::unique_ptr<app::main_window::json::Data> & commandData = data.second;
		QShortcut * shortcut = new QShortcut(commandData->getShortcut(), this->window());
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Connecting shortcut for key " << (commandData->getShortcut()) << " to trigger a change of controller state to " << commandData->getState());
		QMetaObject::Connection connection = connect(shortcut, &QShortcut::activated,
			[&] () {
				this->changeWindowStateWrapper(commandData, app::main_window::state_postprocessing_e::POSTPROCESS);
			}
		);

		EXCEPTION_ACTION_COND((static_cast<bool>(connection) == false), throw, "Unable to connect shortcut for key " << (commandData->getShortcut()) << " to trigger a change of controller state to " << commandData->getState());

	});

}

void app::main_window::window::CtrlWrapper::setCommandLineArgument(const QString & text) {
	const std::unique_ptr<app::main_window::statusbar::Bar> & statusBar = this->core->bottomStatusBar;
	statusBar->showUserInput(text.isEmpty() == false);

	if (text.isEmpty() == true) {
		this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::SETUP);
	} else {
		app::main_window::state_e windowState = this->core->getMainWindowState();

		if (windowState == app::main_window::state_e::IDLE) {
			EXCEPTION_ACTION_COND((text.isEmpty() == false), throw, "Command line should be empty. It is displaying the following string instead \"" << text << "\"");
		} else {
			auto printedCommandName = this->core->getActionName();
			auto textCopy(text);

			QString userTypedText = this->core->getUserText();
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperUserInput, "User typed text \"" << userTypedText << "\" in state " << windowState);
			if (textCopy.contains(printedCommandName, Qt::CaseSensitive) == false) {
				if (userTypedText.isEmpty() == true) {
					if (windowState != app::main_window::state_e::COMMAND) {
						if (windowState == app::main_window::state_e::MOVE_TAB) {
							// If in state TAB MOVE and the core->userText is empty after deleting the last character, set the move value to IDLE
							this->core->setOffsetType(app::shared::offset_type_e::IDLE);
						}
						this->moveToCommandStateFromNonIdleState(windowState);
					}
				} else {
					EXCEPTION_ACTION(throw, "Command line \"" << text << "\" must contains the command name \"" << printedCommandName << "\" because main window is in state " << windowState << " and command line argument is " << userTypedText);
				}
			} else if (windowState == app::main_window::state_e::COMMAND) {
				this->executeCommand(app::main_window::state_postprocessing_e::SETUP);
			}

			// Command line or state may have changed
			windowState = this->core->getMainWindowState();
			printedCommandName = this->core->getActionName();
			textCopy = statusBar->getUserInputText();

			// indexOf finds the position of the first character of the searched string
			const auto commandNameStart = textCopy.indexOf(printedCommandName, 0, Qt::CaseSensitive);
			EXCEPTION_ACTION_COND((commandNameStart == -1), throw, "Unable to find the command name \"" << printedCommandName << "\" in the command line \"" << text << "\" while in state " << windowState);
			// In order to find where the string ends, its length must be added
			const auto commandNameEnd = commandNameStart + printedCommandName.size();
			if (commandNameEnd < textCopy.size()) {
				const auto & commandNameEndCharacter = textCopy.at(commandNameEnd);
				// An additional character has to be skipped as it is the space between the command and its argument
				const auto argumentStart = commandNameEnd + (commandNameEndCharacter.isSpace() ? 1 : 0);
				const auto argument = textCopy.right(textCopy.size() - argumentStart);
				if (windowState != app::main_window::state_e::COMMAND) {
					EXCEPTION_ACTION_COND((commandNameEndCharacter.isSpace() == false), throw, "It is expected that the character between the command " << textCopy.left(commandNameEnd) << " and the argument " << argument << " in the text " << textCopy << " is a space. Found " << commandNameEndCharacter.toLatin1() << " instead.");
				}
				LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Full command " << textCopy << " argument " << argument);
				this->core->updateUserInput(app::main_window::text_action_e::SET, argument);
			}
		}
	}
}

void app::main_window::window::CtrlWrapper::moveToCommandStateFromNonIdleState(const app::main_window::state_e & windowState) {
	// Saving long command for a given state to set it after changing state
	app::main_window::state_e requestedWindowState = app::main_window::state_e::IDLE;
	const std::unique_ptr<app::main_window::json::Data> & data = this->core->commands->findDataWithFieldValue("State", &windowState);
	if (data != this->core->commands->getInvalidData()) {
		QString longCmd(QString::fromStdString(data->getLongCmd()));

		const auto printedCommandName = this->core->getActionName();

		const std::unique_ptr<app::main_window::statusbar::Bar> & statusBar = this->core->bottomStatusBar;
		const auto & fullCmdLine = statusBar->getUserInputText();
		// Delete last character because the command name is not fully printed in the command line
		const bool deleteLastChar = (fullCmdLine.contains(printedCommandName, Qt::CaseSensitive) == false);
		if (deleteLastChar == true) {
			longCmd.chop(1);
		}
		requestedWindowState = app::main_window::state_e::COMMAND;
		// Setting the user input here because it is cleared when changing state
		this->core->updateUserInput(app::main_window::text_action_e::SET, longCmd);
	} else {
		this->core->updateUserInput(app::main_window::text_action_e::CLEAR);
	}
	this->changeWindowState(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS);
	this->core->printUserInput(app::main_window::text_action_e::NO_CHANGE);
}

void app::main_window::window::CtrlWrapper::executeCommand(const app::main_window::state_postprocessing_e & postprocess) {
	const QString & userCommand = this->core->getUserText();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperUserInput, "Looking for command matching user input: " << userCommand);
	const app::main_window::state_e previousWindowState = this->core->getMainWindowState();
	const app::main_window::window::Commands::action_data_t & commands = this->core->commands->getActions();

	std::for_each(commands.cbegin(), commands.cend(), [&] (const auto & data) {
		const std::unique_ptr<app::main_window::json::Data> & commandData = data.second;
		const QString refCommand = QString::fromStdString(commandData->getLongCmd());

		// If user command matches the command in the JSON file
		if (userCommand.compare(refCommand) == 0) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperUserInput, "Found command " << refCommand << " matching user input: " << userCommand);
			this->core->updateUserInput(app::main_window::text_action_e::CLEAR);
			this->changeWindowState(commandData->getState(), postprocess);
		}
	});

	const app::main_window::state_e currentWindowState = this->core->getMainWindowState();

	if (previousWindowState == currentWindowState) {
		LOG_WARNING(mainWindowCtrlWrapperUserInput, "Window state remained unchanged to " << currentWindowState << " while runnign command " << userCommand);
	}
}

void app::main_window::window::CtrlWrapper::saveData() {

	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const QString & commandArgument = this->core->getUserText();

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Saving data: window state " << windowState << " command argument " << commandArgument);

	this->savedData.state = windowState;
	this->savedData.commandArgument = commandArgument;
}

void app::main_window::window::CtrlWrapper::restoreSavedData() {
	const app::main_window::state_e windowState = this->savedData.state;
	// Not taking a reference because when going to the IDLE state to any other state the text is cleared and the focus is changed hence the save data are as well
	const QString commandArgument = this->savedData.commandArgument;
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Restoring data: window state " << windowState << " command argument " << commandArgument);

	// TODO: Restore window state based on the user input text
	// TODO: - parse user input text to find command string (:<command name> -> NON COMMAND STATE or :<space> -> COMMAND)
	// TODO: - set state with no preprocessing - this should change the focus
	// TODO: - check that state is not IDLE

	this->changeWindowState(windowState, app::main_window::state_postprocessing_e::SETUP);
	this->core->printUserInput(app::main_window::text_action_e::SET, commandArgument);
	if (windowState == app::main_window::state_e::IDLE) {
		this->setAllShortcutEnabledProperty(true);
	} else {
		this->setAllShortcutEnabledProperty(false);
	}
}

CONST_GETTER(app::main_window::window::CtrlWrapper::getSavedData, app::main_window::window::ctrl_data_s &, this->savedData)

bool app::main_window::window::CtrlWrapper::isValidWindowState(const app::main_window::state_e & requestedWindowState) {
	bool isValid = false;
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const int tabCount = this->core->getTabCount();

	switch (requestedWindowState) {
		case app::main_window::state_e::IDLE:
		case app::main_window::state_e::OPEN_FILE:
			isValid = true;
			break;
		case app::main_window::state_e::COMMAND:
			// It is only possible to open a tab if in the idle state
			isValid = (windowState == app::main_window::state_e::IDLE);
			break;
		case app::main_window::state_e::QUIT:
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::TOGGLE_MENUBAR:
			// It is only possible to start a new command if in the idle state
			isValid = ((windowState == app::main_window::state_e::IDLE) || (windowState == app::main_window::state_e::COMMAND));
			break;
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::FIND:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
		case app::main_window::state_e::SCROLL_UP:
		case app::main_window::state_e::SCROLL_DOWN:
		case app::main_window::state_e::HISTORY_PREV:
		case app::main_window::state_e::HISTORY_NEXT:
			// It is only possible to perform an operation on a signel tab if the current state is idle and at least 1 tab is opened
			isValid = ((tabCount > 0) && ((windowState == app::main_window::state_e::IDLE) || (windowState == app::main_window::state_e::COMMAND)));
			break;
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
			// It is only possible to perform an operation that requires movement of cursors or tabs if the current state is idle and at least 2 tab is opened
			isValid = ((tabCount > 1) && ((windowState == app::main_window::state_e::IDLE) || (windowState == app::main_window::state_e::COMMAND)));
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to determine whether transaction from " << windowState << " to " << requestedWindowState << " is valid");
			break;
	}

	return isValid;
}

void app::main_window::window::CtrlWrapper::changeWindowStateWrapper(const std::unique_ptr<app::main_window::json::Data> & commandData, const app::main_window::state_postprocessing_e & postprocess) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Command " << commandData->getName() << " (shortcut: " << commandData->getShortcut() << " long command: " << commandData->getLongCmd() << ") - moving to state " << commandData->getState());
	this->changeWindowState(commandData->getState(), postprocess);
}

void app::main_window::window::CtrlWrapper::changeWindowState(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess) {

	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const std::unique_ptr<app::main_window::json::Data> & data = this->core->commands->findDataWithFieldValue("State", &windowState);
	QString longCmd = QString();
	if (data != this->core->commands->getInvalidData()) {
		longCmd = (QString::fromStdString(data->getLongCmd()));
	}

	// Global conditions are:
	// - it is possible to move to any state from the COMMAND state
	// - it is possible to move from any state to COMMAND state
	const bool globalCondition = ((windowState != app::main_window::state_e::COMMAND) && (nextState == app::main_window::state_e::COMMAND));

	// Do not change state if the window is already in the one requested
	if (windowState != nextState) {
		bool isValid = this->isValidWindowState(nextState) || globalCondition;
		if (isValid == true) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Window state change from state " << windowState << " to state " << nextState);
			this->core->setMainWindowState(nextState);

			if (postprocess == app::main_window::state_postprocessing_e::SETUP) {
				this->setupWindowState(windowState);
			} else if (postprocess == app::main_window::state_postprocessing_e::POSTPROCESS) {
				this->setupWindowState(windowState);
				this->postprocessWindowStateChange(windowState);
			} else if (postprocess == app::main_window::state_postprocessing_e::ACTION) {
				this->executeAction(nextState);
			} else {
				this->core->printUserInput(app::main_window::text_action_e::CLEAR);
			}

			emit windowStateChanged(nextState);
		}
	} else {
		LOG_WARNING(mainWindowCtrlWrapperOverall, "Ignoring request to go from state " << windowState << " to state " << nextState);
	}
}

void app::main_window::window::CtrlWrapper::setupWindowState(const app::main_window::state_e & previousState) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Setting up current state " << windowState << " - previous state was " << previousState);

	const int tabCount = this->core->getTabCount();
	std::shared_ptr<app::main_window::tab::Tab> tab = nullptr;
	QString searchText = QString();
	if (tabCount > 0) {
		const int tabIndex = this->core->getCurrentTabIndex();
		tab = this->core->tabs->widget(tabIndex);
		searchText = tab->getSearchText();
	}

	// Hide search results if not in find state
	const bool isFindState = ((windowState == app::main_window::state_e::FIND) || (windowState == app::main_window::state_e::FIND_DOWN) || (windowState == app::main_window::state_e::FIND_UP));
	std::unique_ptr<app::main_window::statusbar::Bar> & statusBar = this->core->bottomStatusBar;
	statusBar->showSearchResult(isFindState);

	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case app::main_window::state_e::IDLE:
			this->setFocus();
			this->setFocusProxy(nullptr);
			this->core->printUserInput(app::main_window::text_action_e::CLEAR);
			this->setAllShortcutEnabledProperty(true);
			break;
		case app::main_window::state_e::QUIT:
		case app::main_window::state_e::TOGGLE_MENUBAR:
			this->winctrl->setFocus();
			this->winctrl->setFocusProxy(nullptr);
			this->setAllShortcutEnabledProperty(false);
			break;
		case app::main_window::state_e::COMMAND:
			this->winctrl->setFocus();
			this->winctrl->setFocusProxy(statusBar->getUserInput().get());
			this->setAllShortcutEnabledProperty(false);
			break;
		case app::main_window::state_e::OPEN_FILE:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
		case app::main_window::state_e::SCROLL_UP:
		case app::main_window::state_e::SCROLL_DOWN:
		case app::main_window::state_e::HISTORY_PREV:
		case app::main_window::state_e::HISTORY_NEXT:
			this->tabctrl->setFocus();
			this->tabctrl->setFocusProxy(nullptr);
			this->setAllShortcutEnabledProperty(false);
			break;
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
		case app::main_window::state_e::FIND:
			this->setFocus();
			this->setFocusProxy(statusBar->getUserInput().get());
			this->setAllShortcutEnabledProperty(false);
			this->core->printUserInput(app::main_window::text_action_e::SET);
			break;
		case app::main_window::state_e::EDIT_SEARCH:
			EXCEPTION_ACTION_COND((tab == nullptr), throw, "Postprocessing state " << windowState << ": Unable to edit string used for previous search as pointer to tab is " << tab.get());
			this->tabctrl->setFocus();
			this->tabctrl->setFocusProxy(statusBar->getUserInput().get());
			this->core->printUserInput(app::main_window::text_action_e::SET, searchText);
			this->setAllShortcutEnabledProperty(false);
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to postprocess transaction to " << windowState << " is valid as state " << windowState << " doesn't have a defined postprocess action");
			break;
	}
}

void app::main_window::window::CtrlWrapper::postprocessWindowStateChange(const app::main_window::state_e & previousState) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Current state " << windowState << " previousState " << previousState);

	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case app::main_window::state_e::IDLE:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::COMMAND:
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
		case app::main_window::state_e::FIND:
			break;
		case app::main_window::state_e::QUIT:
			this->winctrl->closeWindow();
			break;
		case app::main_window::state_e::TOGGLE_MENUBAR:
			this->winctrl->toggleShowMenubar();
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::OPEN_FILE:
			this->tabctrl->createOpenPrompt();
			break;
		case app::main_window::state_e::FIND_DOWN:
			this->tabctrl->setFindDirection(app::shared::offset_type_e::DOWN);
			this->tabctrl->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::FIND_UP:
			this->tabctrl->setFindDirection(app::shared::offset_type_e::UP);
			this->tabctrl->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_UP:
			this->tabctrl->scrollTab(app::shared::offset_type_e::UP);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_DOWN:
			this->tabctrl->scrollTab(app::shared::offset_type_e::DOWN);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::HISTORY_PREV:
			this->tabctrl->goToPageInHistory(app::main_window::navigation_type_e::PREVIOUS);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::HISTORY_NEXT:
			this->tabctrl->goToPageInHistory(app::main_window::navigation_type_e::NEXT);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to postprocess transaction to " << windowState << " is valid as state " << windowState << " doesn't have a defined postprocess action");
			break;
	}
}

void app::main_window::window::CtrlWrapper::setAllShortcutEnabledProperty(const bool enabled) {
	const QList<QShortcut *> shortcuts = this->window()->findChildren<QShortcut *>(QString(), Qt::FindChildrenRecursively);

	for (QShortcut * shortcut : shortcuts) {
		app::commands::KeySequence key(shortcut->key());
		// If shortcut key is not defined, then do not do anything
		if (key.count() > 0) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperUserInput, "Setting enabled for key " << key.toString() << " to " << enabled);
			shortcut->setEnabled(enabled);
		}
	}
}

void app::main_window::window::CtrlWrapper::executeAction(const app::main_window::state_e & windowState) {
	switch (windowState) {
		case app::main_window::state_e::IDLE:
			LOG_ERROR(mainWindowCtrlWrapperUserInput, "Unable to execute action for state " << windowState);
			break;
		case app::main_window::state_e::QUIT:
		case app::main_window::state_e::TOGGLE_MENUBAR:
			this->winctrl->executeAction(windowState);
			break;
		case app::main_window::state_e::COMMAND:
			this->executeCommand(app::main_window::state_postprocessing_e::ACTION);
			break;
		case app::main_window::state_e::OPEN_FILE:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
		case app::main_window::state_e::SCROLL_UP:
		case app::main_window::state_e::SCROLL_DOWN:
		case app::main_window::state_e::HISTORY_PREV:
		case app::main_window::state_e::HISTORY_NEXT:
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
		case app::main_window::state_e::FIND:
		case app::main_window::state_e::EDIT_SEARCH:
			this->tabctrl->executeAction(windowState);
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to execute action for state " << windowState << " as state " << windowState << " doesn't have a defined window controller");
			break;
	}

	const app::main_window::state_e requestedWindowState = app::main_window::state_e::IDLE;
	this->changeWindowState(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS);

	this->core->updateUserInput(app::main_window::text_action_e::CLEAR);
	this->core->bottomStatusBar->setUserInputText(QString());

}

void app::main_window::window::CtrlWrapper::keyReleaseEvent(QKeyEvent * event) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyReleaseEvent(event);
	this->tabctrl->keyReleaseEvent(event);

	this->core->mainWidget->repaint();

}

void app::main_window::window::CtrlWrapper::focusInEvent(QFocusEvent * event) {
	if ((event->gotFocus() == true) && (event->reason() == Qt::ActiveWindowFocusReason)) {
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Main window control wrapper got the keyboard focus because it became active. Restoring the saved data");
		// If the controller is not in the idle state, it is already dealing with a command
		const app::main_window::state_e windowState = this->core->getMainWindowState();
		if (windowState == app::main_window::state_e::IDLE) {
			this->restoreSavedData();
		}
	}

}

void app::main_window::window::CtrlWrapper::focusOutEvent(QFocusEvent * event) {
	if ((event->lostFocus() == true) && (event->reason() == Qt::ActiveWindowFocusReason)) {
		const app::main_window::state_e requestedWindowState = app::main_window::state_e::IDLE;
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall, "Main window control wrapper lost the keyboard focus because it became inactive. Saving the data and setting the state to " << requestedWindowState);
		this->saveData();
		app::main_window::state_postprocessing_e statePostprocess = app::main_window::state_postprocessing_e::NONE;
		const app::main_window::state_e windowState = this->core->getMainWindowState();
		if (windowState == app::main_window::state_e::OPEN_FILE) {
			statePostprocess = app::main_window::state_postprocessing_e::NONE;
		} else {
			statePostprocess = app::main_window::state_postprocessing_e::SETUP;
		}
		this->changeWindowState(requestedWindowState, statePostprocess);
	}
}
