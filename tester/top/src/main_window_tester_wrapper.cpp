/**
 * @copyright
 * @file main_window_tester_wrapper.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Main Window tester wrapper functions
 */

#include <iostream>

#include "top/include/main_window_tester_wrapper.h"

// Categories
LOGGING_CONTEXT(mainWindowTesterWrapperOverall, mainWindowTesterWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_tester_wrapper::MainWindowTesterWrapper::MainWindowTesterWrapper(QWidget * parent, Qt::WindowFlags flags) : main_window::Wrapper(parent, flags) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Main window tester wrapper constructor");

}

main_window_tester_wrapper::MainWindowTesterWrapper::MainWindowTesterWrapper(main_window_tester_wrapper::MainWindowTesterWrapper && rhs) : main_window::Wrapper(std::move(rhs)) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Move constructor main window tester wrapper");

}

main_window_tester_wrapper::MainWindowTesterWrapper & main_window_tester_wrapper::MainWindowTesterWrapper::operator=(main_window_tester_wrapper::MainWindowTesterWrapper && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Move assignment operator for main window tester wrapper");

	main_window_wrapper::Wrapper::operator=(std::move(rhs));

	return *this;
}

main_window_tester_wrapper::MainWindowTesterWrapper::~MainWindowTesterWrapper() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTesterWrapperOverall,  "Main window tester wrapper destructor");
}

CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getPopupContainer, std::shared_ptr<main_window::PopupContainer> &, this->getWindowCore()->popup)
CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getWindowCtrl, std::unique_ptr<main_window::CtrlWrapper> &, this->getWindow()->getCtrl())
CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getWindowCore, std::shared_ptr<main_window::Core> &, this->getWindow()->getCore())

const std::shared_ptr<main_window::Tab> main_window_tester_wrapper::MainWindowTesterWrapper::getCurrentTab() const {
	const std::shared_ptr<main_window::Core> & windowCore = this->getWindowCore();
	const std::unique_ptr<main_window::TabWidget> & tabWidget = windowCore->tabs;
	const int  & currentTabIndex = windowCore->getCurrentTabIndex();
	std::shared_ptr<main_window::Tab> tab = nullptr;
	// Search tab only if the searched index is greater than 0 and the window has more than 1 tab
	if ((currentTabIndex >= 0) && (windowCore->getTabCount() > 0)) {
		tab = tabWidget->widget(currentTabIndex, true);
	}
	return tab;
}
