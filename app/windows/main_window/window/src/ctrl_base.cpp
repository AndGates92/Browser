/**
 * @copyright
 * @file ctrl_base.cpp
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class functions
 */

// Qt libraries
#include <QtWidgets/QShortcut>

#include "utility/stl/include/cpp_operator.h"
#include "utility/qt/include/qt_operator.h"
#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "windows/main_window/common/include/shared_types.h"
#include "windows/main_window/window/include/ctrl_base.h"
#include "widgets/commands/include/key_sequence.h"

LOGGING_CONTEXT(mainWindowCtrlBaseOverall, mainWindowCtrlBase.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlBaseCheck, mainWindowCtrlBase.check, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlBaseUserInput, mainWindowCtrlBase.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::CtrlBase::CtrlBase(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core, const QString & jsonFileName) : QWidget(parent), app::main_window::window::Base(core), app::main_window::json::Action(jsonFileName) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");

	// Shortcuts
	this->createShortcuts();

	// Connect signals and slots
	this->connectSignals();

}

app::main_window::window::CtrlBase::~CtrlBase() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");
}

void app::main_window::window::CtrlBase::printUserInput(const app::main_window::text_action_e & action, const QString & text) {

	QString textPrint = QString();
	if (text == QString()) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Action is " << action << " for user input " << textPrint);

	this->core->updateUserInput(action, text);

	const app::main_window::state_e windowState = this->core->getMainWindowState();

	QString textLabel = QString();
	if (windowState != app::main_window::state_e::IDLE) {
		QString userAction = QString();
		if (windowState != app::main_window::state_e::COMMAND) {
			// Get action name
			userAction = this->core->getActionName();
		}
		// Create string following format: :<action> <userText>
		textLabel.append(":" + userAction + " " + this->core->getUserText());
	}

	this->core->bottomStatusBar->setUserInputText(textLabel);

}

void app::main_window::window::CtrlBase::changeWindowStateWrapper(const std::unique_ptr<app::main_window::json::Data> & commandData, const app::main_window::state_postprocessing_e & postprocess) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Command " << commandData->getName() << " (shortcut: " << commandData->getShortcut() << " long command: " << commandData->getLongCmd() << ") - moving to state " << commandData->getState());
	this->changeWindowState(commandData->getState(), postprocess);
}

void app::main_window::window::CtrlBase::executeCommand(const QString & userCommand, const app::main_window::state_postprocessing_e & postprocess) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Looking for command matching user input: " << userCommand);

	std::for_each(this->actionData.cbegin(), this->actionData.cend(), [&] (const auto & data) {
		const std::unique_ptr<app::main_window::json::Data> & commandData = data.second;
		const QString refCommand = QString::fromStdString(commandData->getLongCmd());

		// If user command matches the command in the JSON file
		if (userCommand.compare(refCommand) == 0) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Found command " << refCommand << " matching user input: " << userCommand);
			this->changeWindowStateWrapper(commandData, postprocess);
		}
	});

}

void app::main_window::window::CtrlBase::createShortcuts() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Create shortcuts");

//	this->createExtraShortcuts();
}

void app::main_window::window::CtrlBase::connectSignals() {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Connect signals");

	std::for_each(this->actionData.cbegin(), this->actionData.cend(), [&] (const auto & data) {
		const std::unique_ptr<app::main_window::json::Data> & commandData = data.second;
		QShortcut * shortcut = new QShortcut(commandData->getShortcut(), this->window());
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall, "Connecting shortcut for key " << (commandData->getShortcut()) << " to trigger a change of controller state to " << commandData->getState());
		QMetaObject::Connection connection = connect(shortcut, &QShortcut::activated,
			[&] () {
				this->changeWindowStateWrapper(commandData, app::main_window::state_postprocessing_e::POSTPROCESS);
			}
		);

		EXCEPTION_ACTION_COND((static_cast<bool>(connection) == false), throw, "Unable to connect shortcut for key " << (commandData->getShortcut()) << " to trigger a change of controller state to " << commandData->getState());

	});

//	this->connectExtraSignals();

}

void app::main_window::window::CtrlBase::updateScroll() {
	const int tabCount = this->core->getTabCount();

	int vScroll = -1;

	if (tabCount > 0) {
		vScroll = 0;
	}

	this->core->bottomStatusBar->setVScroll(vScroll);
}

void app::main_window::window::CtrlBase::updateInfo(const int & currIndex) {
	const QString info(this->tabInfoStr(currIndex));

	this->core->bottomStatusBar->setInfoText(info);
}

QString app::main_window::window::CtrlBase::tabInfoStr(const int & currIndex) const {

	const int tabCount = this->core->getTabCount();

	QString tabInfo = QString();
	if (tabCount == 0) {
		tabInfo.append("No tabs");
	} else {
		tabInfo.append("tab ");
		tabInfo.append(QString("%1").arg(currIndex + 1));
		tabInfo.append(" out of ");
		tabInfo.append(QString("%1").arg(tabCount));
	}

	return tabInfo;
}

void app::main_window::window::CtrlBase::setAllShortcutEnabledProperty(const bool enabled) {
	const QList<QShortcut *> shortcuts = this->window()->findChildren<QShortcut *>(QString(), Qt::FindChildrenRecursively);

	for (QShortcut * shortcut : shortcuts) {
		app::key_sequence::KeySequence key(shortcut->key());
		// If shortcut key is not defined, then do not do anything
		if (key.count() > 0) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Setting enabled for key " << key.toString() << " to " << enabled);
			shortcut->setEnabled(enabled);
		}
	}
}

void app::main_window::window::CtrlBase::changeWindowState(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess, const Qt::Key key) {

	const app::main_window::state_e windowState = this->core->getMainWindowState();
	const QString userTypedText = this->core->getUserText();

	// Global conditions are:
	// - it is possible to move to any state from the COMMAND state
	// - it is possible to move from any state to COMMAND state if the user types Backspace and the user types text is empty
	const bool globalCondition = (windowState == app::main_window::state_e::COMMAND) || ((windowState != app::main_window::state_e::COMMAND) && (nextState == app::main_window::state_e::COMMAND) && (userTypedText.isEmpty() == true) && (key == Qt::Key_Backspace));


	// Do not change state if the window is already in the one requested
	if (windowState != nextState) {
		bool isValid = this->isValidWindowState(nextState) || globalCondition;
		if (isValid == true) {
			this->core->setMainWindowState(nextState);

			this->printUserInput(app::main_window::text_action_e::CLEAR);

			if (postprocess == app::main_window::state_postprocessing_e::POSTPROCESS) {
				this->postprocessWindowStateChange(windowState);
			} else if (postprocess == app::main_window::state_postprocessing_e::ACTION) {
				this->executeAction(nextState);
			}
			emit windowStateChanged(nextState);
		}
	} else {
		LOG_WARNING(mainWindowCtrlBaseOverall, "Ignoring request to go from state " << windowState << " to state " << nextState);
	}
}

void app::main_window::window::CtrlBase::keyReleaseEvent(QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const app::key_sequence::KeySequence keySeq(releasedKey | keyModifiers);

	if (event->type() == QEvent::KeyRelease) {

		const app::main_window::state_e windowState = this->core->getMainWindowState();
		QString userTypedText = this->core->getUserText();

		// Retrieve main window controller state
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (releasedKey) {
			case Qt::Key_Backspace:
				LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseUserInput,  "User typed text " << userTypedText);
				// If in state TAB MOVE and the core->userText is empty after deleting the last character, set the move value to IDLE
				if (userTypedText.isEmpty() == true) {
					if (windowState != app::main_window::state_e::COMMAND) {
						if (windowState == app::main_window::state_e::MOVE_TAB) {
							this->core->setOffsetType(app::shared::offset_type_e::IDLE);
							this->printUserInput(app::main_window::text_action_e::CLEAR);
						}
						this->moveToCommandStateFromNonIdleState(windowState, static_cast<Qt::Key>(releasedKey));
					}
				} else {
					// Compute position of the last character in the string
					const int endString = userTypedText.count() - 1;
					// Delete last character of the string
					userTypedText = userTypedText.remove(endString, 1);
					this->printUserInput(app::main_window::text_action_e::SET, userTypedText);
				}
				break;
			default:
				this->actionOnReleasedKey(windowState, event);
				break;
		}
	}
}



void app::main_window::window::CtrlBase::keyPressEvent(QKeyEvent * event) {

	const int pressedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const app::key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		const app::main_window::state_e windowState = this->core->getMainWindowState();

		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseUserInput,  "State " << windowState << " key " << keySeq.toString());

		switch (pressedKey) {
			case Qt::Key_Enter:
			case Qt::Key_Return:
				this->executeAction(windowState);
				break;
			default:
				this->prepareAction(windowState, event);
				break;
		}
	}

	// If user presses escape, enter or return key, bring the state to IDLE and delete user input
	if ((pressedKey == Qt::Key_Escape) || (pressedKey == Qt::Key_Return) || (pressedKey == Qt::Key_Enter)) {
		this->resetWindowState();
	}

}

void app::main_window::window::CtrlBase::moveToCommandStateFromNonIdleState(const app::main_window::state_e & windowState, const Qt::Key & key) {
	// Saving long command for a given state to set it after changing state
	const app::main_window::state_e requestedWindowState = app::main_window::state_e::COMMAND;
	const std::unique_ptr<app::main_window::json::Data> & data = this->findDataWithFieldValue("State", &windowState);
	if (data != this->getInvalidData()) {
		QString longCmd(QString::fromStdString(data->getLongCmd()));
		this->changeWindowState(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS, key);
		// Setting the user input here because it is cleared when changing state
		this->printUserInput(app::main_window::text_action_e::SET, longCmd);
	}
}

void app::main_window::window::CtrlBase::resetWindowState() {
	const app::main_window::state_e requestedWindowState = app::main_window::state_e::IDLE;
	this->core->setMainWindowState(requestedWindowState);

	this->core->updateUserInput(app::main_window::text_action_e::CLEAR, QString());
	this->core->bottomStatusBar->setUserInputText(QString());
	this->core->getUserText();

	// Enable all shortcuts
	this->setAllShortcutEnabledProperty(true);

	// Give the focus back to the parent widget
	this->parentWidget()->setFocus();
}
