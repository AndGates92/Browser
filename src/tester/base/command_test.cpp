/**
 * @copyright
 * @file command_test.cpp
 * @author Andrea Gianarda
 * @date 08th October 2020
 * @brief Command test functions
 */

#include <filesystem>

#include <QtTest/QTest>

#include "app/shared/enums.h"
#include "app/shared/constants.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/cpp/stl_helper.h"
#include "app/windows/main_window/window/core.h"
#include "app/windows/main_window/statusbar/status_bar.h"
#include "app/windows/main_window/popup/open_popup.h"
#include "app/windows/main_window/popup/popup_container.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/windows/main_window/tabs/web_engine_page.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/shared/shared_functions.h"
#include "tester/base/command_test.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(commandTestOverall, commandTest.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandTestTest, commandTest.test, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {
	namespace base {
		namespace command_test {
			/**
			 * @brief String with white-spaces as defiend by the current C locale:
			 * - ' ': space
			 * - \r: carriage return
			 * - \n: line feed
			 * - \t: horizontal tab
			 * - \v: vertical tab
			 * - \f: form feed
			 *
			 */
			static const std::string whiteSpaces(" \n\t\v\f\r");

			/**
			 * @brief Quit command name
			 *
			 */
			static const std::string openFileCommandName("open file");

			/**
			 * @brief Quit command name
			 *
			 */
			static const std::string quitCommandName("quit");

			/**
			 * @brief Find upward command name
			 *
			 */
			static const std::string findUpCommandName("find upward");

			/**
			 * @brief Find downward command name
			 *
			 */
			static const std::string findDownCommandName("find downward");

		}
	}
}

tester::base::CommandTest::CommandTest(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName, const std::string & jsonFileName, const bool useShortcuts) : tester::base::Test(testSuite, (testName + " using " + (useShortcuts ? "shortcuts" : "full commands"))), app::main_window::json::Action(jsonFileName), sendCommandsThroughShortcuts(useShortcuts) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandTestOverall,  "Creating test " << this->getName() << " in suite " << this->getSuite()->getName());

}

tester::base::CommandTest::~CommandTest() {
	LOG_INFO(app::logger::info_level_e::ZERO, commandTestOverall,  "Test " << this->getName() << " destructor");
}

BASE_GETTER(tester::base::CommandTest::commandSentThroughShortcuts, bool, this->sendCommandsThroughShortcuts)

void tester::base::CommandTest::checkStateAfterTypingText(const std::string & expectedText, const app::main_window::state_e & expectedState) {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const app::main_window::state_e & currentState = windowCore->getMainWindowState();
	WAIT_FOR_CONDITION((currentState == expectedState), tester::shared::error_type_e::WINDOW, "Expected window state " + expectedState + " doesn't match current window state " + currentState, 1000);

	std::string prunedExpectedText(app::utility::removeTrailingCharacter(expectedText, tester::base::command_test::whiteSpaces));
	const std::string textInLabel = windowCore->bottomStatusBar->getUserInputText().toStdString();
	std::string prunedTextInLabel(app::utility::removeTrailingCharacter(textInLabel, tester::base::command_test::whiteSpaces));
	ASSERT((prunedExpectedText.compare(prunedTextInLabel) == 0), tester::shared::error_type_e::STATUSBAR, "Command sent \"" + prunedExpectedText + "\" doesn't match the command written in the user input label \"" + prunedTextInLabel + "\"");
}

void tester::base::CommandTest::writeTextToStatusBar(const std::string & textToWrite, const std::string & expectedText, const app::main_window::state_e & expectedState, const bool execute, const bool pressEnter) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest,  "Write " << textToWrite << " to statusbar");

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

	QTest::KeyAction keyAction = QTest::KeyAction::Click;
	tester::base::CommandTest::sendKeyEventsToFocus(keyAction, textToWrite);

	this->checkStateAfterTypingText(expectedText, expectedState);

	if (execute == true) {
		if (pressEnter == true) {
			tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);
		}

		if (expectedState != app::main_window::state_e::OPEN_FILE) {
			const app::main_window::state_e expectedStateAfterExecution = app::main_window::state_e::IDLE;
			const app::main_window::state_e & currentStateAfterExecution = windowCore->getMainWindowState();
			ASSERT((currentStateAfterExecution == expectedStateAfterExecution), tester::shared::error_type_e::WINDOW, "Expected window state " + expectedStateAfterExecution + " doesn't match current window state " + currentStateAfterExecution);
		}
	}
}

bool tester::base::CommandTest::commandRequiresEnter(const std::string & commandName) const {
	return ((commandName.compare(tester::base::command_test::openFileCommandName) != 0) && (commandName.compare(tester::base::command_test::quitCommandName) != 0) && (commandName.compare(tester::base::command_test::findUpCommandName) != 0) && (commandName.compare(tester::base::command_test::findDownCommandName) != 0));
}

std::string tester::base::CommandTest::commandNameToShownText(const std::string & commandName, const bool commandAsTyped) {
	std::string commandExpectedText = std::string();

	const bool commandsPrintsText = ((commandName.compare(tester::base::command_test::openFileCommandName) == 0) || this->commandRequiresEnter(commandName));
	if (commandsPrintsText == true) {
		const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
		ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getActionJsonFilesAsString());

		if (commandData != nullptr) {
			// Long command that the user has to type is :<long_command>
			// It will be displayed as : <long_command>
			const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
			ASSERT((commandLongCmdPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
			const std::string commandLongCmd(*commandLongCmdPtr);
			commandExpectedText = ":";
			if (commandAsTyped == true) {
				commandExpectedText += " ";
			}
			commandExpectedText += commandLongCmd;

			if (commandAsTyped == false) {
				const std::string commandNameSearchString("-");
				const std::string commandNameReplacingString(" ");
				// If typing the shortcuts, the status bar label prints : <long_command_without_dashes>
				commandExpectedText = app::utility::findAndReplaceString(commandExpectedText, commandNameSearchString, commandNameReplacingString);
			}
		}
	}

	return commandExpectedText;
}

void tester::base::CommandTest::writeCommandToStatusBar(const std::string & commandName, const app::main_window::state_e & expectedState, const bool execute) {

	const std::string commandToSend(this->commandNameToTypedText(commandName));
	const std::string commandExpectedText(this->commandNameToShownText(commandName, (expectedState == app::main_window::state_e::COMMAND)));

	LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Type command " << commandName << " - text sent to statusbar: " << commandToSend);
	const bool commandRequiredEnter = this->commandRequiresEnter(commandName);
	const bool pressEnter = execute || (commandRequiredEnter && this->sendCommandsThroughShortcuts);

	// Send : to move to the command state
	if (this->commandSentThroughShortcuts() == false) {
		const std::string startCommandText(":");
		QTest::KeyAction keyAction = QTest::KeyAction::Click;
		tester::base::CommandTest::sendKeyEventsToFocus(keyAction, startCommandText);

		this->checkStateAfterTypingText(startCommandText, expectedState);
	}

	this->writeTextToStatusBar(commandToSend, commandExpectedText, expectedState, execute, pressEnter);
}

void tester::base::CommandTest::openNewTab(const std::string & search) {
	if (search.empty() == true) {
		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Open new tab to search engine");
	} else {
		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Open new tab searching " << search);
	}
	const std::string openCommandName("open new tab");
	this->makeSearchInTab(openCommandName, search);
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const int loadBarUpperBoundary = 70;
	WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getProgressValue() == loadBarUpperBoundary), tester::shared::error_type_e::STATUSBAR, "Progress bar didn't reach " + std::to_string(loadBarUpperBoundary) + " event though user sent command \"" + openCommandName + "\" and searched " + search, 5000);
	WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getLoadBarVisibility() == false), tester::shared::error_type_e::STATUSBAR, "Progress bar didn't change visibility to false", 5000);
}

void tester::base::CommandTest::openFile(const std::string & filepath) {
	const std::string openCommandName("open file");
	this->executeCommand(openCommandName, std::string());

	const std::shared_ptr<app::main_window::popup::PopupContainer> & popupContainer = this->windowWrapper->getPopupContainer();
	ASSERT((popupContainer != nullptr), tester::shared::error_type_e::POPUP, "Popup container pointer is null");
	std::shared_ptr<app::main_window::popup::OpenPopup> openFilePopup = popupContainer->getOpenFilePopup();
	ASSERT((openFilePopup != nullptr), tester::shared::error_type_e::POPUP, "Open file popup pointer is null");

	const std::filesystem::path file(filepath);
	ASSERT((std::filesystem::exists(file) == true), tester::shared::error_type_e::TEST, "Trying to open inexistent file " + filepath);

	if (openFilePopup != nullptr) {

		WAIT_FOR_CONDITION((openFilePopup->isVisible() == true), tester::shared::error_type_e::POPUP, "Open file popup is not visible even though command " + openCommandName + " was executed.", 5000);

		// Enable insert mode
		tester::base::CommandTest::sendKeyEventToFocus(QTest::KeyAction::Click, 'i');

		// Open file
		tester::base::CommandTest::sendKeyClicksToFocus(filepath);
		const std::string typedFilePath(openFilePopup->getTypedPath().toStdString());
		ASSERT((typedFilePath.compare(filepath) == 0), tester::shared::error_type_e::POPUP, "Typed filepath " + typedFilePath + " doesn't match expected filepath " + filepath);
		ASSERT((openFilePopup->isTypedPathAFile() == true), tester::shared::error_type_e::POPUP, "Typed filepath " + typedFilePath + " is not a file");

		// Open file
		if (this->commandSentThroughShortcuts() == true) {
			// Remove focus from QLineEdit
			tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Escape);
			tester::base::CommandTest::sendKeyEventToFocus(QTest::KeyAction::Click, 'o');
		} else {
			// Press enter while focus is still on the QLineEdit opens the file
			tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Enter);
		}
	}

	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	ASSERT((windowCore->getTabCount() == 1), tester::shared::error_type_e::TABS, "Opened file " + filepath + " in tab - actual number of tabs " + std::to_string(windowCore->getTabCount()));
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
		std::string currentUrl(tabUrl.toString().toStdString());
		std::size_t currentUrlHttpsPosition = currentUrl.find(https);
		const bool currentUrlContainsHttps = (currentUrlHttpsPosition != std::string::npos);
		if (currentUrlContainsHttps == true) {
			currentUrl.erase(currentUrlHttpsPosition, https.size());
		}
		WAIT_FOR_CONDITION((expectedAuthority.compare(currentUrl) == 0), tester::shared::error_type_e::TABS, "Current URL " + currentUrl + " doesn't match expected URL " + expectedAuthority, 5000);

		const std::string expectedTextInLabel = https + expectedAuthority;
		const std::string textInLabel = windowCore->bottomStatusBar->getContentPathText().toStdString();
		ASSERT((expectedTextInLabel.compare(textInLabel) == 0), tester::shared::error_type_e::STATUSBAR, "Source of the content in tab " + expectedTextInLabel + " doesn't match the source of the content that the user requested to search " + textInLabel);
	}
}

std::string tester::base::CommandTest::commandNameToTypedText(const std::string & commandName) {
	const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getActionJsonFilesAsString());

	std::string commandToSend = std::string();
	if (commandData != nullptr) {
		if (this->commandSentThroughShortcuts() == true) {
			const int * const commandShortcutPtr(static_cast<const int *>(commandData->getValueFromMemberName("Shortcut")));
			ASSERT((commandShortcutPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
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
			ASSERT((commandLongCmdPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
			const std::string commandLongCmd(*commandLongCmdPtr);
			commandToSend = commandLongCmd;
		}
	}

	return commandToSend;
}

void tester::base::CommandTest::executeCommand(const std::string & commandName, const std::string & argument) {

	const std::unique_ptr<app::main_window::json::Data> & commandData = this->findDataWithFieldValue("Name", &commandName);
	ASSERT((commandData != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find data with Name " + commandName + " in " + this->getActionJsonFilesAsString());

	app::main_window::state_e commandState = app::main_window::state_e::UNKNOWN;
	if (commandData != nullptr) {
		const app::main_window::state_e * const commandStatePtr(static_cast<const app::main_window::state_e *>(commandData->getValueFromMemberName("State")));
		ASSERT((commandStatePtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find shortcut for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
		commandState = *commandStatePtr;
	}

	app::main_window::state_e commandExpectedState = app::main_window::state_e::UNKNOWN;

	if (this->commandSentThroughShortcuts() == true) {
		const bool commandRequiredEnter = this->commandRequiresEnter(commandName);
		if ((commandName.compare(tester::base::command_test::openFileCommandName) == 0) || (commandRequiredEnter == true)) {
			commandExpectedState = commandState;
		} else {
			commandExpectedState = app::main_window::state_e::IDLE;
		}
	} else {
		commandExpectedState = app::main_window::state_e::COMMAND;
	}

	this->writeCommandToStatusBar(commandName, commandExpectedState, argument.empty());

	if (argument.empty() == false) {
		if (this->commandSentThroughShortcuts() == false) {
			// Send Space to window in order to change state
			tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Space);
			const std::string commandAfterStateChanged(this->commandNameToShownText(commandName, false));

			this->checkStateAfterTypingText(commandAfterStateChanged, commandState);
		}

		const std::string commandExpectedName(this->commandNameToShownText(commandName, false));
		const std::string argumentExpectedText = commandExpectedName + " " + argument;

		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Give argument " << argument << " to command " << commandName);
		this->writeTextToStatusBar(argument, argumentExpectedText, commandState, true, true);
	}

}
