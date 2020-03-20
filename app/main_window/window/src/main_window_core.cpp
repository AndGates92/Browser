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

main_window_core::MainWindowCore::MainWindowCore(QWidget * parentWindow) : mainWidget(new QWidget(parentWindow)), tabs(new main_window_tab_widget::MainWindowTabWidget(this->mainWidget)), topMenuBar(new main_window_menu_bar::MainWindowMenuBar(parentWindow)), bottomStatusBar(new main_window_status_bar::MainWindowStatusBar(parentWindow)), cmdMenu(new command_menu::CommandMenu(parentWindow)), mainWindowState(main_window_shared_types::state_e::IDLE), moveValueType(main_window_shared_types::move_value_e::IDLE), userText(QString::null) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core constructor");

}

main_window_core::MainWindowCore::MainWindowCore(const main_window_core::MainWindowCore & rhs) : mainWidget(rhs.mainWidget), tabs(rhs.tabs), topMenuBar(rhs.topMenuBar), bottomStatusBar(rhs.bottomStatusBar), cmdMenu(rhs.cmdMenu), mainWindowState(rhs.mainWindowState), moveValueType(rhs.moveValueType), userText(rhs.userText) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Copy constructor main window core");

}

main_window_core::MainWindowCore & main_window_core::MainWindowCore::operator=(const main_window_core::MainWindowCore & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Copy assignment operator for main window core");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->mainWidget != rhs.mainWidget) {
		if (this->mainWidget != Q_NULLPTR) {
			delete this->mainWidget;
		}
		this->mainWidget = rhs.mainWidget;
	}

	if (this->tabs != rhs.tabs) {
		if (this->tabs != Q_NULLPTR) {
			delete this->tabs;
		}
		this->tabs = rhs.tabs;
	}

	if (this->topMenuBar != rhs.topMenuBar) {
		if (this->topMenuBar != Q_NULLPTR) {
			delete this->topMenuBar;
		}
		this->topMenuBar = rhs.topMenuBar;
	}

	if (this->bottomStatusBar != rhs.bottomStatusBar) {
		if (this->bottomStatusBar != Q_NULLPTR) {
			delete this->bottomStatusBar;
		}
		this->bottomStatusBar = rhs.bottomStatusBar;
	}

	if (this->cmdMenu != rhs.cmdMenu) {
		if (this->cmdMenu != Q_NULLPTR) {
			delete this->cmdMenu;
		}
		this->cmdMenu = rhs.cmdMenu;
	}

	if (this->mainWindowState != rhs.mainWindowState) {
		this->mainWindowState = rhs.mainWindowState;
	}

	if (this->moveValueType != rhs.moveValueType) {
		this->moveValueType = rhs.moveValueType;
	}

	if (this->userText != rhs.userText) {
		this->userText = rhs.userText;
	}

	return *this;
}

main_window_core::MainWindowCore::MainWindowCore(main_window_core::MainWindowCore && rhs) : mainWidget(std::move(rhs.mainWidget)), tabs(std::move(rhs.tabs)), topMenuBar(std::move(rhs.topMenuBar)), bottomStatusBar(std::move(rhs.bottomStatusBar)), cmdMenu(std::move(rhs.cmdMenu)), mainWindowState(std::move(rhs.mainWindowState)), moveValueType(std::move(rhs.moveValueType)), userText(std::move(rhs.userText)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Move constructor main window core");

	// Reset rhs
	rhs.mainWidget = Q_NULLPTR;
	rhs.tabs = Q_NULLPTR;
	rhs.topMenuBar = Q_NULLPTR;
	rhs.bottomStatusBar = Q_NULLPTR;
	rhs.cmdMenu = Q_NULLPTR;
	rhs.mainWindowState = main_window_shared_types::state_e::IDLE;
	rhs.moveValueType = main_window_shared_types::move_value_e::IDLE;
	rhs.userText = QString::null;
}

main_window_core::MainWindowCore & main_window_core::MainWindowCore::operator=(main_window_core::MainWindowCore && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Move assignment operator for main window core");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->mainWidget != rhs.mainWidget) {
		if (this->mainWidget != Q_NULLPTR) {
			delete this->mainWidget;
		}
		this->mainWidget = std::move(rhs.mainWidget);
	}
	rhs.mainWidget = Q_NULLPTR;

	if (this->tabs != rhs.tabs) {
		if (this->tabs != Q_NULLPTR) {
			delete this->tabs;
		}
		this->tabs = std::move(rhs.tabs);
	}
	rhs.tabs = Q_NULLPTR;

	if (this->topMenuBar != rhs.topMenuBar) {
		if (this->topMenuBar != Q_NULLPTR) {
			delete this->topMenuBar;
		}
		this->topMenuBar = std::move(rhs.topMenuBar);
	}
	rhs.topMenuBar = Q_NULLPTR;

	if (this->bottomStatusBar != rhs.bottomStatusBar) {
		if (this->bottomStatusBar != Q_NULLPTR) {
			delete this->bottomStatusBar;
		}
		this->bottomStatusBar = std::move(rhs.bottomStatusBar);
	}
	rhs.bottomStatusBar = Q_NULLPTR;

	if (this->cmdMenu != rhs.cmdMenu) {
		if (this->cmdMenu != Q_NULLPTR) {
			delete this->cmdMenu;
		}
		this->cmdMenu = std::move(rhs.cmdMenu);
	}
	rhs.cmdMenu = Q_NULLPTR;

	if (this->mainWindowState != rhs.mainWindowState) {
		this->mainWindowState = std::move(rhs.mainWindowState);
	}
	rhs.mainWindowState = main_window_shared_types::state_e::IDLE;

	if (this->moveValueType != rhs.moveValueType) {
		this->moveValueType = std::move(rhs.moveValueType);
	}
	rhs.moveValueType = main_window_shared_types::move_value_e::IDLE;

	if (this->userText != rhs.userText) {
		this->userText = std::move(rhs.userText);
	}
	rhs.userText = QString::null;

	return *this;
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


