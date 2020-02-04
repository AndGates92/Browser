/**
 * @copyright
 * @file main_window_core.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window core functions
 */

#include <iostream>
// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "main_window_core.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCoreOverall, "mainWindowCore.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCoreUserInput, "mainWindowCtrlBase.userInput", MSG_TYPE_LEVEL)

main_window_core::MainWindowCore::MainWindowCore() : mainWidget(Q_NULLPTR), tabs(Q_NULLPTR), topMenuBar(Q_NULLPTR), bottomStatusBar(Q_NULLPTR), cmdMenu(Q_NULLPTR), mainWindowState(main_window_shared_types::state_e::IDLE), moveValueType(main_window_shared_types::move_value_e::IDLE), userText(QString::null) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core constructor");

}

main_window_core::MainWindowCore::~MainWindowCore() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core destructor");

	// Menubar
	delete this->topMenuBar;

	// Label
	delete this->bottomStatusBar;
	delete this->cmdMenu;

	// Main components
	delete this->tabs;

	// Main widget
	delete this->mainWidget;
}

int main_window_core::MainWindowCore::getTabCount() {
	return this->tabs->count();
}

QString main_window_core::MainWindowCore::getActionName() {
	QString actionName(QString::null);

	actionName << this->mainWindowState;

	if (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (this->moveValueType == main_window_shared_types::move_value_e::RIGHT) {
			actionName.append(" right");
		} else if (this->moveValueType == main_window_shared_types::move_value_e::LEFT) {
			actionName.append(" left");
		}
	}

	// Create lowercase copy of the string
	actionName = actionName.toLower();

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreUserInput,  "State " << this->mainWindowState << " action text " << actionName);

	return actionName;
}

int main_window_core::MainWindowCore::getCurrentTabIndex() {
	return this->tabs->currentIndex();
}

void main_window_core::MainWindowCore::updateUserInput(const main_window_shared_types::text_action_e action, QString text) {

	switch (action) {
		case main_window_shared_types::text_action_e::SET:
			this->userText.clear();
			this->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::APPEND:
			this->userText.append(text);
			break;
		case main_window_shared_types::text_action_e::CLEAR:
			this->userText.clear();
			break;
		default:
			qWarning(mainWindowCoreUserInput) << "Unknown action " << action << "\n";
			break;
	}
}

main_window_shared_types::state_e main_window_core::MainWindowCore::getMainWindowState() {
	return this->mainWindowState;
}

main_window_shared_types::move_value_e main_window_core::MainWindowCore::getMoveValueType() {
	return this->moveValueType;
}

QString main_window_core::MainWindowCore::getUserText() {
	return this->userText;
}

void main_window_core::MainWindowCore::setMainWindowState(main_window_shared_types::state_e windowState) {
	this->mainWindowState = windowState;
}

void main_window_core::MainWindowCore::setMoveValueType(main_window_shared_types::move_value_e moveType) {
	this->moveValueType = moveType;
}
