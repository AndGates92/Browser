/**
 * @copyright
 * @file main_window_ctrl_base.cpp
 * @author Andrea Gianarda
 * @date 29th of January 2019
 * @brief Main Window Control base class functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "main_window_ctrl_base.h"
#include "main_window_shared_types.h"
#include "global_types.h"
#include "global_macros.h"

Q_LOGGING_CATEGORY(mainWindowCtrlBaseOverall, "mainWindowCtrlBase.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCtrlBaseUserInput, "mainWindowCtrlBase.userInput", MSG_TYPE_LEVEL)

main_window_ctrl_base::MainWindowCtrlBase::MainWindowCtrlBase(main_window_core::MainWindowCore * windowCore, QWidget * parent, QString jsonFileName) : parent(parent), mainWindowCore(windowCore), commands(json_parser::JsonParser(jsonFileName, QIODevice::ReadOnly)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base classe constructor");
}

main_window_ctrl_base::MainWindowCtrlBase::~MainWindowCtrlBase() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseOverall,  "Main window control base class destructor");

}

int main_window_ctrl_base::MainWindowCtrlBase::getTabCount() {
	return this->mainWindowCore->tabs->count();
}

int main_window_ctrl_base::MainWindowCtrlBase::getCurrentTabIndex() {
	return this->mainWindowCore->tabs->currentIndex();
}

void main_window_ctrl_base::MainWindowCtrlBase::printUserInput(const main_window_shared_types::text_action_e action, QString text) {

	QString textPrint(QString::null);
	if (text == QString::null) {
		textPrint.append("Not provided");
	} else {
		textPrint.append(text);
	}

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "Action is " << action << " for user input " << textPrint);

	switch (action) {
		case main_window_shared_types::text_action_e::SET:
			this->mainWindowCore->userText.clear();
			this->mainWindowCore->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::APPEND:
			this->mainWindowCore->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::CLEAR:
			this->mainWindowCore->userText.clear();
			break;
		default:
			qWarning(mainWindowCtrlBaseUserInput) << "Unknown action " << action << "\n";
			break;
	}

	QString textLabel(QString::null);
	if (this->mainWindowCore->mainWindowState != main_window_shared_types::state_e::IDLE) {
		QString userAction(QString::null);
		if (this->mainWindowCore->mainWindowState != main_window_shared_types::state_e::COMMAND) {
			// Get action name
			userAction = this->getActionName();
		}
		// Create string following format: :<action> <userText>
		textLabel.append(":" + userAction + " " + this->mainWindowCore->userText);
	}

	this->mainWindowCore->userInputText->setText(textLabel);

}

QString main_window_ctrl_base::MainWindowCtrlBase::getActionName() {
	QString actionName(QString::null);

	actionName << this->mainWindowCore->mainWindowState;

	if (this->mainWindowCore->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (this->mainWindowCore->moveValueType == main_window_shared_types::move_value_e::RIGHT) {
			actionName.append(" right");
		} else if (this->mainWindowCore->moveValueType == main_window_shared_types::move_value_e::LEFT) {
			actionName.append(" left");
		}
	}

	// Create lowercase copy of the string
	actionName = actionName.toLower();

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlBaseUserInput,  "State " << this->mainWindowCore->mainWindowState << " action text " << actionName);

	return actionName;
}

void main_window_ctrl_base::MainWindowCtrlBase::updateInfo() {
	QString info(QString::null);
	info = this->mainWindowCore->createTabInfo();

	this->mainWindowCore->infoText->setText(info);
}
