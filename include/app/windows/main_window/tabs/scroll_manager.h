#ifndef MAIN_WINDOW_TAB_SCROLL_MANAGER_H
#define MAIN_WINDOW_TAB_SCROLL_MANAGER_H
/**
 * @copyright
 * @file scroll_manager.h
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"
#include "app/base/tabs/scroll_manager.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class Tab;

			/**
			 * @brief ScrollManager class
			 *
			 */
			class ScrollManager final : public app::base::tab::ScrollManager {
				friend class app::main_window::tab::Tab;

				public:
					/**
					 * @brief Function: explicit ScrollManager(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> browserTab, const std::shared_ptr<app::base::tab::TabBar> & tabBar)
					 *
					 * \param parent: parent widget
					 * \param browserTab: tab
					 * \param tabBar: tab bar
					 *
					 * Main Window Tab Scroll Manager constructor
					 */
					explicit ScrollManager(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> browserTab, const std::shared_ptr<app::base::tab::TabBar> & tabBar);

					/**
					 * @brief Function: virtual ~ScrollManager()
					 *
					 * Main Window Tab Scroll Manager destructor
					 */
					virtual ~ScrollManager();

					/**
					 * @brief Function: std::shared_ptr<app::main_window::tab::Tab> getTab() const
					 *
					 * \return tab the scroll manager belongs to
					 *
					 * This function returns the tab the scroll manager belongs to
					 */
					std::shared_ptr<app::main_window::tab::Tab> getTab() const;

				protected:

				private:

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overscrolling for class ScrollManager
					 *
					 */
					DISABLE_COPY_MOVE(ScrollManager)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_SCROLL_MANAGER_H
