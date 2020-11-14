/**
 * @copyright
 * @file main_window_wrapper.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window wrapper functions
 */

#include <iostream>

#include "windows/main_window/window/include/main_window_wrapper.h"

// Categories
LOGGING_CONTEXT(mainWindowWrapperOverall, mainWindowWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags) : window(new main_window::MainWindow(parent, flags)) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper constructor");

}

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs) : window(std::exchange(rhs.window, Q_NULLPTR)) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWrapperOverall,  "Move constructor main window wrapper");

}

main_window_wrapper::MainWindowWrapper & main_window_wrapper::MainWindowWrapper::operator=(main_window_wrapper::MainWindowWrapper && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWrapperOverall,  "Move assignment operator for main window wrapper");

	if (&rhs != this) {
		this->window = std::move(rhs.window);
		rhs.window.reset();
	}

	return *this;
}

main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper destructor");
}

void main_window_wrapper::MainWindowWrapper::show() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWrapperOverall,  "Show main window");
	this->window->show();
}

CONST_GETTER(main_window_wrapper::MainWindowWrapper::getWindow, std::unique_ptr<main_window::MainWindow> &, this->window)
