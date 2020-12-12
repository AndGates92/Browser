#ifndef MAIN_WINDOW_JSON_ACTION_H
#define MAIN_WINDOW_JSON_ACTION_H
/**
 * @copyright
 * @file action.h
 * @author Andrea Gianarda
 * @date 09th of October 2020
 * @brief Main Window JSON action class header file
*/

#include "app/shared/constructor_macros.h"
#include "app/windows/main_window/json/data.h"
#include "app/base/json/action.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace json {

			/**
			 * @brief Action class
			 *
			 */
			class Action : public app::base::json::Action<app::main_window::json::Data> {

				public:
					/**
					 * @brief Function: explicit Action()
					 *
					 * Default Main window json action class constructor
					 */
					explicit Action();

					/**
					 * @brief Function: explicit Action(const QString jsonFileName)
					 *
					 * \param jsonFileName: JSON filename
					 *
					 * Main window json action class constructor with JSON filename
					 */
					explicit Action(const QString jsonFileName);

					/**
					 * @brief Function: explicit Action(const QString jsonFiles)
					 *
					 * \param jsonFiles: list of JSON file names
					 *
					 * Main window json action class constructor with list of JSON file names
					 */
					explicit Action(const QStringList jsonFiles);

					/**
					 * @brief Function: virtual ~Action()
					 *
					 * Main window json action class destructor
					 */
					virtual ~Action();

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
					 * @brief Function: virtual void addItemToActionData(std::unique_ptr<app::main_window::json::Data> & data, const std::string & key, const std::string & item) override
					 *
					 * \param data: data to be updated
					 * \param key: key the tiem belongs to
					 * \param item: item to add
					 *
					 * This functions adds an item linked to the key to the data provided as input
					 */
					virtual void addItemToActionData(std::unique_ptr<app::main_window::json::Data> & data, const std::string & key, const std::string & item) override;

				private:
					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Action
					 *
					 */
					DISABLE_COPY_MOVE(Action)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_JSON_ACTION_H
