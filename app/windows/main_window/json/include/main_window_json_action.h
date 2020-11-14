#ifndef MAIN_WINDOW_JSON_ACTION_H
#define MAIN_WINDOW_JSON_ACTION_H
/**
 * @copyright
 * @file main_window_json_action.h
 * @author Andrea Gianarda
 * @date 09th of October 2020
 * @brief Main Window JSON action class header file
*/

#include "common/include/constructor_macros.h"
#include "windows/main_window/json/include/main_window_json_data.h"
#include "base/json/include/json_action.h"

/** @defgroup MainWindowJsonActionGroup Main Window JSON action Doxygen Group
 *  Main Window JSON action functions and classes
 *  @{
 */

namespace main_window_json_action {

	/**
	 * @brief MainWindowJsonAction class
	 *
	 */
	class MainWindowJsonAction : public json_action::JsonAction<main_window_json_data::MainWindowJsonData> {

		public:
			/**
			 * @brief Function: explicit MainWindowJsonAction(const QString & jsonFileName = QString())
			 *
			 * \param jsonFileName: JSON filename
			 *
			 * Main window json action class constructor
			 */
			explicit MainWindowJsonAction(const QString & jsonFileName = QString());

			/**
			 * @brief Function: virtual ~MainWindowJsonAction()
			 *
			 * Main window json action class destructor
			 */
			virtual ~MainWindowJsonAction();

		protected:

			/**
			 * @brief Function: std::string getShortcutKey(const std::string & value)
			 *
			 * \param value: value read from JSON file
			 *
			 * \return a string ready to be use to construct a KeqSequence object
			 *
			 * This function process the value read from the JSON file in order to easily construct a KeySequence object
			 */
			std::string getShortcutKey(const std::string & value);

			/**
			 * @brief Function: std::string getShortcutModifier(const std::string & value)
			 *
			 * \param value: value read from JSON file
			 *
			 * \return a string ready to be use to construct a KeqSequence object
			 *
			 * This function process the value read from the JSON file in order to easily construct a KeySequence object
			 */
			std::string getShortcutModifier(const std::string & value);

			/**
			 * @brief Function: virtual void addItemToActionData(std::unique_ptr<main_window_json_data::MainWindowJsonData> & data, const std::string & key, const std::string & item) override
			 *
			 * \param data: data to be updated
			 * \param key: key the tiem belongs to
			 * \param item: item to add
			 *
			 * This functions adds an item linked to the key to the data provided as input
			 */
			virtual void addItemToActionData(std::unique_ptr<main_window_json_data::MainWindowJsonData> & data, const std::string & key, const std::string & item) override;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowJsonAction
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowJsonAction)

	};

}
/** @} */ // End of MainWindowJsonActionGroup group

#endif // MAIN_WINDOW_JSON_ACTION_H
