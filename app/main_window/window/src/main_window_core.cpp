/**
 * @copyright
 * @file main_window_core.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window core functions
 */

#include <iostream>
// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "main_window_core.h"
#include "exception_macros.h"

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

	// Status bar
	delete this->bottomStatusBar;

	// Command menu
	delete this->cmdMenu;

	// tabs
	delete this->tabs;

	// Main widget
	delete this->mainWidget;
}

int main_window_core::MainWindowCore::getTabCount() const {
	return this->tabs->count();
}

QString main_window_core::MainWindowCore::getActionName() const {
	QString actionNameText(QString::null);

	QString actionName(global_functions::qEnumToQString<main_window_shared_types::state_list>(this->mainWindowState, true));
	actionNameText.append(actionName);

	if (this->mainWindowState == main_window_shared_types::state_e::TAB_MOVE) {
		if (this->moveValueType == main_window_shared_types::move_value_e::RIGHT) {
			actionNameText.append(" right");
		} else if (this->moveValueType == main_window_shared_types::move_value_e::LEFT) {
			actionNameText.append(" left");
		}
	}

	// Create lowercase copy of the string
	actionNameText = actionNameText.toLower();
	actionNameText = actionNameText.replace(QChar('_'), QChar(' '), Qt::CaseInsensitive);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreUserInput,  "State " << this->mainWindowState << " action text " << actionNameText);

	return actionNameText;
}

int main_window_core::MainWindowCore::getCurrentTabIndex() const {
	return this->tabs->currentIndex();
}

main_window_shared_types::state_e main_window_core::MainWindowCore::getMainWindowState() const {
	return this->mainWindowState;
}

main_window_shared_types::move_value_e main_window_core::MainWindowCore::getMoveValueType() const {
	return this->moveValueType;
}

QString main_window_core::MainWindowCore::getUserText() const {
	return this->userText;
}

void main_window_core::MainWindowCore::setMainWindowState(main_window_shared_types::state_e windowState) {
	this->mainWindowState = windowState;
}

void main_window_core::MainWindowCore::setMoveValueType(main_window_shared_types::move_value_e moveType) {
	this->moveValueType = moveType;
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
			QEXCEPTION_ACTION(throw,  "Unknown action " << action);
			break;
	}
}


