#ifndef MAIN_WINDOW_CTRL_TYPES_H
#define MAIN_WINDOW_CTRL_TYPES_H
/**
 * @copyright
 * @file types.h
 * @author Andrea Gianarda
 * @date 08th of January 2021
 * @brief Main Window Control Types header file
*/

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

#include "app/windows/main_window/shared/shared_types.h"
#include <QtCore/QString>

namespace app {

	namespace main_window {

		namespace window {

			/**
			 * @brief search data changed
			 *
			 */
			typedef struct ctrl_data_t {
				app::main_window::state_e state;	/**< window state */
				QString commandArgument;		/**< command argument */
			} ctrl_data_s;

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CTRL_TYPES_H
