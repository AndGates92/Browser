#ifndef MAIN_WINDOW_TAB_LOAD_MANAGER_H
#define MAIN_WINDOW_TAB_LOAD_MANAGER_H
/**
 * @copyright
 * @file load_manager.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Main Window Tab Load Manager header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/shared/enums.h"
#include "app/shared/constructor_macros.h"
#include "app/base/tabs/load_manager.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class Tab;

			/**
			 * @brief LoadManager class
			 *
			 */
			class LoadManager final : public app::base::tab::LoadManager {
				friend class app::main_window::tab::Tab;

				public:
					/**
					 * @brief Function: explicit LoadManager(QWidget * parent)
					 *
					 * \param parent: parent widget
					 *
					 * Main Window Tab Load Manager constructor
					 */
					explicit LoadManager(QWidget * parent);

					/**
					 * @brief Function: virtual ~LoadManager()
					 *
					 * Main Window Tab Load Manager destructor
					 */
					virtual ~LoadManager();

				protected:

				private:

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class LoadManager
					 *
					 */
					DISABLE_COPY_MOVE(LoadManager)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_TAB_LOAD_MANAGER_H
