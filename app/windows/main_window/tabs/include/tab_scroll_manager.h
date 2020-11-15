#ifndef MAIN_WINDOW_TAB_SCROLL_MANAGER_H
#define MAIN_WINDOW_TAB_SCROLL_MANAGER_H
/**
 * @copyright
 * @file tab_scroll_manager.h
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"
#include "base/tabs/include/tab_scroll_manager.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	class Tab;

	/**
	 * @brief TabScrollManager class
	 *
	 */
	class TabScrollManager final : public tab_scroll_manager::TabScrollManager {
		friend class main_window::Tab;

		public:
			/**
			 * @brief Function: explicit TabScrollManager(QWidget * parent, std::weak_ptr<main_window::Tab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar)
			 *
			 * \param parent: parent widget
			 * \param tabBar: tab bar
			 * \param tab: tab
			 *
			 * Main Window Tab Scroll Manager constructor
			 */
			explicit TabScrollManager(QWidget * parent, std::weak_ptr<main_window::Tab> browserTab, const std::shared_ptr<tab_bar::TabBar> & tabBar);

			/**
			 * @brief Function: virtual ~TabScrollManager()
			 *
			 * Main Window Tab Scroll Manager destructor
			 */
			virtual ~TabScrollManager();

			/**
			 * @brief Function: std::shared_ptr<main_window::Tab> getTab() const
			 *
			 * \return tab the scroll manager belongs to
			 *
			 * This function returns the tab the scroll manager belongs to
			 */
			std::shared_ptr<main_window::Tab> getTab() const;

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overscrolling for class TabScrollManager
			 *
			 */
			DISABLE_COPY_MOVE(TabScrollManager)

	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_SCROLL_MANAGER_H
