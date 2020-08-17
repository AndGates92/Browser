#ifndef TAB_H
#define TAB_H
/**
 * @copyright
 * @file tab.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWidgets/QWidget>

#include "global_enums.h"
#include "constructor_macros.h"
#include "find_settings.h"
#include "web_engine_view.h"
#include "web_engine_settings.h"
#include "tab_load_manager.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabOverall)
Q_DECLARE_LOGGING_CATEGORY(tabSize)

namespace tab_bar {
	class TabBar;
}

namespace tab_widget {
	class TabWidget;
}

namespace tab_search {
	class TabSearch;
}

namespace tab_scroll_manager {
	class TabScrollManager;
}

namespace tab_history {
	class TabHistory;
}

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_tab_widget {
	class MainWindowTabWidget;
}

namespace tab {

	/**
	 * @brief Tab class
	 *
	 */
	class Tab : public QWidget, public std::enable_shared_from_this<tab::Tab> {
		friend class tab_widget::TabWidget;
		friend class main_window_tab_widget::MainWindowTabWidget;
		friend class main_window_tab::MainWindowTab;

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit Tab(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Tab constructor
			 */
			explicit Tab(QWidget * parent);

			/**
			 * @brief Function: virtual ~Tab()
			 *
			 * Tab destructor
			 */
			virtual ~Tab();

			/**
			 * @brief Function: int getLoadProgress() const
			 *
			 * \return load progress percentage
			 *
			 * This function returns the load progress percentage
			 */
			int getLoadProgress() const;

			/**
			 * @brief Function: int getVerticalScroll() const
			 *
			 * \return vertical scroll percentage
			 *
			 * This function returns the vertical scroll percentage
			 */
			int getVerticalScroll() const;

			/**
			 * @brief Function: int getHorizontalScroll() const
			 *
			 * \return horizontal scroll percentage
			 *
			 * This function returns the horizontal scroll percentage
			 */
			int getHorizontalScroll() const;

			/**
			 * @brief Function: tab_shared_types::load_status_e getLoadStatus() const
			 *
			 * \return load status
			 *
			 * This function returns the load status of the tab
			 */
			tab_shared_types::load_status_e getLoadStatus() const;

			/**
			 * @brief Function: std::shared_ptr<web_engine_page::WebEnginePage> getPage() const
			 *
			 * \return tab web page object
			 *
			 * This function returns the page linked to the tab
			 */
			std::shared_ptr<web_engine_page::WebEnginePage> getPage() const;

			/**
			 * @brief Function: virtual void configure(std::shared_ptr<tab_bar::TabBar> tabBar)
			 *
			 * This function configures the tab
			 */
			virtual void configure(std::shared_ptr<tab_bar::TabBar> tabBar);

		signals:
			/**
			 * @brief Function: void loadProgressChanged(const int & value) const
			 *
			 * \param value: value of the loading.
			 *
			 * This function is a signal to notify that the load progress value has changed
			 */
			void loadProgressChanged(const int & value) const;

			/**
			 * @brief Function: void verticalScrollChanged(const int & value) const
			 *
			 * \param value: value of the vertical scroll.
			 *
			 * This function is a signal to notify that the vertical scroll position changed
			 */
			void verticalScrollChanged(const int & value) const;

			/**
			 * @brief Function: void horizontalScrollChanged(const int & value) const
			 *
			 * \param value: value of the horizontal scroll.
			 *
			 * This function is a signal to notify that the horizontal scroll position changed
			 */
			void horizontalScrollChanged(const int & value) const;

			/**
			 * @brief Function: void historyItemChanged(const global_enums::element_position_e & position)
			 *
			 * \param position: position in the history.
			 *
			 * This function is a signal to notify the current position in the history of the tab
			 */
			void historyItemChanged(const global_enums::element_position_e & position);

		protected:

			/**
			 * @brief Function: virtual void connectSignals()
			 *
			 * This function connects signals and slots within tabs
			 */
			virtual void connectSignals() = 0;

			/**
			 * @brief Function: virtual void reload()
			 *
			 * This function reloads the content of the tab
			 */
			virtual void reload() = 0;

			/**
			 * @brief Function: void resize(const QSize size)
			 *
			 * \param size: new size of the view
			 *
			 * Reimplement resize
			 */
			void resize(const QSize size);

		private:

			/**
			 * @brief web engine view
			 *
			 */
			std::shared_ptr<web_engine_view::WebEngineView> view;

			/**
			 * @brief load manager
			 *
			 */
			std::shared_ptr<tab_load_manager::TabLoadManager> loadManager;

			/**
			 * @brief seach class
			 *
			 */
			std::shared_ptr<tab_search::TabSearch> search;

			/**
			 * @brief history class
			 *
			 */
			std::shared_ptr<tab_history::TabHistory> history;

			/**
			 * @brief settings
			 *
			 */
			std::shared_ptr<web_engine_settings::WebEngineSettings> settings;

			/**
			 * @brief scroll manager
			 *
			 */
			std::shared_ptr<tab_scroll_manager::TabScrollManager> scrollManager;

			/**
			 * @brief progress bar value setter connection
			 *
			 */
			QMetaObject::Connection progressValueConnection;

			/**
			 * @brief vertical scroll value setter connection
			 *
			 */
			QMetaObject::Connection vScrollValueConnection;

			/**
			 * @brief horizontal scroll value setter connection
			 *
			 */
			QMetaObject::Connection hScrollValueConnection;

			/**
			 * @brief history item change connection
			 *
			 */
			QMetaObject::Connection historyItemChangedConnection;

			// Components
			/**
			 * @brief Function: void setView(std::shared_ptr<web_engine_view::WebEngineView> value)
			 *
			 * \param value: view to use
			 *
			 * This function sets the tab view
			 */
			void setView(std::shared_ptr<web_engine_view::WebEngineView> value);

			/**
			 * @brief Function: std::shared_ptr<web_engine_view::WebEngineView> getView() const
			 *
			 * \return tab view
			 *
			 * This function returns the tab view
			 */
			std::shared_ptr<web_engine_view::WebEngineView> getView() const;

			/**
			 * @brief Function: void setLoadManager(std::shared_ptr<tab_load_manager::TabLoadManager> value)
			 *
			 * \param value: load manager to use
			 *
			 * This function sets the load manager
			 */
			void setLoadManager(std::shared_ptr<tab_load_manager::TabLoadManager> value);

			/**
			 * @brief Function: std::shared_ptr<tab_load_manager::TabLoadManager> getLoadManager() const
			 *
			 * \return load manager
			 *
			 * This function returns the load manager
			 */
			std::shared_ptr<tab_load_manager::TabLoadManager> getLoadManager() const;

			/**
			 * @brief Function: void setSearch(std::shared_ptr<tab_search::TabSearch> value)
			 *
			 * \param value: search to use
			 *
			 * This function sets the tab search
			 */
			void setSearch(std::shared_ptr<tab_search::TabSearch> value);

			/**
			 * @brief Function: std::shared_ptr<tab_search::TabSearch> getSearch() const
			 *
			 * \return tab search
			 *
			 * This function returns the tab search
			 */
			std::shared_ptr<tab_search::TabSearch> getSearch() const;

			/**
			 * @brief Function: void setHistory(std::shared_ptr<tab_history::TabHistory> value)
			 *
			 * \param value: history of the tab
			 *
			 * This function sets the history of the page
			 */
			void setHistory(std::shared_ptr<tab_history::TabHistory> value);

			/**
			 * @brief Function: std::shared_ptr<tab_history::TabHistory> getHistory() const
			 *
			 * \return history of the tab
			 *
			 * This function returns the history of the page
			 */
			std::shared_ptr<tab_history::TabHistory> getHistory() const;

			/**
			 * @brief Function: void setSettings(std::shared_ptr<web_engine_settings::WebEngineSettings> value)
			 *
			 * \param value: settings of the web page
			 *
			 * This function stores the pointer to the web page settings into web setting class
			 */
			void setSettings(std::shared_ptr<web_engine_settings::WebEngineSettings> value);

			/**
			 * @brief Function: std::shared_ptr<web_engine_settings::WebEngineSettings> getSettings() const
			 *
			 * \return tab settings
			 *
			 * This function returns the settings
			 */
			std::shared_ptr<web_engine_settings::WebEngineSettings> getSettings() const;

			/**
			 * @brief Function: void setScrollManager(std::shared_ptr<tab_scroll_manager::TabScrollManager> value)
			 *
			 * \param value: scroll manager to use
			 *
			 * This function sets the scroll manager
			 */
			void setScrollManager(std::shared_ptr<tab_scroll_manager::TabScrollManager> value);

			/**
			 * @brief Function: std::shared_ptr<tab_scroll_manager::TabScrollManager> getScrollManager() const
			 *
			 * \return scroll manager
			 *
			 * This function returns the scroll manager
			 */
			std::shared_ptr<tab_scroll_manager::TabScrollManager> getScrollManager() const;

			/**
			 * @brief Function: virtual virtual void find(const find_settings::FindSettings & settings) const final
			 *
			 * \param settings: settings of the search.
			 *
			 * This function searches text in a webpage
			 */
			virtual void find(const find_settings::FindSettings & settings) const final;

			/**
			 * @brief Function: virtual void historyPrev() const
			 *
			 * This function goes to the previous item in the history of a webpage, if it exists
			 */
			virtual void historyPrev() const;

			/**
			 * @brief Function: virtual void historyNext() const
			 *
			 * This function goes to the next item in the history of a webpage, if it exists
			 */
			virtual void historyNext() const;

			/**
			 * @brief Function: virtual void scrollUp() const
			 *
			 * This function request the scroll manager to scroll up
			 */
			virtual void scrollUp() const;

			/**
			 * @brief Function: virtual void scrollDown() const
			 *
			 * This function request the scroll manager to scroll down
			 */
			virtual void scrollDown() const;

			/**
			 * @brief Function: virtual void scrollLeft() const
			 *
			 * This function request the scroll manager to scroll left
			 */
			virtual void scrollLeft() const;

			/**
			 * @brief Function: virtual void scrollRight() const
			 *
			 * This function request the scroll manager to scroll right
			 */
			virtual void scrollRight() const;

			/**
			 * @brief Disable move and copy constructors and operator= overloading for class Tab
			 *
			 */
			DISABLE_COPY_MOVE(Tab)

	};
}
/** @} */ // End of TabGroup group

#endif // TAB_H
