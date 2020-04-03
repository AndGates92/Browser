#ifndef WEB_ENGINE_SEARCH_H
#define WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file web_engine_search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Web Engine Search header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtCore/QString>
#include <qt5/QtWebEngineWidgets/QWebEnginePage>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup WebEngineSearchGroup Web Engine Search Doxygen Group
 *  Web Engine Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(webEngineSearchOverall)

namespace web_engine_search {

	/**
	 * @brief WebEngineSearch class
	 *
	 */
	class WebEngineSearch : public QObject {

		public:
			/**
			 * @brief Function: explicit WebEngineSearch(QWidget * attachedTab, QObject * parent = Q_NULLPTR)
			 *
			 * \param attachedTab: tab attached to the search instance
			 * \param parent: parent object
			 *
			 * Web engine search constructor
			 */
			explicit WebEngineSearch(QWidget * attachedTab, QObject * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~WebEngineSearch()
			 *
			 * Web engine search destructor
			 */
			virtual ~WebEngineSearch();

			// clear
			// search
			// find prev
			// find next

		protected:
			/**
			 * @brief text to search
			 *
			 */
			QString text = QString::null;

			/**
			 * @brief search flags
			 *
			 */
			QWebEnginePage::FindFlag flags;

			/**
			 * @brief tab attached to the web search instance
			 *
			 */
			QWidget * tab;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class WebEngineSearch
			 *
			 */
			DISABLE_COPY_MOVE(WebEngineSearch)

	};
}
/** @} */ // End of WebEngineSearchGroup group

#endif // WEB_ENGINE_SEARCH_H
