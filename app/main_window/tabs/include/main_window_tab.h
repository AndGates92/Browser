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
#include "main_window_tab_search.h"
#include "main_window_tab_load_manager.h"

/** @defgroup TabGroup Main Window Tab Doxygen Group
 *  Main Window Tab functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabOverall)

namespace main_window_tab {

	/**
	 * @brief MainWindowTab class
	 *
	 */
	class MainWindowTab final : public tab::Tab {

		public:
			/**
			 * @brief Function: explicit MainWindowTab(QWidget * parent, const main_window_shared_types::page_type_e type = main_window_shared_types::page_type_e::UNKNOWN, const QString & src = QString::null, const void * data = nullptr)
			 *
			 * \param type: tab type
			 * \param src: source of the tab
			 * \param data: tab extra data
			 * \param parent: parent widget
			 *
			 * Main Window Tab constructor
			 */
			explicit MainWindowTab(QWidget * parent, const main_window_shared_types::page_type_e type = main_window_shared_types::page_type_e::UNKNOWN, const QString & src = QString::null, const void * data = nullptr);

			/**
			 * @brief Function: virtual ~MainWindowTab()
			 *
			 * Main Window Tab destructor
			 */
			virtual ~MainWindowTab();

			/**
			 * @brief Function: void reload() override
			 *
			 * This function reloads the content of the page
			 */
			void reload() override;

			/**
			 * @brief Function: main_window_web_engine_view::MainWindowWebEngineView * getView() const
			 *
			 * \return tab view
			 *
			 * This function returns the load manager
			 */
			main_window_web_engine_view::MainWindowWebEngineView * getView() const;

			/**
			 * @brief Function: main_window_tab_load_manager::MainWindowTabLoadManager * getLoadManager() const
			 *
			 * \return load manager
			 *
			 * This function returns the load manager
			 */
			main_window_tab_load_manager::MainWindowTabLoadManager * getLoadManager() const;

			/**
			 * @brief Function: main_window_tab_search::MainWindowTabSearch * getSearch() const
			 *
			 * \return tab search
			 *
			 * This function returns the load manager
			 */
			main_window_tab_search::MainWindowTabSearch * getSearch() const;

		protected:

			/**
			 * @brief Function: void connectSignals() override
			 *
			 * This function connects signals and slots within main window controller tabs
			 */
			void connectSignals() override;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTab
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTab)

	};
}
/** @} */ // End of TabGroup group

#endif // MAIN_WINDOW_TAB_H
