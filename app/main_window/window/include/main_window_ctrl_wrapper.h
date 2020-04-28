#ifndef MAIN_WINDOW_CTRL_WRAPPER_H
#define MAIN_WINDOW_CTRL_WRAPPER_H
/**
 * @copyright
 * @file main_window_ctrl_wrapper.h
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtWidgets/QWidget>

#include "main_window_shared_types.h"
#include "main_window_ctrl.h"
#include "main_window_ctrl_tab.h"
#include "constructor_macros.h"

/** @defgroup MainWindowCtrlWrapperGroup Main Window Doxygen Group
 *  Main Window control wrapper functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlWrapperOverall)

namespace main_window_ctrl_wrapper {

	/**
	 * @brief MainWindowCtrlWrapper class
	 *
	 */
	class MainWindowCtrlWrapper final : public QWidget, public main_window_base::MainWindowBase {

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlWrapper(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * window, QWidget * parent = QString::null)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 * \param window: window controlled
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrlWrapper(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * window, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~MainWindowCtrlWrapper()
			 *
			 * Main window control constructor
			 */
			~MainWindowCtrlWrapper();

			/**
			 * @brief Function: void keyReleaseEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			void keyReleaseEvent(QKeyEvent * event) override;

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

			/**
			 * @brief Function: main_window_ctrl::MainWindowCtrl * getWinCtrl()
			 *
			 * \return the window controller
			 *
			 * This function returns the window controller
			 */
			main_window_ctrl::MainWindowCtrl * getWinCtrl();

			/**
			 * @brief Function: main_window_ctrl_tab::MainWindowCtrlTab * getTabCtrl()
			 *
			 * \return the tab controller
			 *
			 * This function returns the tab controller
			 */
			main_window_ctrl_tab::MainWindowCtrlTab * getTabCtrl();

		protected:

		private:

			/**
			 * @brief window controlled
			 *
			 */
			QWidget * window;

			/**
			 * @brief Main window control
			 *
			 */
			main_window_ctrl::MainWindowCtrl * winctrl;

			/**
			 * @brief main window tab control
			 *
			 */
			main_window_ctrl_tab::MainWindowCtrlTab * tabctrl;

			/**
			 * @brief Function: void resetWindowState()
			 *
			 * this function resets the window state to IDLE and clear user input
			 */
			void resetWindowState();

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowCtrlWrapper
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowCtrlWrapper)

	};

}
/** @} */ // End of MainWindowCtrlWrapperGroup group

#endif // MAIN_WINDOW_CTRL_WRAPPER_H
