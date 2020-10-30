/**
 * @copyright
 * @file command_test.cpp
 * @author Andrea Gianarda
 * @date 08th October 2020
 * @brief Command test functions
 */

#include <QtTest/QTest>

#include "global_enums.h"
#include "global_constants.h"
#include "macros.h"
#include "qt_operator.h"
#include "stl_helper.h"
#include "main_window_constants.h"
#include "main_window_shared_functions.h"
#include "command_test.h"
#include "base_suite.h"

LOGGING_CONTEXT(commandTestOverall, commandTest.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandTestTest, commandTest.test, TYPE_LEVEL, INFO_VERBOSITY)

command_test::CommandTest::CommandTest(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const std::string & testName, const std::string & jsonFileName, const bool useShortcuts) : base_test::BaseTest(testSuite, (testName + " using " + (useShortcuts ? "shortcuts" : "full commands"))), main_window_json_action::MainWindowJsonAction(QString::fromStdString(jsonFileName)), sendCommandsThroughShortcuts(useShortcuts) {

	LOG_INFO(logger::info_level_e::ZERO, commandTestOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());

}

command_test::CommandTest::~CommandTest() {
	LOG_INFO(logger::info_level_e::ZERO, commandTestOverall,  "Test " << this->getName() << " destructor");
}

BASE_GETTER(command_test::CommandTest::commandSentThroughShortcuts, bool, this->sendCommandsThroughShortcuts)

void command_test::CommandTest::writeTextToStatusBar(const std::string & textToWrite, const std::string & expectedText, const main_window_shared_types::state_e & expectedState, const bool execute, const bool sendShortcut) {

	LOG_INFO(logger::info_level_e::ZERO, commandTestTest,  "Write " << textToWrite << " to statusbar");

	const std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> & windowCtrl =  this->windowWrapper->getWindowCtrl();
	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();

	QTest::KeyAction keyAction = QTest::KeyAction::Click;
	QWidget * widget = windowCtrl.get();
	// Send text characters one by one
	for (const auto & character : textToWrite) {
		QTest::keyEvent(keyAction, widget, character);
	}

	QApplication::processEvents(QEventLoop::AllEvents);

	const main_window_shared_types::state_e & currentStateBeforeExecution = windowCore->getMainWindowState();
	WAIT_FOR_CONDITION((currentStateBeforeExecution == expectedState), test_enums::error_type_e::WINDOW, "Expected window state " + expectedState + " doesn't match current window state " + currentStateBeforeExecution, 1000);

	const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
	ASSERT((expectedText.compare(textInLabel) == 0), test_enums::error_type_e::STATUSBAR, "Command sent " + expectedText + " doesn't match the command written in the user input label " + textInLabel);

	if (execute == true) {
		if (sendShortcut == false) {
			QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);
			QApplication::processEvents(QEventLoop::AllEvents);
		}

		const main_window_shared_types::state_e expectedStateAfterExecution = main_window_shared_types::state_e::IDLE;
		const main_window_shared_types::state_e & currentStateAfterExecution = windowCore->getMainWindowState();
		ASSERT((currentStateAfterExecution == expectedStateAfterExecution), test_enums::error_type_e::WINDOW, "Expected window state " + expectedStateAfterExecution + " doesn't match current window state " + currentStateAfterExecution);
	}
}

std::string command_test::CommandTest::commandNameToShownText(const std::string & commandName, const bool commandState) {
	const std::unique_ptr<main_window_json_data::MainWindowJsonData> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), test_enums::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getSourceFileName().toStdString());

	std::string commandExpectedText = std::string();
	if (commandData != nullptr) {
		// Long command that the user has to type is :<long_command>
		// It will be displayed as : <long_command>
		const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
		ASSERT((commandLongCmdPtr != nullptr), test_enums::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
		const std::string commandLongCmd(*commandLongCmdPtr);
		commandExpectedText = ": " + commandLongCmd;

		if (commandState == false) {
			const std::string commandNameSearchString("-");
			const std::string commandNameReplacingString(" ");
			// If typing the shortcuts, the status bar label prints : <long_command_without_dashes>
			commandExpectedText = stl_helper::findAndReplaceString(commandExpectedText, commandNameSearchString, commandNameReplacingString);
		}
	}

	return commandExpectedText;
}

void command_test::CommandTest::writeCommandToStatusBar(const std::string & commandName, const main_window_shared_types::state_e & expectedState, const bool execute) {

	const std::string commandToSend(this->commandNameToTypedText(commandName));
	const std::string commandExpectedText(this->commandNameToShownText(commandName, (this->commandSentThroughShortcuts() == false)));

	LOG_INFO(logger::info_level_e::ZERO, commandTestTest, "Type command " << commandName << " - text sent to statusbar: " << commandToSend);
	this->writeTextToStatusBar(commandToSend, commandExpectedText, expectedState, execute, this->sendCommandsThroughShortcuts);
}

void command_test::CommandTest::openNewTab(const std::string & search) {
	const std::string openCommandName("open new tab");
	this->makeSearchInTab(openCommandName, search);
}

void command_test::CommandTest::makeSearchInTab(const std::string & commandName, const std::string & search) {
	const std::shared_ptr<main_window_core::MainWindowCore> & windowCore = this->windowWrapper->getWindowCore();

	const std::string openCommandName("open new tab");

	const int initialNumberOfTabs = windowCore->getTabCount();
	int expectedNumberOfTabs = initialNumberOfTabs;
	if (commandName.compare(openCommandName) == 0) {
		expectedNumberOfTabs += 1;
	}

	this->executeCommand(commandName, search);

	WAIT_FOR_CONDITION((windowCore->getTabCount() == expectedNumberOfTabs), test_enums::error_type_e::TABS, "Number of tab mismatch after executing command " + commandName + " - actual number of tabs " + std::to_string(windowCore->getTabCount()) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs), 5000);

	const std::shared_ptr<main_window_tab::MainWindowTab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), test_enums::error_type_e::TABS, "Current tab pointer is null event though " + search + " has been searched.");
	if (currentTab != nullptr) {
		std::string expectedAuthority = std::string();
		std::string searchHostname(search);
		const std::string https(global_constants::https.toStdString());
		const std::string www(global_constants::www.toStdString());
		if (main_window_shared_functions::isUrl(QString::fromStdString(search)) == true) {
			std::size_t httpsPosition = searchHostname.find(https);
			const bool containsHttps = (httpsPosition != std::string::npos);
			if (containsHttps == true) {
				searchHostname.erase(httpsPosition, https.size());
			}
			const bool containsWww = (search.find(www) != std::string::npos);
			if (containsWww == false) {
				expectedAuthority += www;
			}
			expectedAuthority += searchHostname;
		} else if (main_window_shared_functions::isText(QString::fromStdString(search)) == true) {
			expectedAuthority = www + main_window_constants::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();
		} else {
			EXCEPTION_ACTION(throw, "Unable to deduce type of search " << search);
		}

		const QUrl & tabUrl = currentTab->getPage()->url();
		WAIT_FOR_CONDITION((expectedAuthority.compare(tabUrl.authority().toStdString()) == 0), test_enums::error_type_e::TABS, "Current URL authority " + tabUrl.authority().toStdString() + " doesn't match expected authority " + expectedAuthority, 5000);

		const std::string expectedTextInLabel = https + expectedAuthority;
		const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
		ASSERT((expectedTextInLabel.compare(textInLabel) == 0), test_enums::error_type_e::STATUSBAR, "Source of the content in tab " + expectedTextInLabel + " doesn't match the source of the content that the user requested to search " + textInLabel);
	}
}

std::string command_test::CommandTest::commandNameToTypedText(const std::string & commandName) {
	const std::unique_ptr<main_window_json_data::MainWindowJsonData> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), test_enums::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getSourceFileName().toStdString());

	std::string commandToSend = std::string();
	if (commandData != nullptr) {
		if (this->commandSentThroughShortcuts() == true) {
			const int * const commandShortcutPtr(static_cast<const int *>(commandData->getValueFromMemberName("Shortcut")));
			ASSERT((commandShortcutPtr != nullptr), test_enums::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
			int shortcut = *commandShortcutPtr;
			// In order to get the key of the shortcut, bitwise and with the negation of the modifier mask
			Qt::Key key = (Qt::Key)(shortcut & ~global_constants::qmodifierMask);
			QKeySequence sequence(key);
			commandToSend = sequence.toString().toStdString();
			// In order to get the modifier of the shortcut, bitwise and with the modifier mask
			Qt::KeyboardModifiers modifier = (Qt::KeyboardModifiers)(shortcut & global_constants::qmodifierMask);
			const bool hasShiftModifier = (modifier & Qt::ShiftModifier);
			if (hasShiftModifier == false) {
				std::transform(commandToSend.begin(), commandToSend.end(), commandToSend.begin(), [] (unsigned char c) {
					return std::tolower(c);
				});
			}
		} else {
			const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
			ASSERT((commandLongCmdPtr != nullptr), test_enums::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
			const std::string commandLongCmd(*commandLongCmdPtr);
			commandToSend = ":" + commandLongCmd;
		}
	}

	return commandToSend;
}

void command_test::CommandTest::executeCommand(const std::string & commandName, const std::string & argument) {

	const std::unique_ptr<main_window_json_data::MainWindowJsonData> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), test_enums::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getSourceFileName().toStdString());

	main_window_shared_types::state_e commandState = main_window_shared_types::state_e::UNKNOWN;
	if (commandData != nullptr) {
		const main_window_shared_types::state_e * const commandStatePtr(static_cast<const main_window_shared_types::state_e *>(commandData->getValueFromMemberName("State")));
		ASSERT((commandStatePtr != nullptr), test_enums::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
		commandState = *commandStatePtr;
	}

	main_window_shared_types::state_e commandExpectedState = main_window_shared_types::state_e::UNKNOWN;

	if (this->commandSentThroughShortcuts() == true) {
		if (argument.empty() == true) {
			commandExpectedState = main_window_shared_types::state_e::IDLE;
		} else {
			commandExpectedState = commandState;
		}
	} else {
		commandExpectedState = main_window_shared_types::state_e::COMMAND;
	}

	this->writeCommandToStatusBar(commandName, commandExpectedState, argument.empty());

	if (argument.empty() == false) {

		const std::string commandExpectedName(this->commandNameToShownText(commandName, false));
		const std::string argumentExpectedText = commandExpectedName + " " + argument;
		const main_window_shared_types::state_e argumentExpectedState = commandState;

		LOG_INFO(logger::info_level_e::ZERO, commandTestTest, "Give argument " << argument << " to command " << commandName);
		this->writeTextToStatusBar(argument, argumentExpectedText, argumentExpectedState, true, false);
	}

}
