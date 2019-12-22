#ifndef MAIN_WINDOW_CTRL_H
#define MAIN_WINDOW_CTRL_H
/**
 * @copyright
 * @file main_window_ctrl.h
 * @author Andrea Gianarda
 * @date 23th of September 2019
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
#include "file_menu.h"
#include "edit_menu.h"
#include "tab_widget.h"

/** @defgroup MainWindowCtrlGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlCenterWindow)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlUserInput)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlSearch)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabs)

namespace main_window_ctrl {

	namespace {
		/**
		 * @brief invalid tab index - default value of optional argument index of executeActionOnTab function
		 *
		 */
		const int emptyUserInput = -1;

		/**
		 * @brief https string
		 *
		 */
		const QString https("https://");

		/**
		 * @brief www string
		 *
		 */
		const QString www("www.");

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		const QString defaultSearchEngine(https + www + "duckduckgo.com/?q=%1");

	}

	/**
	 * @brief MainWindowCtrl class
	 *
	 */
	class MainWindowCtrl : public QObject {

		Q_OBJECT

		// ================================ START ENUMERATION ========================================//
		/**
		 * @brief states
		 *
		 */
		typedef enum class state_list {
			IDLE,             /**< Idle state - no user input */
			COMMAND,          /**< Typing command */
			OPEN_TAB,         /**< Open new tab */
			CLOSE_TAB,        /**< Close tab */
			REFRESH_TAB,      /**< Refresh tab */
			MOVE_LEFT,        /**< Move to tab to the left */
			MOVE_RIGHT,       /**< Move to tab to the right */
			TAB_MOVE,         /**< Move tab */
			SEARCH            /**< Search on same tab */
		} state_e;

		/**
		 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::state_e & state)
		 *
		 * \param os: output stream
		 * \param state: state to print
		 *
		 * Overload << operator to print state
		 */
		friend QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::state_e & state);

		/**
		 * @brief move info
		 *
		 */
		typedef enum class move_value_list {
			IDLE,             /**< Idle state - no user input */
			LEFT,             /**< Left movement */
			RIGHT,            /**< Right movement */
			ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
		} move_value_e;

		/**
		 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::move_value_e & value_type)
		 *
		 * \param os: output stream
		 * \param value_type: move type
		 *
		 * Overload << operator to print the move type
		 */
		friend QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::move_value_e & value_type);

		/**
		 * @brief text action 
		 *
		 */
		typedef enum class text_action_list {
			SET,              /**< Set text */
			APPEND,           /**< Append text */
			CLEAR             /**< Clear text */
		} text_action_e;

		/**
		 * @brief Function: QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::text_action_e & action)
		 *
		 * \param os: output stream
		 * \param action: action applied on the text in the status bar
		 *
		 * Overload << operator to print text action in the status bar
		 */
		friend QDebug & operator<< (QDebug & os, const main_window_ctrl::MainWindowCtrl::text_action_e & action);

		// ================================ END ENUMERATION ========================================//

		public:

			/**
			 * @brief Function: explicit MainWindowCtrl(QWidget * parent = Q_NULLPTR, int tabIndex = 0, int tabCount = 0)
			 *
			 * \param parent: parent window
			 * \param tabIndex: current tab index
			 * \param tabCount: number of opened tabs
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrl(QWidget * parent = Q_NULLPTR, int tabIndex = 0, int tabCount = 0);

		protected:

		public slots:

			/**
			 * @brief Function: void openNewTabSlot()
			 *
			 * This function opens a new tab
			 */
			void openNewTabSlot();

			/**
			 * @brief Function: void setShortcutEnabledPropertySlot(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function is the slot to set the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void setShortcutEnabledPropertySlot(bool enabled);

			/**
			 * @brief Function: void receiveCurrentTabIndex(int tabIndex)
			 *
			 * \param tabIndex: index of the current tab
			 *
			 * This function retrieves the current tab index 
			 */
			void receiveCurrentTabIndex(int tabIndex);

			/**
			 * @brief Function: void receiveTabCount(int tabCount)
			 *
			 * \param tabCount: number of tabs
			 *
			 * This function retrieves the number of open tabs
			 */
			void receiveTabCount(int tabCount);

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard 
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

		signals:
			/**
			 * @brief Function: void updateInfoActionSignal(int index)
			 *
			 * \param index: index of tab either closed or clicked
			 *
			 * This function is a signal to inform that the info label needs to be updated
			 */
			void updateInfoActionSignal(int index);

			/**
			 * @brief Function: void updateWebsiteSignal(int index)
			 *
			 * \param index: index of tab where the website is searched
			 *
			 * This function is a signal to inform that the info label needs to be updated
			 */
			void updateWebsiteSignal(int index);

			/**
			 * @brief Function: void updateUserInputBarSignal(QString textLabel)
			 *
			 * \param text: text to write to userInputText
			 *
			 * This function is the signal to update the user input label
			 */
			void updateUserInputBarSignal(QString textLabel);

			/**
			 * @brief Function: void enabledPropertyMenuSignal(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void enabledPropertyMenuSignal(bool enabled);

			/**
			 * @brief Function: void moveSignal(int offset, int sign = 0, const main_window_shared_types::object_type_e & object = main_window_shared_types::object_type_e::UNKNOWN)
			 *
			 * \param offset: offset of tab to execute action on
			 * \param sign: direction of movement. -1 for left move and 1 for right move
			 * \param object: object to move: cursor or tab
			 *
			 * This function is a signal to move to a different tab as specified by the user
			 */
			void moveSignal(int offset, int sign = 0, const main_window_shared_types::object_type_e & object = main_window_shared_types::object_type_e::UNKNOWN);

			/**
			 * @brief Function: void refreshUrlSignal(int offset, int sign = 0)
			 *
			 * \param offset: offset of tab to execute action on
			 * \param sign: direction of movement. -1 for left move and 1 for right move
			 *
			 * This function is a signal to refresh a tab as specified by the user
			 */
			void refreshUrlSignal(int offset, int sign = 0);

			/**
			 * @brief Function: void addNewTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function is a signal to add a new tab to the main window
			 */
			void addNewTabSignal(QString search);

			/**
			 * @brief Function: void closeTabSignal(int index)
			 *
			 * \param index: index of tab to close
			 *
			 * This function is a signal to close a tab
			 */
			void closeTabSignal(int index);

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
			 * @brief Function: void requestTabCountSignal()
			 *
			 * This function is a signal to initiate the request of the number of opened tabs
			 */
			void requestTabCountSignal();

		private slots:

			/**
			 * @brief Function: void closeSlot()
			 *
			 * This function closes the main window
			 */
			void closeWindowSlot();

			/**
			 * @brief Function: void refreshUrlSlot()
			 *
			 * This function refresh the url in a tab
			 */
			void refreshUrlSlot();

			/**
			 * @brief Function: void moveLeftSlot()
			 *
			 * This function moves left in the tabs. It will wrap around if the number of position leads to a negative tab index
			 */
			void moveLeftSlot();

			/**
			 * @brief Function: void moveRightSlot()
			 *
			 * This function moves right in the tabs. It will wrap around if the number of position leads to a tab index bigger than the max tab counter
			 */
			void moveRightSlot();

			/**
			 * @brief Function: void moveTabToSlot()
			 *
			 * This function moves tab to. It will wrap around if the number of position leads to a negative tab index
			 */
			void moveTabToSlot();

			/**
			 * @brief Function: void newSearchTabSlot()
			 *
			 * This function changes the title of a tab
			 */
			void newSearchTabSlot();

			/**
			 * @brief Function: void toggleShowMenubarSlot()
			 *
			 * This function is the slot to show/hide the menubar
			 */
			void toggleShowMenubarSlot();

			/**
			 * @brief Function: void closeTabSlot()
			 *
			 * This function closes a tab
			 */
			void closeTabSlot();

		private:

			/**
			 * @brief state of the main window
			 *
			 */
			main_window_ctrl::MainWindowCtrl::state_e mainWindowState;

			/**
			 * @brief type of value of movements in tab bar
			 *
			 */
			main_window_ctrl::MainWindowCtrl::move_value_e moveValueType;

			/**
			 * @brief parent widget
			 *
			 */
			QWidget * parent;

			/**
			 * @brief current tab index
			 *
			 */
			int currentTabIndex;

			/**
			 * @brief number of opened tabs
			 *
			 */
			int tabCount;

			/**
			 * @brief user text
			 *
			 */
			QString userText;

			// ================================ START SHORTCUTS ========================================//
			/**
			 * @brief shortcut to toggle visibility of the menu bar
			 *
			 */
			QShortcut * toggleShowMenuBarKey;

			/**
			 * @brief shortcut to open a new tab
			 *
			 */
			QShortcut * openNewTabKey;

			/**
			 * @brief shortcut to search in the current tab
			 *
			 */
			QShortcut * newSearchTabKey;

			/**
			 * @brief shortcut to close a tab
			 *
			 */
			QShortcut * closeTabKey;

			/**
			 * @brief shortcut to move left in the tab bar
			 *
			 */
			QShortcut * moveLeftKey;

			/**
			 * @brief shortcut to move right in the tab bar
			 *
			 */
			QShortcut * moveRightKey;

			/**
			 * @brief shortcut to refresh the content of a bar
			 *
			 */
			QShortcut * refreshUrlKey;

			/**
			 * @brief shortcut to move tab to the left
			 *
			 */
			QShortcut * moveTabToKey;

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
			 * @brief Function: void executeAction(int userInput = main_window_ctrl::emptyUserInput)
			 *
			 * \param userInput: user input to execute action. If not specified it is default to main_window_ctrl::emptyUserInput
			 *
			 * This function executes action on a based on user input
			 */
			void executeAction(int userInput = main_window_ctrl::emptyUserInput);

			/**
			 * @brief Function: void executeActionOnTab(int index)
			 *
			 * \param index: index of tab to execute action on
			 *
			 * This function executes action on a based on user input
			 */
			void executeActionOnTab(int index);

			/**
			 * @brief Function: void executeActionOnOffset(int offset)
			 *
			 * \param offset: offset of tab to execute action on
			 *
			 * This function executes action on a based on user input
			 */
			void executeActionOnOffset(int offset);

			/**
			 * @brief Function: void processTabIndex(QString userInputStr)
			 *
			 * This function converts the string indexStr to an integer and executes desired action on it
			 */
			void processTabIndex(QString userInputStr);

			/**
			 * @brief Function: void setAllMenuShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of menus of the main window
			 */
			void setAllMenuShortcutEnabledProperty(bool enabled);

			/**
			 * @brief Function: void setAllWindowShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window
			 */
			void setAllWindowShortcutEnabledProperty(bool enabled);

			/**
			 * @brief Function: void setAllShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void setAllShortcutEnabledProperty(bool enabled);

			/**
			 * @brief Function: QString getActionName()
			 *
			 * \return string with the text to display as action
			 *
			 * Get action name to display in the userInputText label
			 */
			QString getActionName();

			/**
			 * @brief Function: void formUserInputStr(const main_window_ctrl::MainWindowCtrl::text_action_e action, QString text = Q_NULLPTR)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function is the slot to update the user input label
			 */
			void formUserInputStr(const main_window_ctrl::MainWindowCtrl::text_action_e action, QString text = Q_NULLPTR);

			/**
			 * @brief Function: main_window_shared_types::object_type_e setAffectedObject()
			 *
			 * This function return the object type the action is applied on
			 */
			main_window_shared_types::object_type_e setAffectedObject();

			/**
			 * @brief Function: void updateCurrentTabIndex()
			 *
			 * This function retrieves the current tab index 
			 */
			void updateCurrentTabIndex();

			/**
			 * @brief Function: void updateTabCount()
			 *
			 * This function updates the number of open tabs
			 */
			void updateTabCount();
	};

}
/** @} */ // End of MainWindowCtrlGroup group

#endif // MAIN_WINDOW_CTRL_H
