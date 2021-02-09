/**
 * @copyright
 * @file long_command_with_spaces.cpp
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Long command with spaces functions
 */

#include <QtTest/QTest>

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/windows/main_window/window/main_window.h"
#include "app/windows/main_window/json/data.h"
#include "tester/tests/long_command_with_spaces.h"
#include "tester/base/suite.h"

LOGGING_CONTEXT(longCommandWithSpacesOverall, longCommandWithSpaces.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(longCommandWithSpacesTest, longCommandWithSpaces.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace test {

		namespace long_command_with_spaces {

			namespace {

				/**
				 * @brief Path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonFilePath("json/");

				/**
				 * @brief Filename storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonFileName("global_commands.json");

				/**
				 * @brief Full path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonFileFullPath(jsonFilePath + jsonFileName);

			}

		}

	}

}

tester::test::LongCommandWithSpaces::LongCommandWithSpaces(const std::shared_ptr<tester::base::Suite> & testSuite, const bool withArgument) : tester::base::CommandTest(testSuite, ("Long command with spaces with " ((withArgument == true) ? (" argument" : "no arguments"))), tester::test::long_command_with_spaces::jsonFileFullPath, false) {
	LOG_INFO(app::logger::info_level_e::ZERO, longCommandWithSpacesOverall, "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());
}

tester::test::LongCommandWithSpaces::~LongCommandWithSpaces() {
	LOG_INFO(app::logger::info_level_e::ZERO, longCommandWithSpacesOverall, "Test " << this->getName() << " destructor");
}

void tester::test::LongCommandWithSpaces::testBody() {

	LOG_INFO(app::logger::info_level_e::ZERO, longCommandWithSpacesTest, "Starting test " << this->getName() << " in suite " << this->getSuite()->getName());

	const std::string commandName("open tab");
	std::string commandArgument = std::string();
	if (withArgument) {
		commandArgument = "test";
	}

	LOG_INFO(app::logger::info_level_e::ZERO, longCommandWithSpacesTest, "Executing command " << commandName << " with " << ((commandArgument.empty() == true) ? (" argument " + commandArgument) : "no arguments"));
	const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getActionJsonFilesAsString());

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	// Add spaces before moving to command state
	const std::string spaces("   ");
	const QTest::KeyAction keyAction = QTest::KeyAction::Click;
	tester::base::CommandTest::sendKeyEventsToFocus(keyAction, spaces);
	const std::string emptyText = std::string();
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const std::string textInLabelBeforeCommand = windowCore->bottomStatusBar->getUserInputText().toStdString();
	// Spaces should be ignored
	ASSERT((emptyText.compare(textInLabelBeforeCommand) == 0), tester::shared::error_type_e::STATUSBAR, "Expected text in command line \"" + emptyText + "\" doesn't match the text written in the user input label \"" + textInLabelBeforeCommand + "\". When the window is in state " + idleState + " spaces should be ignored.");
	const app::main_window::state_e idleState = app::main_window::state_e::IDLE;
	this->checkStateAfterTypingText(emptyText, idleState);

	// Send : to move to the command state
	const std::string startCommandText(":");
	tester::base::CommandTest::sendKeyEventsToFocus(keyAction, startCommandText);
	const app::main_window::state_e typingState = app::main_window::state_e::COMMAND;
	this->checkStateAfterTypingText(startCommandText, typingState);

	// Add spaces after moving to command state
	tester::base::CommandTest::sendKeyEventsToFocus(keyAction, spaces);
	const std::string textBeforeCommand = startCommandText + spaces;
	const std::string textInLabelBeforeCommandName = windowCore->bottomStatusBar->getUserInputText().toStdString();
	ASSERT((textBeforeCommandName.compare(textInLabelBeforeCommandName) == 0), tester::shared::error_type_e::STATUSBAR, "Expected text in the command line \"" + textBeforeCommandName + "\" doesn't match the text written in the user input label \"" + textInLabelBeforeCommandName + "\". After moving to the typing state " + typingState + " spaces should be allowed before start typing the full command name.");
	this->checkStateAfterTypingText(textBeforeCommandName, typingState);

	const std::string commandToSend(this->commandNameToTypedText(commandName));
	const auto longCmd = std::string();
	if (commandData != nullptr) {
		const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
		ASSERT((commandLongCmdPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
		longCmd = *commandLongCmdPtr;
	}
	const std::string commandExpectedText = textBeforeCommand + longCmd;

	// Write long command name to status bar
	LOG_INFO(app::logger::info_level_e::ZERO, longCommandWithSpacesTest, "Type command \"" << commandName << "\" - text sent to statusbar: \"" << commandToSend << "\"");
	LOG_INFO(app::logger::info_level_e::ZERO, longCommandWithSpacesTest, "Full text in command line: \"" << commandExpectedText << "\"");
	this->writeTextToStatusBar(commandToSend, commandExpectedText, typingState, false, false);

	// Send more spaces after finishing typing command
	// This moves the window to the actual command state
	tester::base::CommandTest::sendKeyEventsToFocus(keyAction, spaces);

	const std::string commandNameDisplayed(this->commandNameToShownText(commandName, false));
	app::main_window::state_e commandState = app::main_window::state_e::UNKNOWN;
	if (commandData != nullptr) {
		const app::main_window::state_e * const commandStatePtr(static_cast<const app::main_window::state_e *>(commandData->getValueFromMemberName("State")));
		ASSERT((commandStatePtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
		commandState = *commandStatePtr;
	}

	const std::string textAfterFinishingTypingCommand = commandNameDysplayed + spaces;
	this->checkStateAfterTypingText(textAfterFinishingTypingCommand, commandState);

	// Type argument and execute it if the argument is empty
	const bool executeAfterTypingArgument = commandArgument.empty();
	const std::string fullCommandLine = textAfterFinishingTypingCommand + commandArgument;
	this->writeTextToStatusBar(commandArgument, fullCommandLine, commandState, executeAfterTypingArgument, true);

	// If not executing the command add more spaces
	if (executeAfterTypingArgument == false) {
		tester::base::CommandTest::sendKeyEventsToFocus(keyAction, spaces);
		const std::string fullCommandLineWithSpaces = fullCommandLine + spaces;
		tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);
	}
}
