#ifndef MAIN_WINDOW_BASE_H
#define MAIN_WINDOW_BASE_H
/**
 * @copyright
 * @file main_window_ctrl_base.h
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window base class header file
*/

#include <qt5/QtCore/QLoggingCategory>

#include "main_window_core.h"

/** @defgroup MainWindowBaseGroup Main Window Doxygen Group
 *  Main Window base functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowBaseOverall)

namespace main_window_base {

	/**
	 * @brief MainWindowCtrlBase class
	 *
	 */
	class MainWindowBase {

		public:

			/**
			 * @brief Function: explicit MainWindowBase(main_window_core::MainWindowCore * core)
			 *
			 * \param core: main window core
			 *
			 * Main window base constructor
			 */
			explicit MainWindowBase(main_window_core::MainWindowCore * core);

			/**
			 * @brief Function: ~MainWindowBase()
			 *
			 * Main window base class destructor
			 */
			virtual ~MainWindowBase();

		protected:
			/**
			 * @brief main window core
			 *
			 */
			main_window_core::MainWindowCore * windowCore;

		private:
	};

}
/** @} */ // End of MainWindowBaseGroup group

#endif // MAIN_WINDOW_BASE_H
