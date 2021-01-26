/**
 * @copyright
 * @file main_window_wrapper.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Main Window tester wrapper functions
 */

#include <iostream>

#include "app/utility/logger/enums.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/windows/main_window/window/core.h"
#include "app/windows/main_window/window/main_window.h"
#include "app/windows/main_window/window/ctrl_wrapper.h"
#include "app/windows/main_window/tabs/tab_widget.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/windows/main_window/popup/popup_container.h"
#include "tester/top/main_window_wrapper.h"

// Categories
LOGGING_CONTEXT(mainWindowTesterWrapperOverall, mainWindowTesterWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::main_window_wrapper::MainWindowWrapper::MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags) : app::main_window::window::Wrapper(parent, flags) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall, "Main window tester wrapper constructor");

}

tester::main_window_wrapper::MainWindowWrapper::MainWindowWrapper(tester::main_window_wrapper::MainWindowWrapper && rhs) : app::main_window::window::Wrapper(std::move(rhs)) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall, "Move constructor main window tester wrapper");

}

tester::main_window_wrapper::MainWindowWrapper & tester::main_window_wrapper::MainWindowWrapper::operator=(tester::main_window_wrapper::MainWindowWrapper && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall, "Move assignment operator for main window tester wrapper");

	app::main_window::window::Wrapper::operator=(std::move(rhs));

	return *this;
}

tester::main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall, "Main window tester wrapper destructor");
}

CONST_GETTER(tester::main_window_wrapper::MainWindowWrapper::getPopupContainer, std::shared_ptr<app::main_window::popup::PopupContainer> &, this->getWindowCore()->popup)
CONST_GETTER(tester::main_window_wrapper::MainWindowWrapper::getWindowCtrl, std::unique_ptr<app::main_window::window::CtrlWrapper> &, this->getWindow()->getCtrl())
CONST_GETTER(tester::main_window_wrapper::MainWindowWrapper::getWindowCore, std::shared_ptr<app::main_window::window::Core> &, this->getWindow()->getCore())

const std::shared_ptr<app::main_window::tab::Tab> tester::main_window_wrapper::MainWindowWrapper::getCurrentTab() const {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->getWindowCore();
	const std::unique_ptr<app::main_window::tab::TabWidget> & tabWidget = windowCore->tabs;
	const int  & currentTabIndex = windowCore->getCurrentTabIndex();
	std::shared_ptr<app::main_window::tab::Tab> tab = nullptr;
	// Search tab only if the searched index is greater than 0 and the window has more than 1 tab
	if ((currentTabIndex >= 0) && (windowCore->getTabCount() > 0)) {
		tab = tabWidget->widget(currentTabIndex, true);
	}
	return tab;
}
