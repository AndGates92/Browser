#ifndef MAIN_WINDOW_CONSTANTS_H
#define MAIN_WINDOW_CONSTANTS_H
/**
 * @copyright
 * @file constants.h
 * @author Andrea Gianarda
 * @date 14th of October 2020
 * @brief Main Window Constants file
*/

#include <QtCore/QString>

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  MainWindow Constants
 *  @{
 */
namespace app {

	namespace main_window {

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		static const QString defaultSearchEngine("https://www.duckduckgo.com/?q=%1");

		/**
		 * @brief file prefix in status bar label
		 *
		 */
		const QString filePrefix("file:");

		/**
		 * @brief Text to print when no tab is opened
		 *
		 */
		const QString noTabInfoText("No tabs");

	}

}

/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CONSTANTS_H
