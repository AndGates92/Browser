/**
 * @copyright
 * @file command_test.cpp
 * @author Andrea Gianarda
 * @date 08th October 2020
 * @brief Command test functions
 */

#include <QtTest/QTest>

#include "app/shared/enums.h"
#include "app/shared/constants.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/stl/stl_helper.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/shared/shared_functions.h"
#include "tester/base/command_test.h"
#include "tester/base/suite.h"

LOGGING_CONTEXT(commandTestOverall, commandTest.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandTestTest, commandTest.test, TYPE_LEVEL, INFO_VERBOSITY)

tester::base::CommandTest::CommandTest(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName, const std::string & jsonFileName, const bool useShortcuts) : tester::base::Test(testSuite, (testName + " using " + (useShortcuts ? "shortcuts" : "full commands"))), app::main_window::json::Action(QString::fromStdString(jsonFileName)), sendCommandsThroughShortcuts(useShortcuts) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandTestOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());

}

tester::base::CommandTest::~CommandTest() {
	LOG_INFO(app::logger::info_level_e::ZERO, commandTestOverall,  "Test " << this->getName() << " destructor");
}

BASE_GETTER(tester::base::CommandTest::commandSentThroughShortcuts, bool, this->sendCommandsThroughShortcuts)

void tester::base::CommandTest::writeTextToStatusBar(const std::string & textToWrite, const std::string & expectedText, const app::main_window::state_e & expectedState, const bool execute, const bool sendShortcut) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest,  "Write " << textToWrite << " to statusbar");

	const std::unique_ptr<app::main_window::window::CtrlWrapper> & windowCtrl =  this->windowWrapper->getWindowCtrl();
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	QTest::KeyAction keyAction = QTest::KeyAction::Click;
	QWidget * widget = windowCtrl.get();
	// Send text characters one by one
	for (const auto & character : textToWrite) {
		QTest::keyEvent(keyAction, widget, character);
	}

	QApplication::processEvents(QEventLoop::AllEvents);

	const app::main_window::state_e & currentStateBeforeExecution = windowCore->getMainWindowState();
	WAIT_FOR_CONDITION((currentStateBeforeExecution == expectedState), tester::shared::error_type_e::WINDOW, "Expected window state " + expectedState + " doesn't match current window state " + currentStateBeforeExecution, 1000);

	const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
	ASSERT((expectedText.compare(textInLabel) == 0), tester::shared::error_type_e::STATUSBAR, "Command sent " + expectedText + " doesn't match the command written in the user input label " + textInLabel);

	if (execute == true) {
		if (sendShortcut == false) {
			QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);
			QApplication::processEvents(QEventLoop::AllEvents);
		}

		const app::main_window::state_e expectedStateAfterExecution = app::main_window::state_e::IDLE;
		const app::main_window::state_e & currentStateAfterExecution = windowCore->getMainWindowState();
		ASSERT((currentStateAfterExecution == expectedStateAfterExecution), tester::shared::error_type_e::WINDOW, "Expected window state " + expectedStateAfterExecution + " doesn't match current window state " + currentStateAfterExecution);
	}
}

std::string tester::base::CommandTest::commandNameToShownText(const std::string & commandName, const bool commandState) {
	const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getSourceFileName().toStdString());

	std::string commandExpectedText = std::string();
	if (commandData != nullptr) {
		// Long command that the user has to type is :<long_command>
		// It will be displayed as : <long_command>
		const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
		ASSERT((commandLongCmdPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
		const std::string commandLongCmd(*commandLongCmdPtr);
		commandExpectedText = ": " + commandLongCmd;

		if (commandState == false) {
			const std::string commandNameSearchString("-");
			const std::string commandNameReplacingString(" ");
			// If typing the shortcuts, the status bar label prints : <long_command_without_dashes>
			commandExpectedText = app::utility::findAndReplaceString(commandExpectedText, commandNameSearchString, commandNameReplacingString);
		}
	}

	return commandExpectedText;
}

void tester::base::CommandTest::writeCommandToStatusBar(const std::string & commandName, const app::main_window::state_e & expectedState, const bool execute) {

	const std::string commandToSend(this->commandNameToTypedText(commandName));
	const std::string commandExpectedText(this->commandNameToShownText(commandName, (this->commandSentThroughShortcuts() == false)));

	LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Type command " << commandName << " - text sent to statusbar: " << commandToSend);
	this->writeTextToStatusBar(commandToSend, commandExpectedText, expectedState, execute, this->sendCommandsThroughShortcuts);
}

void tester::base::CommandTest::openNewTab(const std::string & search) {
	const std::string openCommandName("open new tab");
	this->makeSearchInTab(openCommandName, search);
}

void tester::base::CommandTest::makeSearchInTab(const std::string & commandName, const std::string & search) {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	const std::string openCommandName("open new tab");

	const int initialNumberOfTabs = windowCore->getTabCount();
	int expectedNumberOfTabs = initialNumberOfTabs;
	if (commandName.compare(openCommandName) == 0) {
		expectedNumberOfTabs += 1;
	}

	this->executeCommand(commandName, search);

	WAIT_FOR_CONDITION((windowCore->getTabCount() == expectedNumberOfTabs), tester::shared::error_type_e::TABS, "Number of tab mismatch after executing command " + commandName + " - actual number of tabs " + std::to_string(windowCore->getTabCount()) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs), 5000);

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though " + search + " has been searched.");
	if (currentTab != nullptr) {
		std::string expectedAuthority = std::string();
		std::string searchHostname(search);
		const std::string https(app::shared::https.toStdString());
		const std::string www(app::shared::www.toStdString());
		if (app::main_window::isUrl(QString::fromStdString(search)) == true) {
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
		} else if (app::main_window::isText(QString::fromStdString(search)) == true) {
			expectedAuthority = www + app::main_window::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();
		} else {
			EXCEPTION_ACTION(throw, "Unable to deduce type of search " << search);
		}

		const QUrl & tabUrl = currentTab->getPage()->url();
		WAIT_FOR_CONDITION((expectedAuthority.compare(tabUrl.authority().toStdString()) == 0), tester::shared::error_type_e::TABS, "Current URL authority " + tabUrl.authority().toStdString() + " doesn't match expected authority " + expectedAuthority, 5000);

		const std::string expectedTextInLabel = https + expectedAuthority;
		const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
		ASSERT((expectedTextInLabel.compare(textInLabel) == 0), tester::shared::error_type_e::STATUSBAR, "Source of the content in tab " + expectedTextInLabel + " doesn't match the source of the content that the user requested to search " + textInLabel);
	}
}

std::string tester::base::CommandTest::commandNameToTypedText(const std::string & commandName) {
	const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getSourceFileName().toStdString());

	std::string commandToSend = std::string();
	if (commandData != nullptr) {
		if (this->commandSentThroughShortcuts() == true) {
			const int * const commandShortcutPtr(static_cast<const int *>(commandData->getValueFromMemberName("Shortcut")));
			ASSERT((commandShortcutPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
			int shortcut = *commandShortcutPtr;
			// In order to get the key of the shortcut, bitwise and with the negation of the modifier mask
			Qt::Key key = (Qt::Key)(shortcut & ~app::shared::qmodifierMask);
			QKeySequence sequence(key);
			commandToSend = sequence.toString().toStdString();
			// In order to get the modifier of the shortcut, bitwise and with the modifier mask
			Qt::KeyboardModifiers modifier = (Qt::KeyboardModifiers)(shortcut & app::shared::qmodifierMask);
			const bool hasShiftModifier = (modifier & Qt::ShiftModifier);
			if (hasShiftModifier == false) {
				std::transform(commandToSend.begin(), commandToSend.end(), commandToSend.begin(), [] (unsigned char c) {
					return std::tolower(c);
				});
			}
		} else {
			const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
			ASSERT((commandLongCmdPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
			const std::string commandLongCmd(*commandLongCmdPtr);
			commandToSend = ":" + commandLongCmd;
		}
	}

	return commandToSend;
}

void tester::base::CommandTest::executeCommand(const std::string & commandName, const std::string & argument) {

	const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getSourceFileName().toStdString());

	app::main_window::state_e commandState = app::main_window::state_e::UNKNOWN;
	if (commandData != nullptr) {
		const app::main_window::state_e * const commandStatePtr(static_cast<const app::main_window::state_e *>(commandData->getValueFromMemberName("State")));
		ASSERT((commandStatePtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getSourceFileName().toStdString());
		commandState = *commandStatePtr;
	}

	app::main_window::state_e commandExpectedState = app::main_window::state_e::UNKNOWN;

	if (this->commandSentThroughShortcuts() == true) {
		if (argument.empty() == true) {
			commandExpectedState = app::main_window::state_e::IDLE;
		} else {
			commandExpectedState = commandState;
		}
	} else {
		commandExpectedState = app::main_window::state_e::COMMAND;
	}

	this->writeCommandToStatusBar(commandName, commandExpectedState, argument.empty());

	if (argument.empty() == false) {

		const std::string commandExpectedName(this->commandNameToShownText(commandName, false));
		const std::string argumentExpectedText = commandExpectedName + " " + argument;
		const app::main_window::state_e argumentExpectedState = commandState;

		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Give argument " << argument << " to command " << commandName);
		this->writeTextToStatusBar(argument, argumentExpectedText, argumentExpectedState, true, false);
	}

}
