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
#include <qt5/QtWidgets/QLabel>
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
			 * @brief Function: explicit MainWindowCtrl(main_window_core::MainWindowCore * windowCore, QWidget * parent = QString::null)
			 *
			 * \param windowCore: main window core
			 * \param parent: parent window
			 * \param tabIndex: current tab index
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrl(main_window_core::MainWindowCore * windowCore, QWidget * parent = Q_NULLPTR);

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

		public slots:
			/**
			 * @brief Function: void setShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function is the slot to set the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void setShortcutEnabledProperty(bool enabled);

			void openNewTab();

		protected:

		signals:
			/**
			 * @brief Function: void searchCurrentTabSignal(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the current tab
			 */
			void searchCurrentTabSignal(QString search);

			/**
			 * @brief Function: void toggleShowMenubarSignal()
			 *
			 * This function is the signal to show or hide the menubar
			 */
			void toggleShowMenubarSignal();

			/**
			 * @brief Function: void closeSignal()
			 *
			 * This function is a signal to close the main window
			 */
			void closeWindowSignal();

			/**
			 * @brief Function: void requestCurrentTabIndexSignal()
			 *
			 * This function is a signal to initiate the request of the current tab index
			 */
			void requestCurrentTabIndexSignal();

			/**
			 * @brief Function: void sendCurrentTabIndexSignal(int tabIndex)
			 *
			 * \param tabIndex: index of the current tab
			 *
			 * This function is a signal to send the value of the current tab index
			 */
			void sendCurrentTabIndexSignal(int tabIndex);

			/**
			 * @brief Function: void openNewTabSignal(int index)
			 *
			 * \param index: index of tab to close
			 *
			 * This function is a signal to close a tab
			 */
			void openNewTabSignal();

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

			/**
			 * @brief Function: void setAllShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void setAllShortcutEnabledProperty(bool enabled);

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
			 * @brief Function: void getCurrentTabIndex()
			 *
			 * This function sends the current tab index
			 */
			void getCurrentTabIndex();
	};

}
/** @} */ // End of MainWindowCtrlGroup group

#endif // MAIN_WINDOW_CTRL_H
