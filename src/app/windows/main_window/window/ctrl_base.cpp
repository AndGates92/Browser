/**
 * @copyright
 * @file ctrl_base.cpp
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class functions
 */

// Qt libraries
#include <QtWidgets/QShortcut>
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/qt/qt_operator.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/windows/main_window/shared/shared_types.h"
#include "app/windows/main_window/window/commands.h"
#include "app/windows/main_window/window/ctrl_base.h"
#include "app/windows/main_window/statusbar/bar.h"
#include "app/windows/main_window/json/action.h"
#include "app/widgets/commands/key_sequence.h"

LOGGING_CONTEXT(mainWindowCtrlBaseOverall, mainWindowCtrlBase.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlBaseCheck, mainWindowCtrlBase.check, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCtrlBaseUserInput, mainWindowCtrlBase.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::CtrlBase::CtrlBase(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core) : QWidget(parent), app::main_window::window::Base(core) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");
}

app::main_window::window::CtrlBase::~CtrlBase() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");
}

void app::main_window::window::CtrlBase::executeCommand(const QString & userCommand, const app::main_window::state_postprocessing_e & postprocess) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Looking for command matching user input: " << userCommand);

	const app::main_window::state_e previousWindowState = this->core->getMainWindowState();

	const app::main_window::window::Commands::action_data_t & commands = this->core->commands->getActions();

	std::for_each(commands.cbegin(), commands.cend(), [&] (const auto & data) {
		const std::unique_ptr<app::main_window::json::Data> & commandData = data.second;
		const QString refCommand = QString::fromStdString(commandData->getLongCmd());

		// If user command matches the command in the JSON file
		if (userCommand.compare(refCommand) == 0) {
			LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCtrlBaseOverall,  "Found command " << refCommand << " matching user input: " << userCommand);
			emit windowStateChangeRequested(commandData->getState(), postprocess);
		}
	});

	const app::main_window::state_e currentWindowState = this->core->getMainWindowState();

	if (previousWindowState == currentWindowState) {
		LOG_WARNING(mainWindowCtrlBaseOverall, "Window state remained unchanged to " << currentWindowState << " while runnign command " << userCommand);
	}

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

void app::main_window::window::CtrlBase::keyReleaseEvent(QKeyEvent * event) {

	const int releasedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const app::commands::KeySequence keySeq(releasedKey | keyModifiers);

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
							this->core->printUserInput(app::main_window::text_action_e::CLEAR);
						}
						this->moveToCommandStateFromNonIdleState(windowState, static_cast<Qt::Key>(releasedKey));
					}
				} else {
					// Compute position of the last character in the string
					const int endString = userTypedText.count() - 1;
					// Delete last character of the string
					userTypedText = userTypedText.remove(endString, 1);
					this->core->printUserInput(app::main_window::text_action_e::SET, userTypedText);
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

	const app::commands::KeySequence keySeq(pressedKey | keyModifiers);

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
	const std::unique_ptr<app::main_window::json::Data> & data = this->core->commands->findDataWithFieldValue("State", &windowState);
	if (data != this->core->commands->getInvalidData()) {
		QString longCmd(QString::fromStdString(data->getLongCmd()));
		emit windowStateChangeRequested(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS, key);
		// Setting the user input here because it is cleared when changing state
		this->core->printUserInput(app::main_window::text_action_e::SET, longCmd);
	}
}

void app::main_window::window::CtrlBase::resetWindowState() {
	const app::main_window::state_e requestedWindowState = app::main_window::state_e::IDLE;
	emit windowStateChangeRequested(requestedWindowState, app::main_window::state_postprocessing_e::POSTPROCESS);

	this->core->updateUserInput(app::main_window::text_action_e::CLEAR, QString());
	this->core->bottomStatusBar->setUserInputText(QString());

	// Give the focus back to the parent widget
	this->parentWidget()->setFocus();
}
