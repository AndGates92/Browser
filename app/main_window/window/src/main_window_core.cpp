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
#include "global_qfunctions.h"
#include "function_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCoreOverall, "mainWindowCore.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCoreUserInput, "mainWindowCore.userInput", MSG_TYPE_LEVEL)

main_window_core::MainWindowCore::MainWindowCore(QWidget * parent) : mainWidget(new QWidget(parent)), tabs(new main_window_tab_widget::MainWindowTabWidget(parent)), topMenuBar(new main_window_menu_bar::MainWindowMenuBar(parent)), popup(new main_window_popup_container::MainWindowPopupContainer(parent)), bottomStatusBar(new main_window_status_bar::MainWindowStatusBar(parent)), cmdMenu(new command_menu::CommandMenu(parent)), mainWindowState(main_window_shared_types::state_e::IDLE), offsetType(main_window_shared_types::offset_type_e::IDLE), userText(QString::null) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core constructor");
	this->topMenuBar->createMenus();
}

main_window_core::MainWindowCore::MainWindowCore(const main_window_core::MainWindowCore & rhs) : mainWidget(Q_NULLPTR), tabs(Q_NULLPTR), topMenuBar(rhs.topMenuBar), popup(rhs.popup), bottomStatusBar(Q_NULLPTR), cmdMenu(Q_NULLPTR), mainWindowState(rhs.mainWindowState), offsetType(rhs.offsetType), userText(rhs.userText) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Copy constructor main window core");

	this->cmdMenu.reset(rhs.cmdMenu.get());
	this->bottomStatusBar.reset(rhs.bottomStatusBar.get());
	this->mainWidget.reset(rhs.mainWidget.get());
	this->tabs.reset(rhs.tabs.get());

}

main_window_core::MainWindowCore & main_window_core::MainWindowCore::operator=(const main_window_core::MainWindowCore & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Copy assignment operator for main window core");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->mainWidget != rhs.mainWidget) {
		this->mainWidget.reset(rhs.mainWidget.get());
	}

	if (this->tabs != rhs.tabs) {
		this->tabs.reset(rhs.tabs.get());
	}

	if (this->topMenuBar != rhs.topMenuBar) {
		this->topMenuBar = rhs.topMenuBar;
	}

	if (this->popup != rhs.popup) {
		this->popup = rhs.popup;
	}

	if (this->bottomStatusBar != rhs.bottomStatusBar) {
		this->bottomStatusBar.reset(rhs.bottomStatusBar.get());
	}

	if (this->cmdMenu != rhs.cmdMenu) {
		this->cmdMenu.reset(rhs.cmdMenu.get());
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

main_window_core::MainWindowCore::MainWindowCore(main_window_core::MainWindowCore && rhs) :  mainWidget(std::exchange(rhs.mainWidget, Q_NULLPTR)), tabs(std::exchange(rhs.tabs, Q_NULLPTR)), topMenuBar(std::exchange(rhs.topMenuBar, Q_NULLPTR)), popup(std::exchange(rhs.popup, Q_NULLPTR)), bottomStatusBar(std::exchange(rhs.bottomStatusBar, Q_NULLPTR)), cmdMenu(std::exchange(rhs.cmdMenu, Q_NULLPTR)), mainWindowState(std::exchange(rhs.mainWindowState, main_window_shared_types::state_e::IDLE)), offsetType(std::exchange(rhs.offsetType, main_window_shared_types::offset_type_e::IDLE)), userText(std::exchange(rhs.userText, QString::null)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Move constructor main window core");
}

main_window_core::MainWindowCore & main_window_core::MainWindowCore::operator=(main_window_core::MainWindowCore && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Move assignment operator for main window core");

	if (&rhs != this) {
		this->mainWidget = std::move(rhs.mainWidget);
		rhs.mainWidget.reset();

		this->tabs = std::move(rhs.tabs);
		rhs.tabs.reset();

		this->topMenuBar = std::move(rhs.topMenuBar);
		rhs.topMenuBar.reset();

		this->popup = std::move(rhs.popup);
		rhs.popup.reset();

		this->bottomStatusBar = std::move(rhs.bottomStatusBar);
		rhs.bottomStatusBar.reset();

		this->cmdMenu = std::move(rhs.cmdMenu);
		rhs.cmdMenu.reset();

		this->mainWindowState = std::exchange(rhs.mainWindowState, main_window_shared_types::state_e::IDLE);
		this->offsetType = std::exchange(rhs.offsetType, main_window_shared_types::offset_type_e::IDLE);
		this->userText = std::exchange(rhs.userText, QString::null);
	}

	return *this;
}

main_window_core::MainWindowCore::~MainWindowCore() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core destructor");

	// Reset pointers
	this->cmdMenu.reset();
	this->bottomStatusBar.reset();

}

QString main_window_core::MainWindowCore::getActionName() const {
	QString actionNameText(QString::null);

	const QString actionName(global_qfunctions::qEnumToQString<main_window_shared_types::state_list>(this->mainWindowState, true));
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
