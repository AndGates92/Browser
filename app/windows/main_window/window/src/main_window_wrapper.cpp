/**
 * @copyright
 * @file main_window_wrapper.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window wrapper functions
 */

#include <iostream>
// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "main_window_wrapper.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWrapperOverall, "mainWindowWrapper.overall", MSG_TYPE_LEVEL)

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags) : window(new main_window::MainWindow(parent, flags)) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper constructor");

}

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs) : window(std::exchange(rhs.window, Q_NULLPTR)) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Move constructor main window wrapper");

}

main_window_wrapper::MainWindowWrapper & main_window_wrapper::MainWindowWrapper::operator=(main_window_wrapper::MainWindowWrapper && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Move assignment operator for main window wrapper");

	if (&rhs != this) {
		this->window = std::move(rhs.window);
		rhs.window.reset();
	}

	return *this;
}

main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper destructor");
}

void main_window_wrapper::MainWindowWrapper::show() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Show main window");
	this->window->show();
}
