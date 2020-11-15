#ifndef MAIN_WINDOW_CTRL_WRAPPER_H
#define MAIN_WINDOW_CTRL_WRAPPER_H
/**
 * @copyright
 * @file ctrl_wrapper.h
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

#include "windows/main_window/common/include/shared_types.h"
#include "windows/main_window/window/include/ctrl.h"
#include "windows/main_window/window/include/ctrl_tab.h"
#include "common/include/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

namespace main_window {

	class MainWindow;

	/**
	 * @brief CtrlWrapper class
	 *
	 */
	class CtrlWrapper final : public QWidget, public main_window::Base {
		friend class main_window::MainWindow;

		public:

			/**
			 * @brief Function: explicit CtrlWrapper(QWidget * parent, const std::shared_ptr<main_window::Core> & core)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 *
			 * Main window control constructor
			 */
			explicit CtrlWrapper(QWidget * parent, const std::shared_ptr<main_window::Core> & core);

			/**
			 * @brief Function: virtual ~CtrlWrapper()
			 *
			 * Main window control constructor
			 */
			virtual ~CtrlWrapper();

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
			 * @brief Function: void keyPressEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event) override;

		protected:

		private:

			/**
			 * @brief Main window control
			 *
			 */
			std::unique_ptr<main_window::Ctrl> winctrl;

			/**
			 * @brief main window tab control
			 *
			 */
			std::unique_ptr<main_window::CtrlTab> tabctrl;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class CtrlWrapper
			 *
			 */
			DISABLE_COPY_MOVE(CtrlWrapper)

	};

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CTRL_WRAPPER_H
