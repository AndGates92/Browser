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
#include <QtWidgets/QWidget>

#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"
#include "windows/common/include/find_settings.h"
#include "base/tabs/include/web_engine_view.h"
#include "base/tabs/include/web_engine_settings.h"
#include "base/tabs/include/load_manager.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */
namespace app {

	namespace main_window {
		namespace tab {
			class Tab;
			class TabWidget;
		}
	}

	namespace base {

		namespace tab {

			class TabBar;

			class TabWidget;

			class Search;

			class ScrollManager;

			class History;

			/**
			 * @brief Tab class
			 *
			 */
			class Tab : public QWidget, public std::enable_shared_from_this<app::base::tab::Tab> {
				friend class app::base::tab::TabWidget;
				friend class app::main_window::tab::TabWidget;
				friend class app::main_window::tab::Tab;

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
					 * @brief Function: app::base::tab::load_status_e getLoadStatus() const
					 *
					 * \return load status
					 *
					 * This function returns the load status of the tab
					 */
					app::base::tab::load_status_e getLoadStatus() const;

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::WebEnginePage> getPage() const
					 *
					 * \return tab web page object
					 *
					 * This function returns the page linked to the tab
					 */
					std::shared_ptr<app::base::tab::WebEnginePage> getPage() const;

					/**
					 * @brief Function: virtual void configure(std::shared_ptr<app::base::tab::TabBar> tabBar)
					 *
					 * This function configures the tab
					 */
					virtual void configure(std::shared_ptr<app::base::tab::TabBar> tabBar);

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
					 * @brief Function: void historyItemChanged(const app::shared::element_position_e & position)
					 *
					 * \param position: position in the history.
					 *
					 * This function is a signal to notify the current position in the history of the tab
					 */
					void historyItemChanged(const app::shared::element_position_e & position);

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
					std::shared_ptr<app::base::tab::WebEngineView> view;

					/**
					 * @brief load manager
					 *
					 */
					std::shared_ptr<app::base::tab::LoadManager> loadManager;

					/**
					 * @brief seach class
					 *
					 */
					std::shared_ptr<app::base::tab::Search> search;

					/**
					 * @brief history class
					 *
					 */
					std::shared_ptr<app::base::tab::History> history;

					/**
					 * @brief settings
					 *
					 */
					std::shared_ptr<app::base::tab::WebEngineSettings> settings;

					/**
					 * @brief scroll manager
					 *
					 */
					std::shared_ptr<app::base::tab::ScrollManager> scrollManager;

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
					 * @brief Function: void setView(std::shared_ptr<app::base::tab::WebEngineView> value)
					 *
					 * \param value: view to use
					 *
					 * This function sets the tab view
					 */
					void setView(const std::shared_ptr<app::base::tab::WebEngineView> & value);

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::WebEngineView> getView() const
					 *
					 * \return tab view
					 *
					 * This function returns the tab view
					 */
					std::shared_ptr<app::base::tab::WebEngineView> getView() const;

					/**
					 * @brief Function: void setLoadManager(const std::shared_ptr<app::base::tab::LoadManager> & value)
					 *
					 * \param value: load manager to use
					 *
					 * This function sets the load manager
					 */
					void setLoadManager(const std::shared_ptr<app::base::tab::LoadManager> & value);

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::LoadManager> getLoadManager() const
					 *
					 * \return load manager
					 *
					 * This function returns the load manager
					 */
					std::shared_ptr<app::base::tab::LoadManager> getLoadManager() const;

					/**
					 * @brief Function: void setSearch(const std::shared_ptr<app::base::tab::Search> & value)
					 *
					 * \param value: search to use
					 *
					 * This function sets the tab search
					 */
					void setSearch(const std::shared_ptr<app::base::tab::Search> & value);

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::Search> getSearch() const
					 *
					 * \return tab search
					 *
					 * This function returns the tab search
					 */
					std::shared_ptr<app::base::tab::Search> getSearch() const;

					/**
					 * @brief Function: void setHistory(const std::shared_ptr<app::base::tab::History> & value)
					 *
					 * \param value: history of the tab
					 *
					 * This function sets the history of the page
					 */
					void setHistory(const std::shared_ptr<app::base::tab::History> & value);

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::History> getHistory() const
					 *
					 * \return history of the tab
					 *
					 * This function returns the history of the page
					 */
					std::shared_ptr<app::base::tab::History> getHistory() const;

					/**
					 * @brief Function: void setSettings(const std::shared_ptr<app::base::tab::WebEngineSettings> & value)
					 *
					 * \param value: settings of the web page
					 *
					 * This function stores the pointer to the web page settings into web setting class
					 */
					void setSettings(const std::shared_ptr<app::base::tab::WebEngineSettings> & value);

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::WebEngineSettings> getSettings() const
					 *
					 * \return tab settings
					 *
					 * This function returns the settings
					 */
					std::shared_ptr<app::base::tab::WebEngineSettings> getSettings() const;

					/**
					 * @brief Function: void setScrollManager(const std::shared_ptr<app::base::tab::ScrollManager> & value)
					 *
					 * \param value: scroll manager to use
					 *
					 * This function sets the scroll manager
					 */
					void setScrollManager(const std::shared_ptr<app::base::tab::ScrollManager> & value);

					/**
					 * @brief Function: std::shared_ptr<app::base::tab::ScrollManager> getScrollManager() const
					 *
					 * \return scroll manager
					 *
					 * This function returns the scroll manager
					 */
					std::shared_ptr<app::base::tab::ScrollManager> getScrollManager() const;

					/**
					 * @brief Function: virtual virtual void find(const app::windows::shared::FindSettings & settings) const final
					 *
					 * \param settings: settings of the search.
					 *
					 * This function searches text in a webpage
					 */
					virtual void find(const app::windows::shared::FindSettings & settings) const final;

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

	}

}
/** @} */ // End of TabGroup group

#endif // TAB_H
