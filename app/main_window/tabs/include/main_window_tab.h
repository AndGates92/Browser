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
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "tab.h"
#include "global_types.h"
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
			 * @brief Function: explicit MainWindowTab(QWidget * parent, QWidget * tabBar, const QString & search, const main_window_shared_types::page_type_e type = main_window_shared_types::page_type_e::UNKNOWN, const QString & src = QString::null, const void * data = nullptr)
			 *
			 * \param type: tab type
			 * \param src: source of the tab
			 * \param data: tab extra data
			 * \param parent: parent widget
			 * \param tabBar: tab bar
			 *
			 * Main Window Tab constructor
			 */
			explicit MainWindowTab(QWidget * parent, QWidget * tabBar, const QString & search, const main_window_shared_types::page_type_e type = main_window_shared_types::page_type_e::UNKNOWN, const QString & src = QString::null, const void * data = nullptr);

			/**
			 * @brief Function: virtual ~MainWindowTab()
			 *
			 * Main Window Tab destructor
			 */
			virtual ~MainWindowTab();

			/**
			 * @brief Function: main_window_web_engine_page::MainWindowWebEnginePage * getPage() const
			 *
			 * \return tab web page object
			 *
			 * This function returns the page linked to the tab
			 */
			main_window_web_engine_page::MainWindowWebEnginePage * getPage() const;

			/**
			 * @brief Function: const QString getSearchText() const
			 *
			 * \return text searched by the user for this tab
			 *
			 * This function returns the text searched by the user for this tab
			 */
			const QString getSearchText() const;

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
			 * @brief Function: virtual main_window_web_engine_view::MainWindowWebEngineView * getView() const override
			 *
			 * \return tab view
			 *
			 * This function returns the tab view
			 */
			virtual main_window_web_engine_view::MainWindowWebEngineView * getView() const override;

			/**
			 * @brief Function: main_window_tab_load_manager::MainWindowTabLoadManager * getLoadManager() const override
			 *
			 * \return load manager
			 *
			 * This function returns the load manager
			 */
			virtual main_window_tab_load_manager::MainWindowTabLoadManager * getLoadManager() const override;

			/**
			 * @brief Function: virtual main_window_tab_search::MainWindowTabSearch * getSearch() const override
			 *
			 * \return tab search
			 *
			 * This function returns the tab search
			 */
			virtual main_window_tab_search::MainWindowTabSearch * getSearch() const override;

			/**
			 * @brief Function: virtual main_window_web_engine_history::MainWindowWebEngineHistory * getHistory() const override
			 *
			 * \return history of the tab
			 *
			 * This function returns the history of the page
			 */
			virtual main_window_web_engine_history::MainWindowWebEngineHistory * getHistory() const override;

			/**
			 * @brief Function: virtual main_window_web_engine_settings::MainWindowWebEngineSettings * getSettings() const override
			 *
			 * \return tab settings
			 *
			 * This function returns the settings
			 */
			virtual main_window_web_engine_settings::MainWindowWebEngineSettings * getSettings() const override;

			/**
			 * @brief Function: virtual main_window_tab_scroll_manager::MainWindowTabScrollManager * getScrollManager() const override
			 *
			 * \return scroll manager
			 *
			 * This function returns the scroll manager
			 */
			virtual main_window_tab_scroll_manager::MainWindowTabScrollManager * getScrollManager() const override;

			/**
			 * @brief Function: void updateView(main_window_web_engine_view::MainWindowWebEngineView * value)
			 *
			 * \param value: view to use
			 *
			 * This function updates the current view as well as informations derived from it
			 */
			void updateView(main_window_web_engine_view::MainWindowWebEngineView * value);

			/**
			 * @brief Function: void reload() override
			 *
			 * This function reloads the content of the page
			 */
			void reload() override;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTab
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTab)

		private slots:
			/**
			 * @brief Function: void postprocessLoadFInished(const bool & success)
			 *
			 * This function postprocessing the end of a page load
			 */
			void postprocessLoadFInished(const bool & success);

	};
}
/** @} */ // End of TabGroup group

#endif // MAIN_WINDOW_TAB_H
