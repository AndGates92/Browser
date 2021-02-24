/**
 * @copyright
 * @file command_line_validator.cpp
 * @author Andrea Gianarda
 * @date 15th of February 2021
 * @brief Main Window command line validator functions
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/shared/setters_getters.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/windows/main_window/statusbar/command_line_validator.h"
#include "app/windows/main_window/window/core.h"


LOGGING_CONTEXT(commandLineValidatorOverall, commandLineValidator.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandLineValidatorUserInput, commandLineValidator.userInput, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::statusbar::CommandLineValidator::CommandLineValidator(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & windowCore) : QValidator(parent), core(windowCore) {

}

app::main_window::statusbar::CommandLineValidator::~CommandLineValidator() {

}

BASE_GETTER(app::main_window::statusbar::CommandLineValidator::getCore, std::shared_ptr<app::main_window::window::Core>, this->core.lock())

QValidator::State app::main_window::statusbar::CommandLineValidator::validate(QString & input, int & cursorPosition) const {
	QValidator::State state = QValidator::Invalid;
	auto windowCore = this->getCore();
	const auto offsetType = windowCore->getOffsetType();
	const app::main_window::state_e windowState = windowCore->getMainWindowState();

	const auto actionName = windowCore->getActionName();
	const bool foundCommandName = (input.contains(actionName) == true);
	int commandNameEndPosition = actionName.size();
	if (windowState != app::main_window::state_e::COMMAND) {
		// Add one to account for the first character ":"
		commandNameEndPosition += 1;
	}

	const auto commandArgument = windowCore->getUserText();

	bool commandArgumentValid = false;

	switch (windowState) {
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
		case app::main_window::state_e::FIND:
			if (commandArgument.isEmpty() == true) {
				commandArgumentValid = true;
			} else {
				commandArgumentValid = true;
				for (const auto & c : commandArgument) {
					commandArgumentValid &= ((c.isSpace() == true) || (c.isPunct() == true) || (c.isLetterOrNumber() == true));
				}
			}
			break;
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::REFRESH_TAB:
			if (commandArgument.isEmpty() == true) {
				commandArgumentValid = true;
			} else {
				commandArgumentValid = true;
				for (const auto & c : commandArgument) {
					commandArgumentValid &= (c.isDigit() == true);
				}
			}
			break;
		case app::main_window::state_e::MOVE_TAB:
			if (offsetType == app::shared::offset_type_e::IDLE) {
				// If no sign is provided, the tab is considered as absolute value
				// If + or - sign is provided, then the value is considered to be relative to the current tab
				// If key h is pressed, then the value is considered to be relative to the current tab and considered to go to the left
				// If key l is pressed, then the value is considered to be relative to the current tab and considered to go to the right
				bool absoluteMovement = true;
				for (const auto & c : commandArgument) {
					absoluteMovement &= (c.isDigit() == true);
				}

				bool leftMovement = false;
				bool rightMovement = false;

				if (commandArgument.size() == 1) {
					auto firstChar = commandArgument.front();
					leftMovement = ((firstChar == '+') || (firstChar == 'l'));
					leftMovement = ((firstChar == '-') || (firstChar == 'h'));
				}

				if (absoluteMovement == true) {
					windowCore->setOffsetType(app::shared::offset_type_e::ABSOLUTE);
					windowCore->printUserInput(app::main_window::text_action_e::CLEAR);
				} else if (rightMovement == true) {
					windowCore->setOffsetType(app::shared::offset_type_e::RIGHT);
					windowCore->printUserInput(app::main_window::text_action_e::CLEAR);
				} else if (leftMovement == true) {
					windowCore->setOffsetType(app::shared::offset_type_e::LEFT);
					windowCore->printUserInput(app::main_window::text_action_e::CLEAR);
				} else {
					LOG_WARNING(commandLineValidatorUserInput, "Command argument \"" << commandArgument << "\" is not valid while the offset type is " << offsetType << ". Only numbers and + and - signs are accepted while in state " << windowState);
				}

				commandArgumentValid = leftMovement || rightMovement || absoluteMovement;
			} else {
				if (commandArgument.isEmpty() == true) {
					commandArgumentValid = true;
				} else {
					commandArgumentValid = true;
					for (const auto & c : commandArgument) {
						commandArgumentValid &= (c.isDigit() == true);
					}
				}
			}
			break;
		default:
			LOG_INFO(app::logger::info_level_e::ZERO, commandLineValidatorUserInput, "Window in state " << windowState << " Command argument is \"" << commandArgument << "\".");
			break;
	}

	if ((commandArgumentValid == true) && (foundCommandName == true)) {
		state = QValidator::Acceptable;
	} else if ((commandArgumentValid == true) || (foundCommandName == true)) {
		state = QValidator::Intermediate;
	} else {
		state = QValidator::Invalid;
	}

	if (input.isEmpty() == true) {
		windowCore->setMainWindowState(app::main_window::state_e::IDLE);
	} else if ((windowState != app::main_window::state_e::COMMAND) && (foundCommandName == false)) {
		const auto commandNameEndPosition = input.indexOf(commandArgument);
		if (cursorPosition < commandNameEndPosition) {
			auto commandName = input.left(commandNameEndPosition - 1);

			// Delete first character (":")
			commandName = commandName.right(1);

			// Delete white spaces at the end of command name
			while(commandName.lastIndexOf(" ") == (commandName.size() - 1)) {
				commandName = commandName.left(1);
			}
			windowCore->updateUserInput(app::main_window::text_action_e::SET, commandName);
			windowCore->setMainWindowState(app::main_window::state_e::COMMAND);
		}

	} 

	return state;
}
