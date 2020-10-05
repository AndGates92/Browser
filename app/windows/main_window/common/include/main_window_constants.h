#ifndef MAIN_WINDOW_CONSTANTS_H
#define MAIN_WINDOW_CONSTANTS_H
/**
 * @copyright
 * @file main_window_constants.h
 * @author Andrea Gianarda
 * @date 14th of October 2020
 * @brief Main Window Constants file
*/

#include <QtCore/QString>

/** @defgroup MainWindowConstantsGroup Main Window Constants Doxygen Group
 *  MainWindow Constants
 *  @{
 */
namespace main_window_constants {

	/**
	 * @brief default serch engine is duckduckgo
	 *
	 */
	static const QString defaultSearchEngine("duckduckgo.com/?q=%1");

	/**
	 * @brief file prefix in status bar label
	 *
	 */
	const QString filePrefix("file:");

}

/** @} */ // End of MainWindowConstantsGroup group

#endif // MAIN_WINDOW_CONSTANTS_H
