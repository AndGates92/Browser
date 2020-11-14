#ifndef MAIN_WINDOW_TAB_SEARCH_H
#define MAIN_WINDOW_TAB_SEARCH_H
/**
 * @copyright
 * @file search.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab Search header file
*/

// Qt libraries
#include <QtCore/QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#include <QtWebEngineCore/QWebEngineFindTextResult>
#endif

#include "base/tabs/include/search.h"
#include "windows/main_window/tabs/include/web_engine_profile.h"
#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class Tab;

			/**
			 * @brief search data changed
			 *
			 */
			typedef struct search_data_list {
				const int activeMatch;       /**< active match */
				const int numberOfMatches;   /**< total number of matches */
			} search_data_s;

			/**
			 * @brief Search class
			 *
			 */
			class Search final : public app::base::tab::Search {
				friend class app::main_window::tab::Tab;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit Search(QWidget * parent, QWidget * attachedTab)
					 *
					 * \param profile: profile of the search
					 * \param parent: parent widget
					 *
					 * Main window tab search constructor
					 */
					explicit Search(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> attachedTab);

					/**
					 * @brief Function: virtual ~Search()
					 *
					 * Main window tab search destructor
					 */
					virtual ~Search();

				signals:
					/**
					 * @brief Function: void searchResultChanged(const app::main_window::tab::search_data_s & data) const
					 *
					 * \param data: search result data.
					 *
					 * This function is a signal to notify that the search changed
					 */
					void searchResultChanged(const app::main_window::tab::search_data_s & data) const;

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
					 * @brief Function: std::shared_ptr<app::main_window::tab::Tab> getTab() const
					 *
					 * \return tab the scroll manager belongs to
					 *
					 * This function returns the tab the scroll manager belongs to
					 */
					std::shared_ptr<app::main_window::tab::Tab> getTab() const;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Search
					 *
					 */
					DISABLE_COPY_MOVE(Search)

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

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_SEARCH_H
