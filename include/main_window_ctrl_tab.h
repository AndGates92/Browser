#ifndef MAIN_WINDOW_CTRL_TAB_H
#define MAIN_WINDOW_CTRL_TAB_H
/**
 * @copyright
 * @file main_window_ctrl_tab.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Tab Control header file
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

/** @defgroup MainWindowCtrlTabGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabCenterWindow)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabUserInput)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabSearch)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabTabs)

namespace main_window_ctrl_tab {
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
	 * @brief MainWindowCtrlTab class
	 *
	 */
	class MainWindowCtrlTab : public QObject {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlTab(QWidget * parent = Q_NULLPTR, int tabIndex = 0, int tabCount = 0)
			 *
			 * \param parent: parent window
			 * \param tabIndex: current tab index
			 * \param tabCount: number of opened tabs
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrlTab(QWidget * parent = Q_NULLPTR, int tabIndex = 0, int tabCount = 0);

			/**
			 * @brief Function: main_window_shared_types::move_value_e getMoveValueType()
			 *
			 * \return move value type
			 *
			 * This function returns the move value type
			 */
			main_window_shared_types::move_value_e getMoveValueType();

			/**
			 * @brief Function: void setAllTabShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window
			 */
			void setAllTabShortcutEnabledProperty(bool enabled);

			/**
			 * @brief Function: void processTabIndex(QString userInputStr)
			 *
			 * This function converts the string indexStr to an integer and executes desired action on it
			 */
			void processTabIndex(QString userInputStr);

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

			/**
			 * @brief Function: QString createUrl(QString search)
			 *
			 * \param search: string to search
			 * \return string with URL
			 *
			 * This function is creates the URL based on the input from the user
			 * If the user writes down a URL himself/herself, it will return it adding, if required, https
			 * If the user is writing a strign to search, it will be searched in the chosen search engine
			 */
			QString createUrl(QString search);

			/**
			 * @brief Function: QString createTabInfo()
			 *
			 * \return string with tab information
			 *
			 * This function is creates the string to provide tab info to users
			 */
			QString createTabInfo();

		public slots:

			/**
			 * @brief Function: void openNewTab()
			 *
			 * This function opens a new tab
			 */
			void openNewTab();

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
			 * @brief Function: void receiveState(main_window_shared_types::state_e state)
			 *
			 * \param state: state of the main window controller
			 *
			 * This function retrieves the state of the main window controller 
			 */
			void receiveState(main_window_shared_types::state_e state);

		protected:

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
			 * @brief Function: void moveCursorSignal(int tabIndex)
			 *
			 * \param tabIndex: index to move the cursor to
			 *
			 * This function is a signal to move the cursor to a different tab as specified by the user
			 */
			void moveCursorSignal(int tabIndex);

			/**
			 * @brief Function: void moveTabSignal(int tabIndex)
			 *
			 * \param tabIndex: index to move the tab to
			 *
			 * This function is a signal to move the current tab to another position as specified by the user
			 */
			void moveTabSignal(int tabIndex);

			/**
			 * @brief Function: void refreshUrlSignal(int tabIndex)
			 *
			 * \param tabIndex: tab index to refresh
			 *
			 * This function is a signal to refresh a tab as specified by the user
			 */
			void refreshUrlSignal(int tabIndex);

			/**
			 * @brief Function: void addNewTabSignal(QString search)
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

			/**
			 * @brief Function: void requestStateSignal()
			 *
			 * This function is a signal to initiate the request of the main window state
			 */
			void requestStateSignal();

			/**
			 * @brief Function: void setStateSignal(main_window_shared_types::state_e state)
			 *
			 * \param state: state of the main window controller
			 *
			 * This function is a signal to set the state of the main window controller
			 */
			void setStateSignal(main_window_shared_types::state_e state);

			/**
			 * @brief Function: void setShortcutEnabledPropertySignal(bool enabled)
			 *
			 * This function is a signal to set the enabled property of shortcuts
			 * Once an action is under processing, shortcuts are disabled to ensure that they don't intefere
			 */
			void setShortcutEnabledPropertySignal(bool enabled);

			/**
			 * @brief Function: void setUserInputStrSignal(const main_window_shared_types::text_action_e action, QString text = QString::null)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function is the slot to update the user input label
			 */
			void setUserInputStrSignal(const main_window_shared_types::text_action_e action, QString text = QString::null);

		private slots:

			/**
			 * @brief Function: void refreshTabUrl()
			 *
			 * This function refresh the url in a tab
			 */
			void refreshTabUrl();

			/**
			 * @brief Function: void moveLeft()
			 *
			 * This function moves left in the tabs. It will wrap around if the number of position leads to a negative tab index
			 */
			void moveLeft();

			/**
			 * @brief Function: void moveRight()
			 *
			 * This function moves right in the tabs. It will wrap around if the number of position leads to a tab index bigger than the max tab counter
			 */
			void moveRight();

			/**
			 * @brief Function: void moveTabTo()
			 *
			 * This function moves tab to. It will wrap around if the number of position leads to a negative tab index
			 */
			void moveTabTo();

			/**
			 * @brief Function: void newSearchTab()
			 *
			 * This function changes the title of a tab
			 */
			void newSearchTab();

			/**
			 * @brief Function: void closeTab()
			 *
			 * This function closes a tab
			 */
			void closeTab();

		private:

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
			 * @brief state of the main window
			 *
			 */
			main_window_shared_types::state_e mainWindowState;

			/**
			 * @brief type of value of movements in tab bar
			 *
			 */
			main_window_shared_types::move_value_e moveValueType;

			// ================================ START SHORTCUTS ========================================//
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

			/**
			 * @brief Function: void updateState()
			 *
			 * This function retrieves the state of the main window control
			 */
			void updateState();

			/**
			 * @brief Function: void executeCommand(QString command)
			 *
			 * \param command: command to execute.
			 *
			 * This function executes a command on a based on user input
			 */
			void executeCommand(QString command);

			/**
			 * @brief Function: void executeTabAction(int userInput = main_window_ctrl_tab::emptyUserInput)
			 *
			 * \param userInput: user input to execute action. If not specified it is default to main_window_ctrl_tab::emptyUserInput
			 *
			 * This function executes action on a based on user input
			 */
			void executeTabAction(int userInput = main_window_ctrl_tab::emptyUserInput);

			/**
			 * @brief Function: main_window_shared_types::object_type_e setAffectedObject()
			 *
			 * This function return the object type the action is applied on
			 */
			main_window_shared_types::object_type_e setAffectedObject();

			/**
			 * @brief Function: void convertToAbsTabIndex(int offset = main_window_ctrl_tab::emptyUserInput, int sign = 0)
			 *
			 * \param offset: relatinve tab index
			 * \param sign: direction of tab to apply action on: -1 for left move and 1 for right move
			 *
			 * This function moves to a different tab as specified by the user
			 */
			void convertToAbsTabIndex(int offset = main_window_ctrl_tab::emptyUserInput, int sign = 0);
	};

}
/** @} */ // End of MainWindowCtrlTabGroup group

#endif // MAIN_WINDOW_CTRL_TAB_H
