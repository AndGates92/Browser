#ifndef MAIN_WINDOW_TAB_LOAD_MANAGER_H
#define MAIN_WINDOW_TAB_LOAD_MANAGER_H
/**
 * @copyright
 * @file tab_load_manager.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab Load Manager header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "common/include/global_enums.h"
#include "common/include/constructor_macros.h"
#include "base/tabs/include/tab_load_manager.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	class Tab;

	/**
	 * @brief TabLoadManager class
	 *
	 */
	class TabLoadManager final : public tab_load_manager::TabLoadManager {
		friend class main_window::Tab;

		public:
			/**
			 * @brief Function: explicit TabLoadManager(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Main Window Tab Load Manager constructor
			 */
			explicit TabLoadManager(QWidget * parent);

			/**
			 * @brief Function: virtual ~TabLoadManager()
			 *
			 * Main Window Tab Load Manager destructor
			 */
			virtual ~TabLoadManager();

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabLoadManager
			 *
			 */
			DISABLE_COPY_MOVE(TabLoadManager)

	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_LOAD_MANAGER_H
