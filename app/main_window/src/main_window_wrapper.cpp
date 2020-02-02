/**
 * @copyright
 * @file main_window_wrapper.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window wrapper functions
 */

#include <iostream>
// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "main_window_wrapper.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWrapperOverall, "mainWindowWrapper.overall", MSG_TYPE_LEVEL)

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags) : mainWindowCore(new main_window_core::MainWindowCore()), window(new main_window::MainWindow(this->mainWindowCore, parent, flags)),  ctrl(new main_window_ctrl::MainWindowCtrl(this->mainWindowCore, parent)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper constructor");

	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window_wrapper::MainWindowWrapper::close);
}

main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper destructor");

	delete this->mainWindowCore;
	delete this->window;
	delete this->ctrl;

}

void main_window_wrapper::MainWindowWrapper::show() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Show main window");
	this->window->show();
}

void main_window_wrapper::MainWindowWrapper::close() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Close main window");
	bool success = this->window->close();
	Q_ASSERT_X(success, "main window close", "Main window close request was not handled properly");
}
