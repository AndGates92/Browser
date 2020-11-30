/**
 * @copyright
 * @file main_window_tester_wrapper.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Main Window tester wrapper functions
 */

#include <iostream>

#include "tester/top/main_window_tester_wrapper.h"

// Categories
LOGGING_CONTEXT(mainWindowTesterWrapperOverall, mainWindowTesterWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_tester_wrapper::MainWindowTesterWrapper::MainWindowTesterWrapper(QWidget * parent, Qt::WindowFlags flags) : app::main_window::window::Wrapper(parent, flags) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Main window tester wrapper constructor");

}

main_window_tester_wrapper::MainWindowTesterWrapper::MainWindowTesterWrapper(main_window_tester_wrapper::MainWindowTesterWrapper && rhs) : app::main_window::window::Wrapper(std::move(rhs)) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Move constructor main window tester wrapper");

}

main_window_tester_wrapper::MainWindowTesterWrapper & main_window_tester_wrapper::MainWindowTesterWrapper::operator=(main_window_tester_wrapper::MainWindowTesterWrapper && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Move assignment operator for main window tester wrapper");

	app::main_window::window::Wrapper::operator=(std::move(rhs));

	return *this;
}

main_window_tester_wrapper::MainWindowTesterWrapper::~MainWindowTesterWrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Main window tester wrapper destructor");
}

CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getPopupContainer, std::shared_ptr<app::main_window::popup::PopupContainer> &, this->getWindowCore()->popup)
CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getWindowCtrl, std::unique_ptr<app::main_window::window::CtrlWrapper> &, this->getWindow()->getCtrl())
CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getWindowCore, std::shared_ptr<app::main_window::window::Core> &, this->getWindow()->getCore())

const std::shared_ptr<app::main_window::tab::Tab> main_window_tester_wrapper::MainWindowTesterWrapper::getCurrentTab() const {
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
