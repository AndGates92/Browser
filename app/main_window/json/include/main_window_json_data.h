#ifndef MAIN_WINDOW_JSON_DATA_H
#define MAIN_WINDOW_JSON_DATA_H
/**
 * @copyright
 * @file main_window_json_data.h
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Json Data header file
*/

#include <qt5/QtCore/QLoggingCategory>

#include "key_sequence.h"
#include "main_window_shared_types.h"

/** @defgroup MainWindowJsonDataGroup Main Window Json Data Doxygen Group
 *  Main Window json data functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowJsonDataOverall)

namespace main_window_json_data {

	class MainWindowJsonData {

		public:

			/**
			 * @brief Function: static main_window_json_data::MainWindowJsonData * makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const key_sequence::KeySequence & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue)
			 *
			 * \param jsonKey: key in te json file
			 * \param nameKeyValue: name of the action
			 * \param stateKeyValue: state the action puts the main controller into
			 * \param shortcutKeyValue: shortcut associated with the action
			 * \param longCmdKeyValue: long command the user has to type to trigger the action
			 * \param helpKeyValue: help for the action
			 *
			 * this function constructs a new instance of class MainWindowJsonData
			 */
			static main_window_json_data::MainWindowJsonData * makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const key_sequence::KeySequence & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue);

			/**
			 * @brief Function: MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const key_sequence::KeySequence & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue)
			 *
			 * \param jsonKey: key in te json file
			 * \param nameKeyValue: name of the action
			 * \param stateKeyValue: state the action puts the main controller into
			 * \param shortcutKeyValue: shortcut associated with the action
			 * \param longCmdKeyValue: long command the user has to type to trigger the action
			 * \param helpKeyValue: help for the action
			 *
			 * json data constructor
			 */
			explicit MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const key_sequence::KeySequence & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * json data copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: MainWindowJsonData::MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * json data move constructor
			 */
			explicit MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowJsonData & operator=(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * json data copy assignment operator
			 */
			MainWindowJsonData & operator=(const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: MainWindowJsonData & operator=(main_window_json_data::MainWindowJsonData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * json data move assignment operator
			 */
			MainWindowJsonData & operator=(main_window_json_data::MainWindowJsonData && rhs);

			/**
			 * @brief Function: friend bool operator==(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param lhs: left side class to compare
			 * \param rhs: right side class to compare
			 *
			 * json data operator == overloading
			 */
			friend bool operator==(const main_window_json_data::MainWindowJsonData & lhs, const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: friend bool operator!=(const main_window_json_data::MainWindowJsonData & lhs, const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param lhs: left side class to compare
			 * \param rhs: right side class to compare
			 *
			 * json data operator != overloading
			 */
			friend bool operator!=(const main_window_json_data::MainWindowJsonData & lhs, const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: ~MainWindowJsonData()
			 *
			 * json data structure destructor
			 */
			~MainWindowJsonData();

			/**
			 * @brief Function: std::string print() const
			 *
			 * \return json data converted to std::string
			 *
			 * This functions prints json data info to std::string
			 */
			std::string print() const;

			/**
			 * @brief Function: QString qprint() const
			 *
			 * \return json data converted to QString
			 *
			 * This functions prints json data info to QString
			 */
			const QString qprint() const;

			/**
			 * @brief Function: const std::string getKey() const
			 *
			 * \return key under which the JSON object for this action is
			 *
			 * This functions returns the key under which the JSON object for this action is
			 */
			const std::string getKey() const;

			/**
			 * @brief Function: const std::string getName() const
			 *
			 * \return name of the action
			 *
			 * This functions returns the name of the action
			 */
			const std::string getName() const;

			/**
			 * @brief Function: main_window_shared_types::state_e getLongCmd() const
			 *
			 * \return state the main window has to be put into to execute the action
			 *
			 * This functions returns the state the main window has to be put into to execute the action
			 */
			main_window_shared_types::state_e getState() const;

			/**
			 * @brief Function: const key_sequence::KeySequence getShortcut() const
			 *
			 * \return shortcut for the action
			 *
			 * This functions returns the shortcut for the action
			 */
			const key_sequence::KeySequence getShortcut() const;

			/**
			 * @brief Function: const std::string getLongCmd() const
			 *
			 * \return long command for the action
			 *
			 * This functions returns the long command for the action
			 */
			const std::string getLongCmd() const;

			/**
			 * @brief Function: const std::string getHelp() const
			 *
			 * \return help of the action
			 *
			 * This functions returns the help of the action
			 */
			const std::string getHelp() const;

		protected:

		private:
			/**
			 * @brief key under which the JSON object is
			 *
			 */
			std::string key;

			/**
			 * @brief name of the action
			 *
			 */
			std::string name;

			/**
			 * @brief state the main window has to be put into to execute the action
			 *
			 */
			main_window_shared_types::state_e state;

			/**
			 * @brief shortcut associated with the action
			 *
			 */
			key_sequence::KeySequence shortcut;

			/**
			 * @brief long command the user has to type to trigger the action
			 *
			 */
			std::string longCmd;

			/**
			 * @brief help for the action
			 *
			 */
			std::string help;

	};

}
/** @} */ // End of MainWindowJsonDataGroup group

#endif // MAIN_WINDOW_JSON_DATA_H
