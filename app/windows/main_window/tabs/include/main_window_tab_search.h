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
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#include <QtWebEngineCore/QWebEngineFindTextResult>
#endif

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
	 * @brief search data changed
	 *
	 */
	typedef struct search_data_list {
		const int activeMatch;       /**< active match */
		const int numberOfMatches;   /**< total number of matches */
	} search_data_s;

	/**
	 * @brief MainWindowTabSearch class
	 *
	 */
	class MainWindowTabSearch final : public tab_search::TabSearch {
		friend class main_window_tab::MainWindowTab;

		Q_OBJECT

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

		signals:
			/**
			 * @brief Function: void searchResultChanged(const main_window_tab_search::search_data_s & data) const
			 *
			 * \param data: search result data.
			 *
			 * This function is a signal to notify that the search changed
			 */
			void searchResultChanged(const main_window_tab_search::search_data_s & data) const;

			/**
			 * @brief Function: void findTextFinished(bool found)
			 *
			 * \param found: boolean stating whether the text was found or not.
			 *
			 * This function is a signal to notify whether a search was successful
			 */
			void findTextFinished(bool found);

		protected:
			/**
			 * @brief Function: virtual void setCallback() override
			 *
			 * This function sets the callback to be run after the search
			 */
			virtual void setCallback() override;

		private:
			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots within the tab search
			 */
			void connectSignals();

			/**
			 * @brief Function: std::shared_ptr<main_window_tab::MainWindowTab> getTab() const
			 *
			 * \return tab the scroll manager belongs to
			 *
			 * This function returns the tab the scroll manager belongs to
			 */
			std::shared_ptr<main_window_tab::MainWindowTab> getTab() const;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabSearch
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabSearch)

		private slots:
			//#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
			// Dirty workaround for bug QTBUG-57121
			#if QT_VERSION >= 0x050e00
			/**
			 * @brief Function: void postProcessSearch(const QWebEngineFindTextResult & result)
			 *
			 * \param result: result of search
			 *
			 * This function is the slot that receives the result of the text search
			 */
			void postProcessSearch(const QWebEngineFindTextResult & result);
			#endif // QT_VERSION
	};
}
/** @} */ // End of MainWindowTabSearchGroup group

#endif // MAIN_WINDOW_WEB_ENGINE_SEARCH_H
