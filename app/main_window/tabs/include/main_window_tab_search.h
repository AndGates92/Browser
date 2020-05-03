#ifndef MAIN_WINDOW_WEB_ENGINE_SEARCH_H
#define MAIN_WINDOW_WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file main_window_tab_search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab Search header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "tab_search.h"
#include "main_window_web_engine_profile.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup MainWindowTabSearchGroup Main Window Tab Search Doxygen Group
 *  Main Window Tab Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabSearchOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabSearchFind)

namespace main_window_tab_search {

	/**
	 * @brief MainWindowTabSearch class
	 *
	 */
	class MainWindowTabSearch final : public tab_search::TabSearch {

		public:
			/**
			 * @brief Function: explicit MainWindowTabSearch(QObject * parent, QWidget * attachedTab)
			 *
			 * \param profile: profile of the search
			 * \param parent: parent widget
			 *
			 * Main window web engine search constructor
			 */
			explicit MainWindowTabSearch(QObject * parent, QWidget * attachedTab);

			/**
			 * @brief Function: virtual ~MainWindowTabSearch()
			 *
			 * Main window web engine search destructor
			 */
			virtual ~MainWindowTabSearch();

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabSearch
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabSearch)

	};
}
/** @} */ // End of MainWindowTabSearchGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_SEARCH_H
