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

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper constructor");

}

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(const main_window_wrapper::MainWindowWrapper & rhs) : window(Q_NULLPTR) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Copy constructor main window wrapper");

	this->window.reset(rhs.window.get());

}
main_window_wrapper::MainWindowWrapper & main_window_wrapper::MainWindowWrapper::operator=(const main_window_wrapper::MainWindowWrapper & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Copy assignment operator for main window wrapper");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->window != rhs.window) {
		this->window.reset(rhs.window.get());
	}

	return *this;
}

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs) : window(std::exchange(rhs.window, Q_NULLPTR)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Move constructor main window wrapper");

}

main_window_wrapper::MainWindowWrapper & main_window_wrapper::MainWindowWrapper::operator=(main_window_wrapper::MainWindowWrapper && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Move assignment operator for main window wrapper");

	if (&rhs != this) {
		this->window = std::move(rhs.window);
		rhs.window.reset();
	}

	return *this;
}

main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper destructor");
}

void main_window_wrapper::MainWindowWrapper::show() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Show main window");
	this->window->show();
}
