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
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include "tab_search.h"
#include "main_window_web_engine_profile.h"
#include "global_enums.h"
#include "constructor_macros.h"

/** @defgroup MainWindowTabSearchGroup Main Window Tab Search Doxygen Group
 *  Main Window Tab Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabSearchOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabSearchFind)

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_tab_search {

	/**
	 * @brief MainWindowTabSearch class
	 *
	 */
	class MainWindowTabSearch final : public tab_search::TabSearch {
		friend class main_window_tab::MainWindowTab;

		public:
			/**
			 * @brief Function: explicit MainWindowTabSearch(QWidget * parent, QWidget * attachedTab)
			 *
			 * \param profile: profile of the search
			 * \param parent: parent widget
			 *
			 * Main window web engine search constructor
			 */
			explicit MainWindowTabSearch(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> attachedTab);

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
