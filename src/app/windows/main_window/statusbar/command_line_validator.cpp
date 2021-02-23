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


LOGGING_CONTEXT(commandLineValidatorOverall, commandLineValidator.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandLineValidatorUserInput, commandLineValidator.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::statusbar::CommandLineValidator::CommandLineValidator(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & windowCore) : QValidator(parent), core(windowCore) {

}

app::main_window::statusbar::CommandLineValidator::~CommandLineValidator() {

}

QValidator::State app::main_window::statusbar::CommandLineValidator::validate(QString & input, int & cursorPosition) const {
	QValidator::State state = QValidator::Invalid;
	QChar currentKey = input.at(cursorPosition);

	const app::main_window::state_e windowState = this->core->getMainWindowState();
	switch (windowState) {
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
		case app::main_window::state_e::FIND:
			if ((currentKey.isSpace() == true) || (currentKey.isPunct() == true) || (currentKey.isLetterOrNumber() == true)) {
				this->core->printUserInput(app::main_window::text_action_e::APPEND, event->text());
			}
			break;
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::REFRESH_TAB:
			if (currentKey.isDigit() == true) {
				state = QValidator::Acceptable;
			} else {
				LOG_WARNING(commandLineValidatorUserInput, "Pressed key " << event->text() << ". Only numbers are accepted when executing actions like closing windows or moving in the tab bar");
			}
			break;
		case app::main_window::state_e::MOVE_TAB:
			if (offsetType == app::shared::offset_type_e::IDLE) {
				// If no sign is provided, the tab is considered as absolute value
				// If + or - sign is provided, then the value is considered to be relative to the current tab
				// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
				// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
				if (currentKey.isDigit() == true) {
					this->core->setOffsetType(app::shared::offset_type_e::ABSOLUTE);
					this->core->printUserInput(app::main_window::text_action_e::CLEAR);
					state = QValidator::Acceptable;
				} else if ((currentKey.isNumber() == '+') || (currentKey.isNumber() == 'l')) {
					this->core->setOffsetType(app::shared::offset_type_e::RIGHT);
					this->core->printUserInput(app::main_window::text_action_e::CLEAR);
					state = QValidator::Acceptable;
				} else if ((currentKey.isNumber() == '-') || (currentKey.isNumber() == 'h')) {
					this->core->setOffsetType(app::shared::offset_type_e::LEFT);
					this->core->printUserInput(app::main_window::text_action_e::CLEAR);
					state = QValidator::Acceptable;
				} else {
					LOG_WARNING(commandLineValidatorUserInput, "Pressed key " << event->text() << ". Only numbers and + and - signs are accepted when executing actions like move tabs in the tab bar");
				}
			} else {
				if (currentKey.isDigit() == true) {
					state = QValidator::Acceptable;
				} else {
					LOG_WARNING(commandLineValidatorUserInput, "Pressed key " << event->text() << ". Only numbers accepted when executing actions like move tabs in the tab bar");
				}
			}
			break;
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, commandLineValidatorUserInput, "Window in state " << windowState << " Key pressed is " << event->text() << "(ID " << pressedKey << ")");
			break;
	}
	return state;
}
