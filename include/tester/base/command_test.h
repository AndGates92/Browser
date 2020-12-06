#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H
/**
 * @copyright
 * @file command_test.h
 * @author Andrea Gianarda
 * @date 08th October 2020
 * @brief Command test header file
 */

#include "app/windows/main_window/json/action.h"
#include "tester/base/test.h"

/** @defgroup TesterBaseGroup Tester Base Doxygen Group
 *  Tester Base functions and classes
 *  @{
 */

namespace tester {

	namespace base {

		/**
		 * @brief CommandTest class
		 *
		 */
		class CommandTest : public tester::base::Test, public app::main_window::json::Action {

			public:
				/**
				 * @brief Function: bool commandSentThroughShortcuts() const
				 *
				 * \return boolean to stae whether commands are sent through shortcuts
				 *
				 * This function returns a boolean to indicate whtehr commands are sent throught shortcuts or through full command
				 */
				bool commandSentThroughShortcuts() const;

			protected:

				/**
				 * @brief Function: explicit CommandTest(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName, const std::string & jsonFileName, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param testName: name of the test
				 * \param jsonFileName: JSON filename
				 * \param useShortcuts: test uses shortcuts to send commands
				 *
				 * Command test constructor
				 */
				explicit CommandTest(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName, const std::string & jsonFileName, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~CommandTest()
				 *
				 * Command test destructor
				 */
				virtual ~CommandTest();

				/**
				 * @brief Function: makeSearchInTab(const std::string & commandName, const std::string & search = std::string())
				 *
				 * \param commandName: command releated to the search
				 * \param search: text of the search
				 *
				 * This function makes a search in a tab and loads the search provided as an argument. If argument search is empty, then the default tab will be opened
				 */
				void makeSearchInTab(const std::string & commandName, const std::string & search = std::string());

				/**
				 * @brief Function: void openNewTab(const std::string & website = std::string())
				 *
				 * \param website: website to open
				 *
				 * This function opens a new tab and loads the website provided as an argument. If argument website is empty, then the default tab will be opened
				 */
				void openNewTab(const std::string & website = std::string());

				/**
				 * @brief Function: void openFile(const std::string & filepath)
				 *
				 * \param filepath: path to the file to open
				 *
				 * This function opens a file in a new tab
				 */
				void openFile(const std::string & filepath);

				/**
				 * @brief Function: void executeCommand(const std::string & commandName, const std::string & argument)
				 *
				 * \param commandName: name of command to search in the JSON
				 * \param argument: argument to provide to the command. This argument can be an empty string
				 *
				 * This function send an argument and pass an argument to it
				 */
				void executeCommand(const std::string & commandName, const std::string & argument);

				/**
				 * @brief Function: bool commandRequiresEnter(const std::string & commandName) const
				 *
				 * \param commandName: name of command to search in the JSON
				 *
				 * This function returns true if the command requires the user to press Enter to validate the command
				 */
				bool commandRequiresEnter(const std::string & commandName) const;

			protected:

			private:

				/**
				 * @brief Function: std::string commandNameToTypedText(const std::string & commandName)
				 *
				 * \param commandName: name of command to search in the JSON
				 *
				 * This function converts a command name into the text to send to the app
				 */
				std::string commandNameToTypedText(const std::string & commandName);

				/**
				 * @brief Function: std::string commandNameToShownText(const std::string & commandName, const bool useShortcut);
				 *
				 * \param commandName: name of command to search in the JSON
				 * \param useShortcut: command sent through shortcuts
				 *
				 * This function converts a command name into the text to shown in the statusbar
				 */
				std::string commandNameToShownText(const std::string & commandName, const bool useShortcut);

				/**
				 * @brief Function: void writeTextToStatusBar(const std::string & textToWrite, const std::string & expectedText, const app::main_window::state_e & expectedState, const bool execute)
				 *
				 * \param textToWrite: text to write in the status bar
				 * \param expectedText: expected text to be displayed in the window
				 * \param expectedState: expected window state while typing
				 * \param excute: boolean that control whether to execute the command or not
				 * \param pressEnter: press enter to validate the command
				 *
				 * This function writes text to the status base and compares it against a golden reference
				 */
				void writeTextToStatusBar(const std::string & textToWrite, const std::string & expectedText, const app::main_window::state_e & expectedState, const bool execute, const bool pressEnter);

				/**
				 * @brief Function: void writeCommandToStatusBar(const std::string & commandName, const app::main_window::state_e & expectedState, const bool execute)
				 *
				 * \param commandName: name of command to search in the JSON
				 * \param expectedState: expected window state while typing
				 * \param excute: boolean that control whether to execute the command or not
				 *
				 * This function writes a command to the status base and creates the golden reference to compare against
				 */
				void writeCommandToStatusBar(const std::string & commandName, const app::main_window::state_e & expectedState, const bool execute);


				/**
				 * @brief use shortcuts to send commands
				 *
				 */
				bool sendCommandsThroughShortcuts;

		};


	}

}
/** @} */ // End of TesterBaseGroup group

#endif // COMMAND_TEST_H
