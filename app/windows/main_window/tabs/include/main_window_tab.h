#ifndef MAIN_WINDOW_TAB_H
#define MAIN_WINDOW_TAB_H
/**
 * @copyright
 * @file main_window_tab.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWidgets/QWidget>

#include "tab.h"
#include "global_enums.h"
#include "constructor_macros.h"
#include "main_window_shared_types.h"
#include "main_window_web_engine_view.h"
#include "main_window_web_engine_settings.h"
#include "main_window_web_engine_history.h"
#include "main_window_tab_search.h"
#include "main_window_tab_load_manager.h"
#include "main_window_tab_scroll_manager.h"

/** @defgroup TabGroup Main Window Tab Doxygen Group
 *  Main Window Tab functions and classes
 *  @{
 */

namespace main_window_tab_widget {
	class MainWindowTabWidget;
}

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabOverall)

namespace main_window_tab {

	/**
	 * @brief MainWindowTab class
	 *
	 */
	class MainWindowTab final : public tab::Tab {
		friend class main_window_tab_widget::MainWindowTabWidget;

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit MainWindowTab(QWidget * parent, const QString & search)
			 *
			 * \param search: search in the current tab
			 * \param parent: parent widget
			 *
			 * Main Window Tab constructor
			 */
			explicit MainWindowTab(QWidget * parent, const QString & search);

			/**
			 * @brief Function: virtual ~MainWindowTab()
			 *
			 * Main Window Tab destructor
			 */
			virtual ~MainWindowTab();

			/**
			 * @brief Function: std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> getPage() const
			 *
			 * \return tab web page object
			 *
			 * This function returns the page linked to the tab
			 */
			std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> getPage() const;

			/**
			 * @brief Function: const QString getSearchText() const
			 *
			 * \return text searched by the user for this tab
			 *
			 * This function returns the text searched by the user for this tab
			 */
			const QString getSearchText() const;

			/**
			 * @brief Function: void configure(std::shared_ptr<tab_bar::TabBar> tabBar, const main_window_shared_types::page_type_e type, const QString & src, const void * data)
			 *
			 * \param type: tab type
			 * \param src: source of the tab
			 * \param data: tab extra data
			 * \param tabBar: tab bar
			 *
			 * This function configures the main window tab
			 */
			void configure(std::shared_ptr<tab_bar::TabBar> tabBar, const main_window_shared_types::page_type_e type, const QString & src, const void * data);

		signals:
			/**
			 * @brief Function: void sourceChanged(const QString & src)
			 *
			 * \param src: source of the content of the page
			 *
			 * This signal notifies that the title of a page has changed
			 */
			void sourceChanged(const QString & src);

			/**
			 * @brief Function: void titleChanged(const QString & title)
			 *
			 * \param title: title of the content of the page
			 *
			 * This signal notifies that the title of a page has changed
			 */
			void titleChanged(const QString & src);

			/**
			 * @brief Function: void urlChanged(const QUrl & url)
			 *
			 * \param url: url of the page
			 *
			 * This signal notifies that the url of a page has changed
			 */
			void urlChanged(const QUrl & url);

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

		private:
			/**
			 * @brief text searched for this tab
			 *
			 */
			QString searchText;

			/**
			 * @brief Function: void connectSignals() override
			 *
			 * This function connects signals and slots within main window controller tabs
			 */
			void connectSignals() override;

			/**
			 * @brief Function: void setSearchText(QString value)
			 *
			 * \param value: text searched by the user for this tab
			 *
			 * This function sets the text searched by the user for this tab
			 */
			void setSearchText(QString value);

			/**
			 * @brief Function: std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> getView() const
			 *
			 * \return tab view
			 *
			 * This function returns the tab view
			 */
			std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> getView() const;

			/**
			 * @brief Function: std::shared_ptr<main_window_tab_load_manager::MainWindowTabLoadManager> getLoadManager() const
			 *
			 * \return load manager
			 *
			 * This function returns the load manager
			 */
			std::shared_ptr<main_window_tab_load_manager::MainWindowTabLoadManager> getLoadManager() const;

			/**
			 * @brief Function: std::shared_ptr<main_window_tab_search::MainWindowTabSearch> getSearch() const
			 *
			 * \return tab search
			 *
			 * This function returns the tab search
			 */
			std::shared_ptr<main_window_tab_search::MainWindowTabSearch> getSearch() const;

			/**
			 * @brief Function: std::shared_ptr<main_window_web_engine_history::MainWindowWebEngineHistory> getHistory() const
			 *
			 * \return history of the tab
			 *
			 * This function returns the history of the page
			 */
			std::shared_ptr<main_window_web_engine_history::MainWindowWebEngineHistory> getHistory() const;

			/**
			 * @brief Function: std::shared_ptr<main_window_web_engine_settings::MainWindowWebEngineSettings> getSettings() const
			 *
			 * \return tab settings
			 *
			 * This function returns the settings
			 */
			std::shared_ptr<main_window_web_engine_settings::MainWindowWebEngineSettings> getSettings() const;

			/**
			 * @brief Function: std::shared_ptr<main_window_tab_scroll_manager::MainWindowTabScrollManager> getScrollManager() const
			 *
			 * \return scroll manager
			 *
			 * This function returns the scroll manager
			 */
			std::shared_ptr<main_window_tab_scroll_manager::MainWindowTabScrollManager> getScrollManager() const;

			/**
			 * @brief Function: void updateView(std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> value)
			 *
			 * \param value: view to use
			 *
			 * This function updates the current view as well as informations derived from it
			 */
			void updateView(std::shared_ptr<main_window_web_engine_view::MainWindowWebEngineView> value);

			/**
			 * @brief Function: void reload() override
			 *
			 * This function reloads the content of the page
			 */
			void reload() override;

			/**
			 * @brief Function: std::shared_ptr<main_window_tab::MainWindowTab> shared_from_this()
			 *
			 * \return shared pointer of this
			 *
			 * This function returns a shared pointer to this
			 */
			std::shared_ptr<main_window_tab::MainWindowTab> shared_from_this();

			/**
			 * @brief Function: std::weak_ptr<main_window_tab::MainWindowTab> sweak_from_this()
			 *
			 * \return weak pointer of this
			 *
			 * This function returns a weak pointer to this
			 */
			std::weak_ptr<main_window_tab::MainWindowTab> weak_from_this();

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTab
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTab)

		private slots:
			/**
			 * @brief Function: void postprocessLoadFinished(const bool & success)
			 *
			 * This function postprocessing the end of a page load
			 */
			void postprocessLoadFinished(const bool & success);

	};
}
/** @} */ // End of TabGroup group

#endif // MAIN_WINDOW_TAB_H
