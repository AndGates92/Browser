#ifndef MAIN_WINDOW_SHARED_FUNCTIONS_H
#define MAIN_WINDOW_SHARED_FUNCTIONS_H
/**
 * @copyright
 * @file shared_functions.h
 * @author Andrea Gianarda
 * @date 2nd June 2020
 * @brief Main Window Shared Functions file
*/

#include "app/windows/main_window/shared/shared_types.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions
 *  @{
 */
namespace app {

	namespace main_window {

		/**
		 * @brief Function: bool isUrl(const QString & text)
		 *
		 * \param text: text to check
		 *
		 * \return true if the text is a valid URL, false otherwise
		 *
		 * This function check whether input string is a URL
		 */
		bool isUrl(const QString & text);

		/**
		 * @brief Function: bool isFile(const QString & text)
		 *
		 * \param text: text to check
		 *
		 * \return true if the text is an existing file, false otherwise
		 *
		 * This function check whether input string is a file
		 */
		bool isFile(const QString & text);

		/**
		 * @brief Function: bool isText(const QString & text)
		 *
		 * \param text: text to check
		 *
		 * \return true if the text is a valid text, false otherwise
		 *
		 * This function check whether input string is text
		 */
		bool isText(const QString & text);

		/**
		 * @brief Function: app::main_window::page_type_e textToPageType(const QString & text)
		 *
		 * \param text: text to deduce type from
		 *
		 * \return the page type deduced for the text provided as argument
		 *
		 * This function deduces the page type associated with the text provided as argument
		 */
		app::main_window::page_type_e textToPageType(const QString & text);

		/**
		 * @brief Function: QString app::main_window::deletePrefix(QString text)
		 *
		 * \param source: raw text
		 *
		 * \return the text without any prefix
		 *
		 * This function deletes prefixes from the text passed as argument
		 */
		QString deletePrefix(QString text);
	}

}

/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_SHARED_FUNCTIONS_H
