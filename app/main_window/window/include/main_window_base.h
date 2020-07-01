#ifndef MAIN_WINDOW_BASE_H
#define MAIN_WINDOW_BASE_H
/**
 * @copyright
 * @file main_window_ctrl_base.h
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window base class header file
*/

#include <memory>

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
			 * @brief Function: explicit MainWindowBase(std::shared_ptr<main_window_core::MainWindowCore> core)
			 *
			 * \param core: main window core
			 *
			 * Main window base constructor
			 */
			explicit MainWindowBase(std::shared_ptr<main_window_core::MainWindowCore> core);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowBase(const main_window_base::MainWindowBase & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowBase copy constructor
			 */
			explicit MainWindowBase(const main_window_base::MainWindowBase & rhs);

			/**
			 * @brief Function: MainWindowBase(main_window_base::MainWindowBase && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowBase move constructor
			 */
			explicit MainWindowBase(main_window_base::MainWindowBase && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowBase & operator=(const main_window_base::MainWindowBase & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowBase copy assignment operator
			 */
			MainWindowBase & operator=(const main_window_base::MainWindowBase & rhs);

			/**
			 * @brief Function: MainWindowBase & operator=(main_window_base::MainWindowBase && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowBase move assignment operator
			 */
			MainWindowBase & operator=(main_window_base::MainWindowBase && rhs);

			/**
			 * @brief Function: virtual ~MainWindowBase()
			 *
			 * Main window base class destructor
			 */
			virtual ~MainWindowBase();

		protected:
			/**
			 * @brief main window core
			 *
			 */
			std::shared_ptr<main_window_core::MainWindowCore> windowCore;

		private:
	};

}
/** @} */ // End of MainWindowBaseGroup group

#endif // MAIN_WINDOW_BASE_H
