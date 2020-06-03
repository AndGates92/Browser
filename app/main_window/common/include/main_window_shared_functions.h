#ifndef MAIN_WINDOW_SHARED_FUNCTIONS_H
#define MAIN_WINDOW_SHARED_FUNCTIONS_H
/**
 * @copyright
 * @file main_window_shared_functions.h
 * @author Andrea Gianarda
 * @date 2nd June 2020
 * @brief Main Window Shared Functions file
*/

#include <qt5/QtCore/QtDebug>

#include "type_print_macros.h"

/** @defgroup MainWindowSharedFunctionsGroup Main Window Shared Functions Doxygen Group
 *  Main Window Shared Functions
 *  @{
 */
namespace main_window_shared_functions {

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
}

/** @} */ // End of MainWindowSharedFunctionsGroup group

#endif // MAIN_WINDOW_SHARED_FUNCTIONS_H
