#ifndef MAIN_WINDOW_CTRL_H
#define MAIN_WINDOW_CTRL_H
/**
 * @copyright
 * @file main_window_ctrl.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtWidgets/QWidget>

#include "main_window_shared_types.h"
#include "main_window_ctrl_tab.h"
#include "constructor_macros.h"

/** @defgroup MainWindowCtrlGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlUserInput)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlSearch)

namespace main_window_ctrl {

	namespace {
		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		const QString commandFilePath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		const QString commandFileName("global_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		const QString commandFileFullPath(commandFilePath + commandFileName);
	}

	/**
	 * @brief MainWindowCtrl class
	 *
	 */
	class MainWindowCtrl final : public main_window_ctrl_base::MainWindowCtrlBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrl(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * window, QWidget * parent = QString::null)
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 * \param window: window controlled
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrl(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * window, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~MainWindowCtrl()
			 *
			 * Main window control constructor
			 */
			~MainWindowCtrl();

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

			/**
			 * @brief Function: void keyReleaseEvent(QKeyEvent * event) override
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			void keyReleaseEvent(QKeyEvent * event) override;

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
			 * @brief Function: virtual void setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes a command on a based on user input and the state the window is in
			 */
			virtual void setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) override;

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
