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

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags) : main_window_base::MainWindowBase(new main_window_core::MainWindowCore()), window(new main_window::MainWindow(this->windowCore, parent, flags)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper constructor");

}

main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper destructor");

	delete this->windowCore;
	delete this->window;

}

void main_window_wrapper::MainWindowWrapper::show() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Show main window");
	this->window->show();
}
