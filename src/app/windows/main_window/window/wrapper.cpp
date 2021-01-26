/**
 * @copyright
 * @file wrapper.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window wrapper functions
 */

#include "app/utility/logger/enums.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/windows/main_window/window/wrapper.h"
#include "app/windows/main_window/window/main_window.h"

// Categories
LOGGING_CONTEXT(mainWindowWrapperOverall, mainWindowWrapper.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::Wrapper::Wrapper(QWidget * parent, Qt::WindowFlags flags) : window(new app::main_window::window::MainWindow(parent, flags)) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWrapperOverall, "Main window wrapper constructor");

}

app::main_window::window::Wrapper::Wrapper(app::main_window::window::Wrapper && rhs) : window(std::exchange(rhs.window, Q_NULLPTR)) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWrapperOverall, "Move constructor main window wrapper");

}

app::main_window::window::Wrapper & app::main_window::window::Wrapper::operator=(app::main_window::window::Wrapper && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWrapperOverall, "Move assignment operator for main window wrapper");

	if (&rhs != this) {
		this->window = std::move(rhs.window);
		rhs.window.reset();
	}

	return *this;
}

app::main_window::window::Wrapper::~Wrapper() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWrapperOverall, "Main window wrapper destructor");
}

void app::main_window::window::Wrapper::show() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWrapperOverall, "Show main window");
	this->window->show();
}

CONST_GETTER(app::main_window::window::Wrapper::getWindow, std::unique_ptr<app::main_window::window::MainWindow> &, this->window)
