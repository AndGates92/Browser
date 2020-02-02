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
#include "main_window_ctrl_base.h"

/** @defgroup MainWindowCtrlTabGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabUserInput)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabSearch)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabTabs)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlTabUrl)

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

		/**
		 * @brief Path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		const QString commandFilePath("json/");

		/**
		 * @brief Filename storing informations about commands and shortcuts
		 *
		 */
		const QString commandFileName("tab_commands.json");

		/**
		 * @brief Full path towards JSON file storing informations about commands and shortcuts
		 *
		 */
		const QString commandFileFullPath(commandFilePath + commandFileName);
	}


	/**
	 * @brief MainWindowCtrlTab class
	 *
	 */
	class MainWindowCtrlTab : public main_window_ctrl_base::MainWindowCtrlBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlTab(main_window_core::MainWindowCore * windowCore, QWidget * parent = Q_NULLPTR)
			 *
			 * \param windowCore: main window core
			 * \param parent: parent window
			 *
			 * Main window tab control constructor
			 */
			explicit MainWindowCtrlTab(main_window_core::MainWindowCore * windowCore, QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: ~MainWindowCtrlTab()
			 *
			 * Main window tab control destructor
			 */
			~MainWindowCtrlTab();

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
			 * @brief Function: void executeCommand(QString command)
			 *
			 * \param command: command to execute.
			 *
			 * This function executes a command on a based on user input
			 */
			void executeCommand(QString command);

		public slots:

			/**
			 * @brief Function: void setUpOpenNewTab()
			 *
			 * This function prepares to add a new tab and automatically search the user input
			 */
			void setUpOpenNewTab();

		protected:

		private slots:

			/**
			 * @brief Function: void setUpRefreshTabUrl()
			 *
			 * This function refresh the url in a tab
			 */
			void setUpRefreshTabUrl();

			/**
			 * @brief Function: void setUpMoveLeft()
			 *
			 * This function moves left in the tabs. It will wrap around if the number of position leads to a negative tab index
			 */
			void setUpMoveLeft();

			/**
			 * @brief Function: void setUpMoveRight()
			 *
			 * This function moves right in the tabs. It will wrap around if the number of position leads to a tab index bigger than the max tab counter
			 */
			void setUpMoveRight();

			/**
			 * @brief Function: void setUpMoveTab()
			 *
			 * This function moves tab to. It will wrap around if the number of position leads to a negative tab index
			 */
			void setUpMoveTab();

			/**
			 * @brief Function: void setUpNewSearchTab()
			 *
			 * This function prepares to search the user input
			 */
			void setUpNewSearchTab();

			/**
			 * @brief Function: void setUpCloseTab()
			 *
			 * This function closes a tab
			 */
			void setUpCloseTab();

			/**
			 * @brief Function: void updateInfoSlot(int index)
			 *
			 * \param index: index of tab either closed or clicked
			 *
			 * This function is the slot to update the info label
			 * Note: argument index is not used
			 */
			void updateInfoSlot(int index);

		private:

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
			 * @brief Function: void executeActionOnTab(int index = main_window_ctrl_tab::emptyUserInput)
			 *
			 * \param index: index of tab to execute action on
			 *
			 * This function executes action on a based on user input
			 */
			void executeActionOnTab(int index = main_window_ctrl_tab::emptyUserInput);

			/**
			 * @brief Function: void executeActionOnOffset(int offset)
			 *
			 * \param offset: offset of tab to execute action on
			 *
			 * This function executes action on a based on user input
			 */
			void executeActionOnOffset(int offset);

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

			/**
			 * @brief Function: void updateWebsite(int index)
			 *
			 * \param index: index of tab where the website has to be updated
			 *
			 * This function updates the website label
			 */
			void updateWebsite(int index);

			// ================================ START ACTIONS ========================================//
			/**
			 * @brief Function: void addNewTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function adds a new tab to the main window
			 */
			void addNewTab(QString search);

			/**
			 * @brief Function: void newSearchTab(int index, QString search)
			 *
			 * \param index: tab index to be searched
			 * \param search: string to search
			 *
			 * This function search on the tab at index index
			 */
			void newSearchTab(int index, QString search);

			/**
			 * @brief Function: void searchCurrentTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the current tab
			 */
			void searchCurrentTab(QString search);

			/**
			 * @brief Function: void refreshUrl(int tabIndex)
			 *
			 * \param tabIndex: tab index to refresh
			 *
			 * This function refreshes a tab as specified by the user
			 */
			void refreshUrl(int tabIndex);

			/**
			 * @brief Function: void closeTab(int index)
			 *
			 * \param index: index of tab to close
			 *
			 * This function is a signal to close a tab
			 */
			void closeTab(int index);

			/**
			 * @brief Function: void moveTab(int tabIndex)
			 *
			 * \param tabIndex: index to move the tab to
			 *
			 * This function moves the current tab to a different tab as specified by the user
			 */
			void moveTab(int tabIndex);

			/**
			 * @brief Function: void moveCursor(int tabIndex)
			 *
			 * \param tabIndex: index to move the cursor to
			 *
			 * This function moves the cursor to a different tab as specified by the user
			 */
			void moveCursor(int tabIndex);
			// ================================ END ACTIONS ========================================//

	};

}
/** @} */ // End of MainWindowCtrlTabGroup group

#endif // MAIN_WINDOW_CTRL_TAB_H
