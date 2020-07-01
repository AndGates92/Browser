#ifndef MAIN_WINDOW_WRAPPER_H
#define MAIN_WINDOW_WRAPPER_H
/**
 * @copyright
 * @file main_window_wrapper.h
 * @author Andrea Gianarda
 * @date 30th of January 2020
 * @brief Main Window wrapper class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "main_window_base.h"
#include "main_window_ctrl.h"
#include "main_window_ctrl_tab.h"
#include "main_window.h"

/** @defgroup MainWindowWrapperGroup Main Window Wrapper Doxygen Group
 *  Main Window wrapper functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWrapperOverall)

namespace main_window_wrapper {

	/**
	 * @brief MainWindowWrapper class
	 *
	 */
	class MainWindowWrapper final {

		public:
			/**
			 * @brief Function: explicit MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window wrapper constructor
			 */
			explicit MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowWrapper(const main_window_wrapper::MainWindowWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowWrapper copy constructor
			 */
			explicit MainWindowWrapper(const main_window_wrapper::MainWindowWrapper & rhs);

			/**
			 * @brief Function: MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowWrapper move constructor
			 */
			explicit MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowWrapper & operator=(const main_window_wrapper::MainWindowWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowWrapper copy assignment operator
			 */
			MainWindowWrapper & operator=(const main_window_wrapper::MainWindowWrapper & rhs);

			/**
			 * @brief Function: MainWindowWrapper & operator=(main_window_wrapper::MainWindowWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowWrapper move assignment operator
			 */
			MainWindowWrapper & operator=(main_window_wrapper::MainWindowWrapper && rhs);

			/**
			 * @brief Function: virtual ~MainWindowWrapper()
			 *
			 * Main window wrapper destructor
			 */
			virtual ~MainWindowWrapper();

			/**
			 * @brief Function: void show()
			 *
			 * Show main window
			 */
			void show();

		protected:

		private:

			/**
			 * @brief Main window
			 *
			 */
			std::unique_ptr<main_window::MainWindow> window;

	};

}

/** @} */ // End of MainWindowWrapperGroup group

#endif // MAIN_WINDOW_WRAPPER_H
