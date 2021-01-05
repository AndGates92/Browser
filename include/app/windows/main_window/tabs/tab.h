#ifndef MAIN_WINDOW_TAB_H
#define MAIN_WINDOW_TAB_H
/**
 * @copyright
 * @file tab.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/base/tabs/tab.h"
#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"
#include "app/windows/main_window/tabs/types.h"
#include "app/windows/main_window/shared/shared_types.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class TabWidget;
			class WebEngineView;
			class WebEnginePage;
			class WebEngineSettings;
			class History;
			class Search;
			class LoadManager;
			class ScrollManager;

			/**
			 * @brief Tab class
			 *
			 */
			class Tab final : public app::base::tab::Tab {
				friend class app::main_window::tab::TabWidget;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit Tab(QWidget * parent, const QString & search)
					 *
					 * \param search: search in the current tab
					 * \param parent: parent widget
					 *
					 * Main Window Tab constructor
					 */
					explicit Tab(QWidget * parent, const QString & search);

					/**
					 * @brief Function: virtual ~Tab()
					 *
					 * Main Window Tab destructor
					 */
					virtual ~Tab();

					/**
					 * @brief Function: const app::main_window::page_type_e & getType() const
					 *
					 * \return page type
					 *
					 * This function returns page type
					 */
					const app::main_window::page_type_e & getType() const;

					/**
					 * @brief Function: const QString getSource() const
					 *
					 * \return source of the page
					 *
					 * This function returns the source of the page
					 */
					const QString getSource() const;

					/**
					 * @brief Function: std::shared_ptr<app::main_window::tab::WebEnginePage> getPage() const
					 *
					 * \return tab web page object
					 *
					 * This function returns the page linked to the tab
					 */
					std::shared_ptr<app::main_window::tab::WebEnginePage> getPage() const;

					/**
					 * @brief Function: const QString & getSearchText() const
					 *
					 * \return text searched by the user for this tab
					 *
					 * This function returns the text searched by the user for this tab
					 */
					const QString & getSearchText() const;

					/**
					 * @brief Function: int getVerticalScrollPercentage() const
					 *
					 * \return the vertical position of the scrollbar
					 *
					 * This function returns the vertical position of the scrollbar
					 */
					int getVerticalScrollPercentage() const;

					/**
					 * @brief Function: void configure(const std::shared_ptr<app::base::tab::TabBar> & tabBar, const app::main_window::page_type_e & type, const QString & src, const void * data)
					 *
					 * \param type: tab type
					 * \param src: source of the tab
					 * \param data: tab extra data
					 * \param tabBar: tab bar
					 *
					 * This function configures the main window tab
					 */
					void configure(const std::shared_ptr<app::base::tab::TabBar> & tabBar, const app::main_window::page_type_e & type, const QString & src, const void * data);

					/**
					 * @brief Function: virtual void keyReleaseEvent(QKeyEvent * event) override final
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles event coming from the keyboard
					 * Re-implement key released event
					 */
					virtual void keyReleaseEvent(QKeyEvent * event) override final;

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
					 * @brief Function: void searchResultChanged(const app::main_window::tab::search_data_s & data) const
					 *
					 * \param data: search result data.
					 *
					 * This function is a signal to notify that the search changed
					 */
					void searchResultChanged(const app::main_window::tab::search_data_s & data) const;

					/**
					 * @brief Function: void findTextFinished(const bool & found)
					 *
					 * \param found: boolean stating whether the text was found or not.
					 *
					 * This function is a signal to notify whether a search was successful
					 */
					void findTextFinished(const bool & found);

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
					 * @brief Function: void setSearchText(const QString & value)
					 *
					 * \param value: text searched by the user for this tab
					 *
					 * This function sets the text searched by the user for this tab
					 */
					void setSearchText(const QString & value);

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::WebEngineView> getView() const
					 *
					 * \return tab view
					 *
					 * This function returns the tab view
					 */
					const std::shared_ptr<app::main_window::tab::WebEngineView> getView() const;

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::LoadManager> getLoadManager() const
					 *
					 * \return load manager
					 *
					 * This function returns the load manager
					 */
					const std::shared_ptr<app::main_window::tab::LoadManager> getLoadManager() const;

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::Search> getSearch() const
					 *
					 * \return tab search
					 *
					 * This function returns the tab search
					 */
					const std::shared_ptr<app::main_window::tab::Search> getSearch() const;

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::History> getHistory() const
					 *
					 * \return history of the tab
					 *
					 * This function returns the history of the page
					 */
					const std::shared_ptr<app::main_window::tab::History> getHistory() const;

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::WebEngineSettings> getSettings() const
					 *
					 * \return tab settings
					 *
					 * This function returns the settings
					 */
					const std::shared_ptr<app::main_window::tab::WebEngineSettings> getSettings() const;

					/**
					 * @brief Function: const std::shared_ptr<app::main_window::tab::ScrollManager> getScrollManager() const
					 *
					 * \return scroll manager
					 *
					 * This function returns the scroll manager
					 */
					const std::shared_ptr<app::main_window::tab::ScrollManager> getScrollManager() const;

					/**
					 * @brief Function: void updateView(const std::shared_ptr<app::main_window::tab::WebEngineView> & value)
					 *
					 * \param value: view to use
					 *
					 * This function updates the current view as well as informations derived from it
					 */
					void updateView(const std::shared_ptr<app::main_window::tab::WebEngineView> & value);

					/**
					 * @brief Function: void reload() override
					 *
					 * This function reloads the content of the page
					 */
					void reload() override;

					/**
					 * @brief Function: std::shared_ptr<app::main_window::tab::Tab> shared_from_this()
					 *
					 * \return shared pointer of this
					 *
					 * This function returns a shared pointer to this
					 */
					std::shared_ptr<app::main_window::tab::Tab> shared_from_this();

					/**
					 * @brief Function: std::weak_ptr<app::main_window::tab::Tab> sweak_from_this()
					 *
					 * \return weak pointer of this
					 *
					 * This function returns a weak pointer to this
					 */
					std::weak_ptr<app::main_window::tab::Tab> weak_from_this();

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Tab
					 *
					 */
					DISABLE_COPY_MOVE(Tab)

				private slots:
					/**
					 * @brief Function: void postprocessLoadFinished(const bool & success)
					 *
					 * This function postprocessing the end of a page load
					 */
					void postprocessLoadFinished(const bool & success);

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_H
