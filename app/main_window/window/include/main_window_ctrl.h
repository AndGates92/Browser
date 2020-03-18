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
	class MainWindowCtrl : public main_window_ctrl_base::MainWindowCtrlBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrl(std::shared_ptr<main_window_core::MainWindowCore> core, QWidget * parent = QString::null)
			 *
			 * \param core: main window core
			 * \param parent: parent window
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrl(std::shared_ptr<main_window_core::MainWindowCore> core, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~MainWindowCtrlTab()
			 *
			 * Main window control constructor
			 */
			~MainWindowCtrl();

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
			 * @brief Function: void keyReleaseEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			void keyReleaseEvent(QKeyEvent * event);

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
			 * @brief main window tab control
			 *
			 */
			main_window_ctrl_tab::MainWindowCtrlTab * tabctrl;

			// ================================ START SHORTCUTS ========================================//
			/**
			 * @brief shortcut to toggle visibility of the menu bar
			 *
			 */
			QShortcut * toggleShowMenuBarKey;

			/**
			 * @brief shortcut to close the main window
			 *
			 */
			QShortcut * closeKey;
			// ================================ END SHORTCUTS ========================================//

			/**
			 * @brief Function: void createShortcuts()
			 *
			 * This function creates shortcuts for the items on the window
			 */
			void createShortcuts();

			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots within main window controller
			 */
			void connectSignals();

			/**
			 * @brief Function: void executeCommand(QString command)
			 *
			 * \param command: command to execute.
			 *
			 * This function executes a command on a based on user input
			 */
			void executeCommand(QString command);

			/**
			 * @brief Function: void setStateAction(main_window_shared_types::state_e windowState, QKeyEvent * event)
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function executes a command on a based on user input and the state the window is in
			 */
			void setStateAction(main_window_shared_types::state_e windowState, QKeyEvent * event);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowCtrl(const main_window_ctrl::MainWindowCtrl & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowCtrl copy constructor
			 */
			explicit MainWindowCtrl(const main_window_ctrl::MainWindowCtrl & rhs) = delete;

			/**
			 * @brief Function: MainWindowCtrl(main_window_ctrl::MainWindowCtrl && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowCtrl move constructor
			 */
			explicit MainWindowCtrl(main_window_ctrl::MainWindowCtrl && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowCtrl & operator=(const main_window_ctrl::MainWindowCtrl & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowCtrl copy assignment operator
			 */
			MainWindowCtrl & operator=(const main_window_ctrl::MainWindowCtrl & rhs) = delete;

			/**
			 * @brief Function: MainWindowCtrl & operator=(main_window_ctrl::MainWindowCtrl && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowCtrl move assignment operator
			 */
			MainWindowCtrl & operator=(main_window_ctrl::MainWindowCtrl && rhs) = delete;

	};

}
/** @} */ // End of MainWindowCtrlGroup group

#endif // MAIN_WINDOW_CTRL_H
