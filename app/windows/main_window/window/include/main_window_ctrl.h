#ifndef MAIN_WINDOW_CTRL_H
#define MAIN_WINDOW_CTRL_H
/**
 * @copyright
 * @file main_window_ctrl.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

#include "main_window_shared_types.h"
#include "main_window_ctrl_tab.h"
#include "constructor_macros.h"

/** @defgroup MainWindowCtrlGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

namespace main_window_ctrl {

	/**
	 * @brief MainWindowCtrl class
	 *
	 */
	class MainWindowCtrl final : public main_window_ctrl_base::MainWindowCtrlBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrl(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrl(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core);

			/**
			 * @brief Function: virtual ~MainWindowCtrl()
			 *
			 * Main window control constructor
			 */
			virtual ~MainWindowCtrl();

			/**
			 * @brief Function: virtual void actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes an action when a key is released
			 */
			virtual void actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override;


		protected:

		signals:
			/**
			 * @brief Function: void closeWindowSignal()
			 *
			 * This function is a signal to close the main window
			 */
			void closeWindowSignal();

		private slots:

			/**
			 * @brief Function: void close()
			 *
			 * This function closes the main window
			 */
			void closeWindow();

			/**
			 * @brief Function: void toggleShowMenubar()
			 *
			 * This function is the slot to show/hide the menubar
			 */
			void toggleShowMenubar();

		private:

			/**
			 * @brief Function: virtual void createExtraShortcuts() override
			 *
			 * This function creates shortcuts for the items on the window
			 */
			virtual void createExtraShortcuts() override;

			/**
			 * @brief Function: virtual void connectExtraSignals() override
			 *
			 * This function connects signals and slots within main window controller
			 */
			virtual void connectExtraSignals() override;

			/**
			 * @brief Function: virtual void postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) override
			 *
			 * \param previousState: state the window was into before the transition.
			 *
			 * This function is abstract and it defines action to be taken immediately after the window has changed state
			 */
			virtual void postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) override;

			/**
			 * @brief Function: virtual bool isValidWindowState(const main_window_shared_types::state_e & windowState) override
			 *
			 * \param windowState: state the window is requested to go into.
			 *
			 * \return boolean whether the state is valid or not. true if the state is valid and false otherwise.
			 *
			 * This function checks that the state is valid
			 */
			virtual bool isValidWindowState(const main_window_shared_types::state_e & windowState) override;

			/**
			 * @brief Function: virtual void prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes a command on a based on user input and the state the window is in
			 */
			virtual void prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override;

			/**
			 * @brief Function: virtual void executeAction(const main_window_shared_types::state_e & windowState) override
			 *
			 * \param windowState: state the window is into.
			 *
			 * This function executes the actions required when the window is a given state
			 */
			virtual void executeAction(const main_window_shared_types::state_e & windowState) override;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowCtrl
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowCtrl)

	};

}
/** @} */ // End of MainWindowCtrlGroup group

#endif // MAIN_WINDOW_CTRL_H
