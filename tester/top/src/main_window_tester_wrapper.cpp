/**
 * @copyright
 * @file main_window_tester_wrapper.cpp
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Main Window tester wrapper functions
 */

#include <iostream>
// Qt libraries
#include <QtCore/QtGlobal>

#include "main_window_tester_wrapper.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTesterWrapperOverall, "mainWindowTesterWrapper.overall", MSG_TYPE_LEVEL)

main_window_tester_wrapper::MainWindowTesterWrapper::MainWindowTesterWrapper(QWidget * parent, Qt::WindowFlags flags) : main_window_wrapper::MainWindowWrapper(parent, flags) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTesterWrapperOverall,  "Main window tester wrapper constructor");

}

main_window_tester_wrapper::MainWindowTesterWrapper::MainWindowTesterWrapper(main_window_tester_wrapper::MainWindowTesterWrapper && rhs) : main_window_wrapper::MainWindowWrapper(std::move(rhs)) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTesterWrapperOverall,  "Move constructor main window tester wrapper");

}

main_window_tester_wrapper::MainWindowTesterWrapper & main_window_tester_wrapper::MainWindowTesterWrapper::operator=(main_window_tester_wrapper::MainWindowTesterWrapper && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTesterWrapperOverall,  "Move assignment operator for main window tester wrapper");

	main_window_wrapper::MainWindowWrapper::operator=(std::move(rhs));

	return *this;
}

main_window_tester_wrapper::MainWindowTesterWrapper::~MainWindowTesterWrapper() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTesterWrapperOverall,  "Main window tester wrapper destructor");
}

CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getPopupContainer, std::shared_ptr<main_window_popup_container::MainWindowPopupContainer> &, this->getWindowCore()->popup)
CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getWindowCtrl, std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> &, this->getWindow()->getCtrl())
CONST_GETTER(main_window_tester_wrapper::MainWindowTesterWrapper::getWindowCore, std::shared_ptr<main_window_core::MainWindowCore> &, this->getWindow()->getCore())

const std::shared_ptr<main_window_tab::MainWindowTab> main_window_tester_wrapper::MainWindowTesterWrapper::getCurrentTab() const {
	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->getWindowCore();
	const std::unique_ptr<main_window_tab_widget::MainWindowTabWidget> & tabWidget = windowCore->tabs;
	const int  & currentTabIndex = windowCore->getCurrentTabIndex();
	std::shared_ptr<main_window_tab::MainWindowTab> tab = nullptr;
	// Search tab only if the searched index is greater than 0 and the window has more than 1 tab
	if ((currentTabIndex >= 0) && (windowCore->getTabCount() > 0)) {
		tab = tabWidget->widget(currentTabIndex, true);
	}
	return tab;
}
