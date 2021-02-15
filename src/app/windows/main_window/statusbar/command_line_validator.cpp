/**
 * @copyright
 * @file command_line_validator.cpp
 * @author Andrea Gianarda
 * @date 15th of February 2021
 * @brief Main Window command line validator functions
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/windows/main_window/statusbar/command_line_validator.h"
#include "app/windows/main_window/window/core.h"

app::main_window::statusbar::CommandLineValidator::CommandLineValidator(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & windowCore) : QValidator(parent), core(windowCore) {

}

app::main_window::statusbar::CommandLineValidator::~CommandLineValidator() {

}

QValidator::State app::main_window::statusbar::CommandLineValidator::validate(QString & input, int & cursorPosition) {
	return QValidator::Acceptable;
}
