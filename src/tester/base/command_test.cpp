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
#include "app/windows/main_window/statusbar/bar.h"
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
			commandExpectedText = ":";
			if (commandAsTyped == true) {
				const std::string * const commandLongCmdPtr(static_cast<const std::string *>(commandData->getValueFromMemberName("LongCmd")));
				ASSERT((commandLongCmdPtr != nullptr), tester::shared::error_type_e::COMMAND, "Unable to find long command for data data with Name " + commandName + " in " + this->getActionJsonFilesAsString());
				const std::string commandLongCmd(*commandLongCmdPtr);
				commandExpectedText += " ";
				commandExpectedText += commandLongCmd;
			} else {
				const app::main_window::state_e * const commandStatePtr(static_cast<const app::main_window::state_e *>(commandData->getValueFromMemberName("State")));
				const std::string commandState(app::shared::qEnumToQString(*commandStatePtr, true).toStdString());
				std::string lowerCommandState = commandState;
				std::transform(lowerCommandState.begin(), lowerCommandState.end(), lowerCommandState.begin(), [] (unsigned char c) {
					return std::tolower(c);
				});
				commandExpectedText += lowerCommandState;

				const std::string commandNameSearchString("_");
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

	std::string expectedText = commandExpectedText;
	if (expectedState == app::main_window::state_e::EDIT_SEARCH) {
		expectedText += " ";
		const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
		expectedText += currentTab->getSearchText().toStdString();
	}

	this->writeTextToStatusBar(commandToSend, expectedText, expectedState, execute, pressEnter);
}

void tester::base::CommandTest::openNewTab(const std::string & search) {
	if (search.empty() == true) {
		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Open new tab to search engine " << app::shared::https << app::shared::www << app::main_window::defaultSearchEngine);
	} else {
		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Open new tab searching " << search);
	}
	const std::string openCommandName("open new tab");
	this->makeSearchInTab(openCommandName, search);
}

void tester::base::CommandTest::waitForTabOpened() {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getLoadBarVisibility() == true), tester::shared::error_type_e::STATUSBAR, "Progress bar didn't change visibility to true", 5000);
	const int loadBarUpperBoundary = 70;
	WAIT_FOR_CONDITION((windowCore->bottomStatusBar->getProgressValue() >= loadBarUpperBoundary), tester::shared::error_type_e::STATUSBAR, "Progress bar didn't reach " + std::to_string(loadBarUpperBoundary), 5000);
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

	this->waitForTabOpened();
	this->checkCurrentTab(search, expectedNumberOfTabs);
}

void tester::base::CommandTest::checkCurrentTab(const std::string & search, const int & expectedNumberOfTabs) {
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	WAIT_FOR_CONDITION((windowCore->getTabCount() == expectedNumberOfTabs), tester::shared::error_type_e::TABS, "Number of tab mismatch - actual number of tabs " + std::to_string(windowCore->getTabCount()) + " expected number of tabs is " + std::to_string(expectedNumberOfTabs), 5000);

	const std::shared_ptr<app::main_window::tab::Tab> currentTab = this->windowWrapper->getCurrentTab();
	ASSERT((currentTab != nullptr), tester::shared::error_type_e::TABS, "Current tab pointer is null event though " + search + " has been searched.");
	if (currentTab != nullptr) {
		this->checkSource(currentTab, search);
	}
}

void tester::base::CommandTest::checkSource(const std::shared_ptr<app::main_window::tab::Tab> & tab, const std::string & search) {
	std::string expectedSourceText = std::string();
	std::string searchHostname(search);
	const std::string www(app::shared::www.toStdString());

	app::main_window::page_type_e tabType = tab->getType();

	if (tabType == app::main_window::page_type_e::WEB_CONTENT) {
		ASSERT(((app::main_window::isUrl(QString::fromStdString(search)) == true) || (app::main_window::isText(QString::fromStdString(search)) == true)), tester::shared::error_type_e::TABS, "Search string " + search + " for tab of type " + tabType + " is not recognized neither as a URL or a text");
	} else if (tabType == app::main_window::page_type_e::TEXT) {
		ASSERT((app::main_window::isFile(QString::fromStdString(search)) == true), tester::shared::error_type_e::TABS, "Search string " + search + " for tab of type " + tabType + " is not recognized as a file path");
	} else {
		EXCEPTION_ACTION(throw, "Untreated case of tab of type " << tabType);
	}

	if (app::main_window::isUrl(QString::fromStdString(search)) == true) {
		const std::string https(app::shared::https.toStdString());

		std::size_t httpsPosition = searchHostname.find(https);
		const bool containsHttps = (httpsPosition != std::string::npos);
		// Erase https from searched text
		if (containsHttps == true) {
			searchHostname.erase(httpsPosition, https.size());
		}
		expectedSourceText = https;

		// Add www to searched text
		const bool containsWww = (search.find(www) != std::string::npos);
		if (containsWww == false) {
			expectedSourceText += www;
		}
		expectedSourceText += searchHostname;
		// expectedSourceText is the hostname (www.<domainName>.<domainSuffix>
	} else if (app::main_window::isText(QString::fromStdString(search)) == true) {
		std::string unprocessedAuthority = app::main_window::defaultSearchEngine.arg(QString::fromStdString(search)).toStdString();
		// Let Qt fix common mistakes in URL
		QUrl authority(QString::fromStdString(unprocessedAuthority), QUrl::TolerantMode);
		expectedSourceText = authority.url().toStdString();
	} else if (app::main_window::isFile(QString::fromStdString(search)) == true) {
		expectedSourceText += search;
	} else {
		EXCEPTION_ACTION(throw, "Unable to deduce type of search " << search);
	}

	std::string currentSource = std::string();
	if (tabType == app::main_window::page_type_e::WEB_CONTENT) {
		const QUrl & tabUrl = tab->getPage()->url();
		currentSource = tabUrl.toString().toStdString();
		ASSERT((tabUrl.isValid() == true), tester::shared::error_type_e::TABS, "The URL returned by the tab " + tabUrl.toString().toStdString() + " is not a valid URL");
		std::string tabUrlPath = std::string();
		std::string tabUrlHost = std::string();
		if (tabUrl.isValid() == true) {
			tabUrlPath = tabUrl.path(QUrl::FullyEncoded).toStdString();
			tabUrlHost = tabUrl.host(QUrl::FullyEncoded).toStdString();
			std::size_t wwwPosition = tabUrlHost.find(www);
			const bool containsWww = (wwwPosition != std::string::npos);
			// Erase https from searched text
			if (containsWww == true) {
				tabUrlHost.erase(wwwPosition, www.size());
			}
		} else {
			tabUrlPath = "Invalid tab URL";
			tabUrlHost = "Invalid tab URL";
		}
		const QUrl expectedUrl = QUrl(QString::fromStdString(expectedSourceText));
		ASSERT((expectedUrl.isValid() == true), tester::shared::error_type_e::TEST, "The expected source " + expectedSourceText + " is not a valid URL");
		std::string expectedUrlPath = std::string();
		std::string expectedUrlHost = std::string();
		if (expectedUrl.isValid() == true) {
			expectedUrlPath = expectedUrl.path(QUrl::FullyEncoded).toStdString();
			expectedUrlHost = expectedUrl.host(QUrl::FullyEncoded).toStdString();
			std::size_t wwwPosition = expectedUrlHost.find(www);
			const bool containsWww = (wwwPosition != std::string::npos);
			// Erase https from searched text
			if (containsWww == true) {
				expectedUrlHost.erase(wwwPosition, www.size());
			}
		} else {
			expectedUrlPath = "Invalid expected URL";
			expectedUrlHost = "Invalid expected URL";
		}
		ASSERT((tabUrlPath.find(expectedUrlPath) != std::string::npos), tester::shared::error_type_e::TABS, "Current path " + tabUrlPath + " of URL " + currentSource + " opened in tab doesn't contain path " + expectedUrlPath + " of the expected URL " + expectedSourceText);
		ASSERT((tabUrlHost.find(expectedUrlHost) != std::string::npos), tester::shared::error_type_e::TABS, "Current host " + tabUrlHost + " of URL " + currentSource + " opened in tab doesn't contain host " + expectedUrlHost + " of the expected URL " + expectedSourceText);
	} else if (tabType == app::main_window::page_type_e::TEXT) {
		currentSource = tab->getSource().toStdString();
		WAIT_FOR_CONDITION((expectedSourceText.compare(currentSource) == 0), tester::shared::error_type_e::TABS, "Current source " + currentSource + " doesn't match expected source " + expectedSourceText, 5000);
	}

	std::string expectedTextInLabel = std::string();
	if ((app::main_window::isUrl(QString::fromStdString(search)) == true) || (app::main_window::isText(QString::fromStdString(search)) == true)) {
		expectedTextInLabel = currentSource;
	} else if (app::main_window::isFile(QString::fromStdString(search)) == true) {
		const std::string filePrefix(app::main_window::filePrefix.toStdString());
		expectedTextInLabel = filePrefix + currentSource;
	}

	if (tabType == app::main_window::page_type_e::WEB_CONTENT) {
		const QUrl & tabUrl = tab->getPage()->url();
	}
	const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();
	const std::string textInLabel = windowCore->bottomStatusBar->getContentPathText().toStdString();
	ASSERT((expectedTextInLabel.compare(textInLabel) == 0), tester::shared::error_type_e::STATUSBAR, "Source of the content in tab " + expectedTextInLabel + " doesn't match the source of the content that the user requested to search " + textInLabel);
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

bool tester::base::CommandTest::stateRequiresArgument(const app::main_window::state_e & state) const {
	bool required = false;

	switch (state) {
		case app::main_window::state_e::IDLE:
		case app::main_window::state_e::QUIT:
		case app::main_window::state_e::TOGGLE_MENUBAR:
		case app::main_window::state_e::OPEN_FILE:
		case app::main_window::state_e::REFRESH_TAB:
		case app::main_window::state_e::FIND_DOWN:
		case app::main_window::state_e::FIND_UP:
		case app::main_window::state_e::SCROLL_UP:
		case app::main_window::state_e::SCROLL_DOWN:
		case app::main_window::state_e::HISTORY_PREV:
		case app::main_window::state_e::HISTORY_NEXT:
		case app::main_window::state_e::OPEN_TAB:
		case app::main_window::state_e::CLOSE_TAB:
		case app::main_window::state_e::MOVE_RIGHT:
		case app::main_window::state_e::MOVE_LEFT:
		case app::main_window::state_e::MOVE_TAB:
			required = false;
			break;
		case app::main_window::state_e::COMMAND:

		case app::main_window::state_e::FIND:
		case app::main_window::state_e::NEW_SEARCH:
		case app::main_window::state_e::EDIT_SEARCH:
			required = true;
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to determine whether state " << state << " requires an argument");
			break;
	}

	return required;
}

void tester::base::CommandTest::executeCommand(const std::string & commandName, const std::string & argument, const bool execute) {

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

	const bool executeCommand = ((this->stateRequiresArgument(commandExpectedState) == false) && (argument.empty() == true));
	this->writeCommandToStatusBar(commandName, commandExpectedState, executeCommand);

	if (argument.empty() == false) {
		if (this->commandSentThroughShortcuts() == false) {
			// Send Space to window in order to change state
			tester::base::CommandTest::sendKeyClickToFocus(Qt::Key_Space);
			const std::string commandAfterStateChanged(this->commandNameToShownText(commandName, false));
			const std::string expectedText = commandAfterStateChanged;

			this->checkStateAfterTypingText(expectedText, commandState);
		}

		const std::string commandExpectedName(this->commandNameToShownText(commandName, false));
		const std::string argumentExpectedText = commandExpectedName + " " + argument;

		LOG_INFO(app::logger::info_level_e::ZERO, commandTestTest, "Give argument " << argument << " to command " << commandName);
		this->writeTextToStatusBar(argument, argumentExpectedText, commandState, execute, true);
	}

}
