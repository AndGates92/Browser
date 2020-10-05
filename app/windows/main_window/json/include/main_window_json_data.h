#ifndef MAIN_WINDOW_JSON_DATA_H
#define MAIN_WINDOW_JSON_DATA_H
/**
 * @copyright
 * @file main_window_json_data.h
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Json Data header file
*/

#include <memory>
#include <vector>

#include <QtCore/QLoggingCategory>

#include "key_sequence.h"
#include "main_window_shared_types.h"
#include "json_data.h"

/** @defgroup MainWindowJsonDataGroup Main Window Json Data Doxygen Group
 *  Main Window json data functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowJsonDataOverall)

namespace main_window_json_action {
	class MainWindowJsonAction;
}

namespace main_window_json_data {

	namespace {
		/**
		 * @brief default action parameters which are the keys of the JSON file
		 *
		 */
		static const std::vector<std::string> keyNames{"Key", "Name", "State", "Shortcut", "LongCmd", "Help"};
	}

	/**
	 * @brief MainWindowJsonData class
	 *
	 */
	class MainWindowJsonData : public json_data::JsonData {
		friend class main_window_json_action::MainWindowJsonAction;

		public:

			/**
			 * @brief Function: static std::shared_ptr<main_window_json_data::MainWindowJsonData> makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue)
			 *
			 * \param jsonKey: key in the json file
			 * \param nameKeyValue: name of the action
			 * \param stateKeyValue: state the action puts the main controller into
			 * \param shortcutKeyValue: shortcut associated with the action
			 * \param longCmdKeyValue: long command the user has to type to trigger the action
			 * \param helpKeyValue: help for the action
			 *
			 * this function constructs a new instance of class MainWindowJsonData
			 */
			static std::shared_ptr<main_window_json_data::MainWindowJsonData> makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue);

			/**
			 * @brief Function: MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue = std::string(), const main_window_shared_types::state_e & stateKeyValue = main_window_shared_types::state_e::IDLE, const int & shortcutKeyValue = (int)Qt::Key_unknown, const std::string & longCmdKeyValue = std::string(), const std::string & helpKeyValue = std::string())
			 *
			 * \param jsonKey: key in the json file
			 * \param nameKeyValue: name of the action
			 * \param stateKeyValue: state the action puts the main controller into
			 * \param shortcutKeyValue: shortcut associated with the action
			 * \param longCmdKeyValue: long command the user has to type to trigger the action
			 * \param helpKeyValue: help for the action
			 *
			 * Main Window json data constructor
			 */
			explicit MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue = std::string(), const main_window_shared_types::state_e & stateKeyValue = main_window_shared_types::state_e::IDLE, const int & shortcutKeyValue = (int)Qt::Key_unknown, const std::string & longCmdKeyValue = std::string(), const std::string & helpKeyValue = std::string());

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main Window json data copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: MainWindowJsonData::MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main Window json data move constructor
			 */
			explicit MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs);

			/**
			 * @brief Function: virtual ~MainWindowJsonData()
			 *
			 * Main Window json data structure destructor
			 */
			virtual ~MainWindowJsonData();

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowJsonData & operator=(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main Window json data copy assignment operator
			 */
			MainWindowJsonData & operator=(const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: MainWindowJsonData & operator=(main_window_json_data::MainWindowJsonData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main Window json data move assignment operator
			 */
			MainWindowJsonData & operator=(main_window_json_data::MainWindowJsonData && rhs);

			/**
			 * @brief Function: bool operator==(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param rhs: right side class to compare
			 *
			 * Main Window json data operator == overloading
			 */
			bool operator==(const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: bool operator!=(const main_window_json_data::MainWindowJsonData & rhs)
			 *
			 * \param lhs: left side class to compare
			 * \param rhs: right side class to compare
			 *
			 * Main Window json data operator != overloading
			 */
			bool operator!=(const main_window_json_data::MainWindowJsonData & rhs);

			/**
			 * @brief Function: virtual const std::string print() const override
			 *
			 * \return main window json data converted to std::string
			 *
			 * This functions prints main window json data info to std::string
			 */
			virtual const std::string print() const override;

			/**
			 * @brief Function: const std::string & getKey() const
			 *
			 * \return key under which the JSON object for this action is
			 *
			 * This functions returns the key under which the JSON object for this action is
			 */
			const std::string & getKey() const;

			/**
			 * @brief Function: const std::string & getName() const
			 *
			 * \return name of the action
			 *
			 * This functions returns the name of the action
			 */
			const std::string & getName() const;

			/**
			 * @brief Function: const main_window_shared_types::state_e & getLongCmd() const
			 *
			 * \return state the main window has to be put into to execute the action
			 *
			 * This functions returns the state the main window has to be put into to execute the action
			 */
			const main_window_shared_types::state_e & getState() const;

			/**
			 * @brief Function: const int & getShortcut() const
			 *
			 * \return shortcut for the action
			 *
			 * This functions returns the shortcut for the action
			 */
			const int & getShortcut() const;

			/**
			 * @brief Function: const std::string & getLongCmd() const
			 *
			 * \return long command for the action
			 *
			 * This functions returns the long command for the action
			 */
			const std::string & getLongCmd() const;

			/**
			 * @brief Function: const std::string & getHelp() const
			 *
			 * \return help of the action
			 *
			 * This functions returns the help of the action
			 */
			const std::string & getHelp() const;

			/**
			 * @brief Function: virtual bool isSameFieldValue(const std::string & name, const void * value) const override
			 *
			 * \param name: name of the name of the member as a string
			 * \param value: value of the member
			 *
			 * \return if field value matches value
			 *
			 * This functions compares the input value with the member of MainWindowJsonData by accessing it through its name
			 */
			virtual bool isSameFieldValue(const std::string & name, const void * value) const override;

			/**
			 * @brief Function: virtual const void * getValueFromMemberName(const std::string & name) const override
			 *
			 * \param name: name of the name of the member as a string
			 *
			 * \return value of the member
			 *
			 * This functions returns the value of a member of MainWindowJsonData by accessing it through its name
			 */
			virtual const void * getValueFromMemberName(const std::string & name) const override;

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
			int shortcut;

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

			/**
			 * @brief Function: virtual void setValueFromMemberName(const std::string & name, const void * value) override
			 *
			 * \param name: name of the member as a string
			 * \param value: value to be assigned to the element
			 *
			 * This functions assign a value to a member of MainWindowJsonData by accessing it through its name
			 */
			virtual void setValueFromMemberName(const std::string & name, const void * value) override;

	};

}
/** @} */ // End of MainWindowJsonDataGroup group

#endif // MAIN_WINDOW_JSON_DATA_H
