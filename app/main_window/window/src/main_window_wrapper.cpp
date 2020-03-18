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

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags) : main_window_base::MainWindowBase(std::shared_ptr<main_window_core::MainWindowCore>(std::make_shared<main_window_core::MainWindowCore>())), window(std::make_unique<main_window::MainWindow>(this->windowCore, parent, flags)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper constructor");

}

main_window_wrapper::MainWindowWrapper::MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs) : main_window_base::MainWindowBase(std::move(rhs)), window(std::move(rhs.window)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Move constructor main window wrapper");

	// Reset rhs
	rhs.window = Q_NULLPTR;
}

main_window_wrapper::MainWindowWrapper & main_window_wrapper::MainWindowWrapper::operator=(main_window_wrapper::MainWindowWrapper && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Move assignment operator for main window wrapper");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->window != rhs.window) {
		if (this->window != Q_NULLPTR) {
			this->window.reset(nullptr);
		}
		this->window = std::move(rhs.window);
	}
	rhs.window = Q_NULLPTR;

	this->main_window_base::MainWindowBase::operator=(rhs);

	return *this;
}

main_window_wrapper::MainWindowWrapper::~MainWindowWrapper() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Main window wrapper destructor");

	this->window.reset(nullptr);

}

void main_window_wrapper::MainWindowWrapper::show() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWrapperOverall,  "Show main window");
	this->window->show();
}
