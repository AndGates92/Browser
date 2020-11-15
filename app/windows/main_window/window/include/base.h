#ifndef MAIN_WINDOW_BASE_H
#define MAIN_WINDOW_BASE_H
/**
 * @copyright
 * @file base.h
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window base class header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>

#include "windows/main_window/window/include/core.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	/**
	 * @brief CtrlBase class
	 *
	 */
	class Base {

		public:

			/**
			 * @brief Function: explicit Base(const std::shared_ptr<main_window::Core> & windowCore)
			 *
			 * \param windowCore: main window core
			 *
			 * Main window base constructor
			 */
			explicit Base(const std::shared_ptr<main_window::Core> & windowCore);

			// Move and copy constructor
			/**
			 * @brief Function: Base(const main_window::Base & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Base copy constructor
			 */
			explicit Base(const main_window::Base & rhs);

			/**
			 * @brief Function: Base(main_window::Base && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Base move constructor
			 */
			explicit Base(main_window::Base && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: Base & operator=(const main_window::Base & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Base copy assignment operator
			 */
			Base & operator=(const main_window::Base & rhs);

			/**
			 * @brief Function: Base & operator=(main_window::Base && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Base move assignment operator
			 */
			Base & operator=(main_window::Base && rhs);

			/**
			 * @brief Function: virtual ~Base()
			 *
			 * Main window base class destructor
			 */
			virtual ~Base();

			/**
			 * @brief Function: const std::shared_ptr<main_window::Core> & getCore() const
			 *
			 * \return window core
			 *
			 * This method return the window core
			 */
			const std::shared_ptr<main_window::Core> & getCore() const;

		protected:
			/**
			 * @brief main window core
			 *
			 */
			std::shared_ptr<main_window::Core> core;

		private:
	};

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_BASE_H
