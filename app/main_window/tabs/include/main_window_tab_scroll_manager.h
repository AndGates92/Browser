#ifndef MAIN_WINDOW_TAB_SCROLL_MANAGER_H
#define MAIN_WINDOW_TAB_SCROLL_MANAGER_H
/**
 * @copyright
 * @file main_window_tab_scroll_manager.h
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "constructor_macros.h"
#include "tab_scroll_manager.h"

/** @defgroup MainWindowTabScrollManagerGroup Main Window Tab Scroll Manager Doxygen Group
 *  Main Window Tab Scroll Manager functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabScrollManagerOverall)

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_tab_scroll_manager {

	/**
	 * @brief MainWindowTabScrollManager class
	 *
	 */
	class MainWindowTabScrollManager final : public tab_scroll_manager::TabScrollManager {
		friend class main_window_tab::MainWindowTab;

		public:
			/**
			 * @brief Function: explicit MainWindowTabScrollManager(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> browserTab, std::shared_ptr<tab_bar::TabBar> tabBar)
			 *
			 * \param parent: parent widget
			 * \param tabBar: tab bar
			 * \param tab: tab
			 *
			 * Main Window Tab Scroll Manager constructor
			 */
			explicit MainWindowTabScrollManager(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> browserTab, std::shared_ptr<tab_bar::TabBar> tabBar);

			/**
			 * @brief Function: virtual ~MainWindowTabScrollManager()
			 *
			 * Main Window Tab Scroll Manager destructor
			 */
			virtual ~MainWindowTabScrollManager();

			/**
			 * @brief Function: std::shared_ptr<main_window_tab::MainWindowTab> getTab() const
			 *
			 * \return tab the scroll manager belongs to
			 *
			 * This function returns the tab the scroll manager belongs to
			 */
			std::shared_ptr<main_window_tab::MainWindowTab> getTab() const;

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overscrolling for class MainWindowTabScrollManager
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabScrollManager)

	};
}
/** @} */ // End of MainWindowTabScrollManagerGroup group

#endif // MAIN_WINDOW_TAB_SCROLL_MANAGER_H
