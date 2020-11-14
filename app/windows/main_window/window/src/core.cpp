/**
 * @copyright
 * @file core.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window core functions
 */

#include <iostream>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/exception_macros.h"
#include "common/include/global_qfunctions.h"
#include "common/include/function_macros.h"
#include "windows/main_window/window/include/core.h"

// Categories
LOGGING_CONTEXT(mainWindowCoreOverall, mainWindowCore.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowCoreUserInput, mainWindowCore.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::Core::Core(QWidget * parent) : mainWidget(new QWidget(parent)), tabs(new app::main_window::tab::TabWidget(parent)), topMenuBar(new app::main_window::menu::MenuBar(parent)), popup(new app::main_window::popup::PopupContainer(parent)), bottomStatusBar(new app::main_window::status_bar::StatusBar(parent)), cmdMenu(new app::command_menu::CommandMenu(parent)), mainWindowState(app::main_window::state_e::IDLE), offsetType(app::shared::offset_type_e::IDLE), userText(QString()) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCoreOverall,  "Main window core constructor");
	this->topMenuBar->createMenus();
}

app::main_window::window::Core::Core(app::main_window::window::Core && rhs) :  mainWidget(std::exchange(rhs.mainWidget, Q_NULLPTR)), tabs(std::exchange(rhs.tabs, Q_NULLPTR)), topMenuBar(std::exchange(rhs.topMenuBar, Q_NULLPTR)), popup(std::exchange(rhs.popup, Q_NULLPTR)), bottomStatusBar(std::exchange(rhs.bottomStatusBar, Q_NULLPTR)), cmdMenu(std::exchange(rhs.cmdMenu, Q_NULLPTR)), mainWindowState(std::exchange(rhs.mainWindowState, app::main_window::state_e::IDLE)), offsetType(std::exchange(rhs.offsetType, app::shared::offset_type_e::IDLE)), userText(std::exchange(rhs.userText, QString())) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCoreOverall,  "Move constructor main window core");
}

app::main_window::window::Core & app::main_window::window::Core::operator=(app::main_window::window::Core && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCoreOverall,  "Move assignment operator for main window core");

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

		this->mainWindowState = std::exchange(rhs.mainWindowState, app::main_window::state_e::IDLE);
		this->offsetType = std::exchange(rhs.offsetType, app::shared::offset_type_e::IDLE);
		this->userText = std::exchange(rhs.userText, QString());
	}

	return *this;
}

app::main_window::window::Core::~Core() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCoreOverall,  "Main window core destructor");

	// Reset pointers
	this->cmdMenu.reset();
	this->bottomStatusBar.reset();

}

const QString app::main_window::window::Core::getActionName() const {
	QString actionNameText = QString();

	const QString actionName(app::shared::qEnumToQString<app::main_window::state_list>(this->mainWindowState, true));
	actionNameText.append(actionName);

	if (this->mainWindowState == app::main_window::state_e::MOVE_TAB) {
		if (this->offsetType == app::shared::offset_type_e::RIGHT) {
			actionNameText.append(" right");
		} else if (this->offsetType == app::shared::offset_type_e::LEFT) {
			actionNameText.append(" left");
		}
	}

	// Create lowercase copy of the string
	actionNameText = actionNameText.toLower();
	actionNameText = actionNameText.replace(QChar('_'), QChar(' '), Qt::CaseInsensitive);

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCoreUserInput,  "State " << this->mainWindowState << " action text " << actionNameText);

	return actionNameText;
}

BASE_GETTER(app::main_window::window::Core::getTabCount, int, this->tabs->count())
BASE_GETTER(app::main_window::window::Core::getCurrentTabIndex, int, this->tabs->currentIndex())
CONST_SETTER_GETTER(app::main_window::window::Core::setMainWindowState, app::main_window::window::Core::getMainWindowState, app::main_window::state_e &, this->mainWindowState)
CONST_SETTER_GETTER(app::main_window::window::Core::setOffsetType, app::main_window::window::Core::getOffsetType, app::shared::offset_type_e &, this->offsetType)
CONST_GETTER(app::main_window::window::Core::getUserText, QString &, this->userText)

void app::main_window::window::Core::updateUserInput(const app::main_window::text_action_e & action, const QString & text) {

	switch (action) {
		case app::main_window::text_action_e::SET:
			this->userText.clear();
			this->userText.append(text);
			break;
		case app::main_window::text_action_e::APPEND:
			this->userText.append(text);
			break;
		case app::main_window::text_action_e::CLEAR:
			this->userText.clear();
			break;
		default:
			EXCEPTION_ACTION(throw, "Unknown action " << action);
			break;
	}
}
