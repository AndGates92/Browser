#ifndef MAIN_WINDOW_TAB_LOAD_MANAGER_H
#define MAIN_WINDOW_TAB_LOAD_MANAGER_H
/**
 * @copyright
 * @file main_window_tab_load_manager.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab Load Manager header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "constructor_macros.h"
#include "tab_load_manager.h"

/** @defgroup MainWindowTabLoadManagerGroup Main Window Tab Load Manager Doxygen Group
 *  Main Window Tab Load Manager functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowTabLoadManagerOverall)

namespace main_window_tab {
	class MainWindowTab;
}

namespace main_window_tab_load_manager {

	/**
	 * @brief MainWindowTabLoadManager class
	 *
	 */
	class MainWindowTabLoadManager : public tab_load_manager::TabLoadManager {
		friend class main_window_tab::MainWindowTab;

		public:
			/**
			 * @brief Function: explicit MainWindowTabLoadManager(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Main Window Tab Load Manager constructor
			 */
			explicit MainWindowTabLoadManager(QWidget * parent);

			/**
			 * @brief Function: virtual ~MainWindowTabLoadManager()
			 *
			 * Main Window Tab Load Manager destructor
			 */
			virtual ~MainWindowTabLoadManager();

		protected:

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowTabLoadManager
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowTabLoadManager)

	};
}
/** @} */ // End of MainWindowTabLoadManagerGroup group

#endif // MAIN_WINDOW_TAB_LOAD_MANAGER_H
