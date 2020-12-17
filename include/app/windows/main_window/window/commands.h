#ifndef MAIN_WINDOW_COMMANDS_H
#define MAIN_WINDOW_COMMANDS_H
/**
 * @copyright
 * @file commands.h
 * @author Andrea Gianarda
 * @date 13th December 2020
 * @brief Main window commands header file 
 */

#include "app/shared/constructor_macros.h"
#include "app/windows/main_window/json/action.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and class
 *  @{
 */
namespace app {

	namespace main_window {

		namespace window {

			/**
			 * @brief Commands class
			 *
			 */
			class Commands : public app::main_window::json::Action::Action {

				public:
					/**
					 * @brief Function: explicit Commands()
					 *
					 * Main window commands constructor
					 */
					explicit Commands();

					/**
					 * @brief Function: explicit Commands(const std::string jsonFile)
					 *
					 * \param jsonFile: JSON files with the commands
					 *
					 * Main window commands constructor with JSON file
					 */
					explicit Commands(const std::string jsonFile);

					/**
					 * @brief Function: explicit Commands(const std::list<std::string> jsonFiles)
					 *
					 * \param jsonFiles: list of JSON files with the commands
					 *
					 * Main window commands constructor with JSON file list
					 */
					explicit Commands(const std::list<std::string> jsonFiles);

					/**
					 * @brief Function: virtual ~Commands()
					 *
					 * Main window commands destructor
					 */
					virtual ~Commands();

					/**
					 * @brief Function: void appendActionData(const std::list<std::string> & jsonFiles)
					 *
					 * \param jsonFiles: list of JSON file names
					 *
					 * This function append to the action data map with the content from the json files
					 */
					void appendActionData(const std::list<std::string> & jsonFiles);

					/**
					 * @brief Function: void appendActionData(const std::string & filename)
					 *
					 * \param filename: JSON file name to append
					 *
					 * This function append to the action data map with the content of a JSON file
					 */
					void appendActionData(const std::string & filename);

					/**
					 * @brief Function: void clear()
					 *
					 * This function clears the main window commands 
					 */
					void clear();

				protected:

				private:

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Commands
					 *
					 */
					DISABLE_COPY_MOVE(Commands)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_COMMANDS_H
