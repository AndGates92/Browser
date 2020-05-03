#ifndef WEB_ENGINE_SEARCH_H
#define WEB_ENGINE_SEARCH_H
/**
 * @copyright
 * @file tab_search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab Search header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtCore/QString>
#include <qt5/QtWebEngineWidgets/QWebEnginePage>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup TabSearchGroup Tab Search Doxygen Group
 *  Tab Search functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabSearchOverall)
Q_DECLARE_LOGGING_CATEGORY(tabSearchFind)

namespace tab_search {

	/**
	 * @brief TabSearch class
	 *
	 */
	class TabSearch : public QObject {

		public:
			/**
			 * @brief Function: explicit TabSearch(QObject * parent, QWidget * attachedTab)
			 *
			 * \param attachedTab: tab attached to the search instance
			 * \param parent: parent object
			 *
			 * Tab search constructor
			 */
			explicit TabSearch(QObject * parent, QWidget * attachedTab);

			/**
			 * @brief Function: virtual ~TabSearch()
			 *
			 * Tab search destructor
			 */
			virtual ~TabSearch();

			/**
			 * @brief Function: virtual void findPrev() final
			 *
			 * This function searches previous match in a webpage
			 */
			virtual void findPrev() final;

			/**
			 * @brief Function: virtual void findNext() final
			 *
			 * This function searches next match in a webpage
			 */
			virtual void findNext() final;

			/**
			 * @brief Function: virtual void findTabContent(const QString & searchText, const bool & reverse, const bool & caseSensitive, std::function<void(bool)> cb = std::function<void(bool)>()) final
			 *
			 * \param searchText: text to search.
			 * \param reverse: true if searching in the reverse direction, false otherwise.
			 * \param caseSensitive: true if case sensitive search, false otherwise.
			 * \param cb: callback to call
			 *
			 * This function searches text in a webpage
			 */
			virtual void findTabContent(const QString & searchText, const bool & reverse, const bool & caseSensitive, std::function<void(bool)> cb = std::function<void(bool)>()) final;

		protected:
			/**
			 * @brief tab attached to the web search instance
			 *
			 */
			QWidget * tab;

			/**
			 * @brief text to search
			 *
			 */
			QString text;

			/**
			 * @brief search flags
			 *
			 */
			QWebEnginePage::FindFlags flags;

			/**
			 * @brief callback
			 *
			 */
			std::function<void(bool)> callback;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabSearch
			 *
			 */
			DISABLE_COPY_MOVE(TabSearch)

			/**
			 * @brief Function: virtual void search() final
			 *
			 * This function searches text in a webpage
			 */
			virtual void search() final;

	};
}
/** @} */ // End of TabSearchGroup group

#endif // WEB_ENGINE_SEARCH_H
