#ifndef MAIN_WINDOW_WEB_ENGINE_SEARCH_H
#define MAIN_WINDOW_WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file main_window_web_engine_search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Web Engine Search header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include "web_engine_search.h"
#include "main_window_web_engine_profile.h"
#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup MainWindowWebEngineSearchGroup Web Engine Search Doxygen Group
 *  Web Engine Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineSearchOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowWebEngineSearchFind)

namespace main_window_web_engine_search {

	/**
	 * @brief MainWindowWebEngineSearch class
	 *
	 */
	class MainWindowWebEngineSearch final : public web_engine_search::WebEngineSearch {

		public:
			/**
			 * @brief Function: explicit MainWindowWebEngineSearch(QWidget * attachedTab, QObject * parent = Q_NULLPTR)
			 *
			 * \param profile: profile of the search
			 * \param parent: parent widget
			 *
			 * Main window web engine search constructor
			 */
			explicit MainWindowWebEngineSearch(QWidget * attachedTab, QObject * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~MainWindowWebEngineSearch()
			 *
			 * Main window web engine search destructor
			 */
			virtual ~MainWindowWebEngineSearch();

		protected:

		private:

			/**
			 * @brief Function: void FindTabContent(const int & index, const QString & search, const bool & reverse, const bool & caseSensitive)
			 *
			 * \param search: text to search.
			 * \param reverse: true if searching in the reverse direction, false otherwise.
			 * \param caseSensitive: true if case sensitive search, false otherwise.
			 * \param callback: callback to call
			 *
			 * This function searches text in a webpage
			 */
			void FindTabContent(const QString & search, const bool & reverse, const bool & caseSensitive, void (* callback)(bool) = nullptr);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowWebEngineSearch
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowWebEngineSearch)

	};
}
/** @} */ // End of MainWindowWebEngineSearchGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_SEARCH_H
