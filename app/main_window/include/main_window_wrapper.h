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
#include <qt5/QtWidgets/QMainWindow>

#include "main_window_core.h"
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
	class MainWindowWrapper {

	public:
			/**
			 * @brief Function: explicit MainWindowWrapper(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window wrapper constructor
			 */
			explicit MainWindowWrapper(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~MainWindowWrapper()
			 *
			 * Main window wrapper destructor
			 */
			~MainWindowWrapper();

			/**
			 * @brief Function: void show()
			 *
			 * Show main window
			 */
			void show();

	protected:

	private:

		/**
		 * @brief Main window core
		 *
		 */
		main_window_core::MainWindowCore * mainWindowCore;

		/**
		 * @brief Main window
		 *
		 */
		main_window::MainWindow * window;

		/**
		 * @brief Main window control
		 *
		 */
		main_window_ctrl::MainWindowCtrl * ctrl;



	};

}

/** @} */ // End of MainWindowWrapperGroup group

#endif // MAIN_WINDOW_WRAPPER_H
