/**
 * @copyright
 * @file ctrl_wrapper.cpp
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/windows/main_window/window/ctrl_wrapper.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/shared/exception.h"

// Categories
LOGGING_CONTEXT(mainWindowCtrlWrapperOverall, mainWindowCtrlWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlWrapperUserInput, mainWindowCtrlWrapper.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::CtrlWrapper::CtrlWrapper(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : QWidget(parent), app::main_window::window::Base(core), winctrl(new app::main_window::window::Ctrl(this, core)), tabctrl(new app::main_window::window::CtrlTab(this, core)) {
	// Connect signals and slots
	this->connectSignals();

}

app::main_window::window::CtrlWrapper::~CtrlWrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Main window control wrapper destructor");
}

void app::main_window::window::CtrlWrapper::keyPressEvent(QKeyEvent * event) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyPress key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyPressEvent(event);
	this->tabctrl->keyPressEvent(event);

	this->core->mainWidget->repaint();

}

void app::main_window::window::CtrlWrapper::connectSignals() {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Connect signals");

	connect(this->winctrl.get(), &app::main_window::window::Ctrl::windowStateChangeRequested, this, &app::main_window::window::CtrlWrapper::changeWindowState);
	connect(this->tabctrl.get(), &app::main_window::window::CtrlTab::windowStateChangeRequested, this, &app::main_window::window::CtrlWrapper::changeWindowState);

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

void app::main_window::window::CtrlWrapper::keyReleaseEvent(QKeyEvent * event) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Key event details: event type: keyRelease key: " << event->key() << " modifier: " << event->modifiers());

	this->winctrl->keyReleaseEvent(event);
	this->tabctrl->keyReleaseEvent(event);

	this->core->mainWidget->repaint();

}

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
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Command " << commandData->getName() << " (shortcut: " << commandData->getShortcut() << " long command: " << commandData->getLongCmd() << ") - moving to state " << commandData->getState());
	this->changeWindowState(commandData->getState(), postprocess);
}

void app::main_window::window::CtrlWrapper::executeAction(const app::main_window::state_e & windowState) {
	this->winctrl->executeAction(windowState);
	this->tabctrl->executeAction(windowState);
}

void app::main_window::window::CtrlWrapper::changeWindowState(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess, const Qt::Key key) {

	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const QString userTypedText = this->core->getUserText();

	// Global conditions are:
	// - it is possible to move to any state from the COMMAND state
	// - it is possible to move from any state to COMMAND state if the user types Backspace and the user types text is empty
	const bool globalCondition = ((windowState != app::main_window::state_e::COMMAND) && (nextState == app::main_window::state_e::COMMAND) && (userTypedText.isEmpty() == true) && (key == Qt::Key_Backspace));

	// Do not change state if the window is already in the one requested
	if (windowState != nextState) {
		bool isValid = this->isValidWindowState(nextState) || globalCondition;
		if (isValid == true) {
			this->core->setMainWindowState(nextState);

			this->core->printUserInput(app::main_window::text_action_e::CLEAR);

			if (postprocess == app::main_window::state_postprocessing_e::SETUP) {
				this->setupWindowState(windowState);
			} else if (postprocess == app::main_window::state_postprocessing_e::POSTPROCESS) {
				this->setupWindowState(windowState);
				this->postprocessWindowStateChange(windowState);
			} else if (postprocess == app::main_window::state_postprocessing_e::ACTION) {
				this->executeAction(nextState);
			}
			emit windowStateChanged(nextState);
		}
	} else {
		LOG_WARNING(mainWindowCtrlWrapperOverall, "Ignoring request to go from state " << windowState << " to state " << nextState);
	}
}

void app::main_window::window::CtrlWrapper::setupWindowState(const app::main_window::state_e & previousState) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Setting up current state " << windowState << " previousState " << previousState);

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
	std::unique_ptr<app::main_window::status_bar::StatusBar> & statusBar = this->core->bottomStatusBar;
	statusBar->showSearchResult(isFindState);

	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case app::main_window::state_e::IDLE:
			this->core->printUserInput(app::main_window::text_action_e::CLEAR);
			this->setAllShortcutEnabledProperty(true);
			break;
		case app::main_window::state_e::QUIT:
		case app::main_window::state_e::TOGGLE_MENUBAR:
		case app::main_window::state_e::COMMAND:
			this->setAllShortcutEnabledProperty(false);
			winctrl->setFocus();
			break;
		case app::main_window::state_e::OPEN_FILE:
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
		case app::main_window::state_e::FIND:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
		case app::main_window::state_e::SCROLL_UP:
		case app::main_window::state_e::SCROLL_DOWN:
		case app::main_window::state_e::HISTORY_PREV:
		case app::main_window::state_e::HISTORY_NEXT:
			this->setAllShortcutEnabledProperty(false);
			tabctrl->setFocus();
			break;
		case app::main_window::state_e::EDIT_SEARCH:
			EXCEPTION_ACTION_COND((tab == nullptr), throw,  "Postprocessing state " << windowState << ": Unable to edit string used for previous search as pointer to tab is " << tab.get());
			this->core->printUserInput(app::main_window::text_action_e::SET, searchText);
			this->setAllShortcutEnabledProperty(false);
			tabctrl->setFocus();
			break;
		default: 
			EXCEPTION_ACTION(throw, "Unable to postprocess transaction to " << windowState << " is valid as state " << windowState << " doesn't have a defined postprocess action");
			break;
	}
}

void app::main_window::window::CtrlWrapper::postprocessWindowStateChange(const app::main_window::state_e & previousState) {
	const app::main_window::state_e windowState = this->core->getMainWindowState();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperOverall,  "Current state " << windowState << " previousState " << previousState);

	// If requesting to go to the idle state, enable shortcuts
	switch (windowState) {
		case app::main_window::state_e::IDLE:
		case app::main_window::state_e::COMMAND:
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
		case app::main_window::state_e::FIND:
			break;
		case app::main_window::state_e::QUIT:
			winctrl->closeWindow();
			break;
		case app::main_window::state_e::TOGGLE_MENUBAR:
			winctrl->toggleShowMenubar();
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::OPEN_FILE:
			tabctrl->createOpenPrompt();
			break;
		case app::main_window::state_e::FIND_DOWN:
			tabctrl->setFindDirection(app::shared::offset_type_e::DOWN);
			tabctrl->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::FIND_UP:
			tabctrl->setFindDirection(app::shared::offset_type_e::UP);
			tabctrl->searchCurrentTab(QString());
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_UP:
			tabctrl->scrollTab(app::shared::offset_type_e::UP);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::SCROLL_DOWN:
			tabctrl->scrollTab(app::shared::offset_type_e::DOWN);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::HISTORY_PREV:
			tabctrl->goToPageInHistory(app::main_window::navigation_type_e::PREVIOUS);
			this->changeWindowState(app::main_window::state_e::IDLE, app::main_window::state_postprocessing_e::POSTPROCESS);
			break;
		case app::main_window::state_e::HISTORY_NEXT:
			tabctrl->goToPageInHistory(app::main_window::navigation_type_e::NEXT);
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
		app::key_sequence::KeySequence key(shortcut->key());
		// If shortcut key is not defined, then do not do anything
		if (key.count() > 0) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlWrapperUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
			shortcut->setEnabled(enabled);
		}
	}
}
