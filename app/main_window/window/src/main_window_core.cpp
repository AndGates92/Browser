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
#include "global_functions.h"
#include "function_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCoreOverall, "mainWindowCore.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCoreUserInput, "mainWindowCtrlBase.userInput", MSG_TYPE_LEVEL)

main_window_core::MainWindowCore::MainWindowCore(QWidget * parentWindow) : mainWidget(new QWidget(parentWindow)), tabs(new main_window_tab_widget::MainWindowTabWidget(this->mainWidget)), topMenuBar(new main_window_menu_bar::MainWindowMenuBar(parentWindow)), bottomStatusBar(new main_window_status_bar::MainWindowStatusBar(parentWindow)), cmdMenu(new command_menu::CommandMenu(parentWindow)), mainWindowState(main_window_shared_types::state_e::IDLE), offsetType(main_window_shared_types::offset_type_e::IDLE), userText(QString::null) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core constructor");

}

main_window_core::MainWindowCore::MainWindowCore(const main_window_core::MainWindowCore & rhs) : mainWidget(rhs.mainWidget), tabs(rhs.tabs), topMenuBar(rhs.topMenuBar), bottomStatusBar(rhs.bottomStatusBar), cmdMenu(rhs.cmdMenu), mainWindowState(rhs.mainWindowState), offsetType(rhs.offsetType), userText(rhs.userText) {

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

	if (this->offsetType != rhs.offsetType) {
		this->offsetType = rhs.offsetType;
	}

	if (this->userText != rhs.userText) {
		this->userText = rhs.userText;
	}

	return *this;
}

main_window_core::MainWindowCore::MainWindowCore(main_window_core::MainWindowCore && rhs) : mainWidget(std::exchange(rhs.mainWidget, Q_NULLPTR)), tabs(std::exchange(rhs.tabs, Q_NULLPTR)), topMenuBar(std::exchange(rhs.topMenuBar, Q_NULLPTR)), bottomStatusBar(std::exchange(rhs.bottomStatusBar, Q_NULLPTR)), cmdMenu(std::exchange(rhs.cmdMenu, Q_NULLPTR)), mainWindowState(std::exchange(rhs.mainWindowState, main_window_shared_types::state_e::IDLE)), offsetType(std::exchange(rhs.offsetType, main_window_shared_types::offset_type_e::IDLE)), userText(std::exchange(rhs.userText, QString::null)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Move constructor main window core");
}

main_window_core::MainWindowCore & main_window_core::MainWindowCore::operator=(main_window_core::MainWindowCore && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Move assignment operator for main window core");

	if (&rhs != this) {
		if (this->mainWidget != Q_NULLPTR) {
			delete this->mainWidget;
		}
		this->mainWidget = std::exchange(rhs.mainWidget, Q_NULLPTR);

		if (this->tabs != Q_NULLPTR) {
			delete this->tabs;
		}
		this->tabs = std::exchange(rhs.tabs, Q_NULLPTR);

		if (this->topMenuBar != Q_NULLPTR) {
			delete this->topMenuBar;
		}
		this->topMenuBar = std::exchange(rhs.topMenuBar, Q_NULLPTR);

		if (this->bottomStatusBar != Q_NULLPTR) {
			delete this->bottomStatusBar;
		}
		this->bottomStatusBar = std::exchange(rhs.bottomStatusBar, Q_NULLPTR);

		if (this->cmdMenu != Q_NULLPTR) {
			delete this->cmdMenu;
		}
		this->cmdMenu = std::exchange(rhs.cmdMenu, Q_NULLPTR);

		this->mainWindowState = std::exchange(rhs.mainWindowState, main_window_shared_types::state_e::IDLE);
		this->offsetType = std::exchange(rhs.offsetType, main_window_shared_types::offset_type_e::IDLE);
		this->userText = std::exchange(rhs.userText, QString::null);
	}

	return *this;
}

main_window_core::MainWindowCore::~MainWindowCore() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core destructor");

	// Menubar
	if (this->topMenuBar != Q_NULLPTR) {
		delete this->topMenuBar;
	}

	// Status bar
	if (this->bottomStatusBar != Q_NULLPTR) {
		delete this->bottomStatusBar;
	}

	// Command menu
	if (this->cmdMenu != Q_NULLPTR) {
		delete this->cmdMenu;
	}

	// tabs
	if (this->tabs != Q_NULLPTR) {
		delete this->tabs;
	}

	// Main widget
	if (this->mainWidget != Q_NULLPTR) {
		delete this->mainWidget;
	}
}

QString main_window_core::MainWindowCore::getActionName() const {
	QString actionNameText(QString::null);

	const QString actionName(global_functions::qEnumToQString<main_window_shared_types::state_list>(this->mainWindowState, true));
	actionNameText.append(actionName);

	if (this->mainWindowState == main_window_shared_types::state_e::MOVE_TAB) {
		if (this->offsetType == main_window_shared_types::offset_type_e::RIGHT) {
			actionNameText.append(" right");
		} else if (this->offsetType == main_window_shared_types::offset_type_e::LEFT) {
			actionNameText.append(" left");
		}
	}

	// Create lowercase copy of the string
	actionNameText = actionNameText.toLower();
	actionNameText = actionNameText.replace(QChar('_'), QChar(' '), Qt::CaseInsensitive);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreUserInput,  "State " << this->mainWindowState << " action text " << actionNameText);

	return actionNameText;
}

BASE_GETTER(main_window_core::MainWindowCore::getTabCount, int, this->tabs->count())

BASE_GETTER(main_window_core::MainWindowCore::getCurrentTabIndex, int, this->tabs->currentIndex())

BASE_GETTER(main_window_core::MainWindowCore::getMainWindowState, main_window_shared_types::state_e, this->mainWindowState)

BASE_GETTER(main_window_core::MainWindowCore::getOffsetType, main_window_shared_types::offset_type_e, this->offsetType)

CONST_GETTER(main_window_core::MainWindowCore::getUserText, QString, this->userText)

void main_window_core::MainWindowCore::setMainWindowState(main_window_shared_types::state_e windowState) {
	this->mainWindowState = windowState;
}

void main_window_core::MainWindowCore::setOffsetType(main_window_shared_types::offset_type_e type) {
	this->offsetType = type;
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


