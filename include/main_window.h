#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
/**
 * @copyright
 * @file main_window.h
 * @author Andrea Gianarda
 * @date 23th of September 2019
 * @brief Main Window header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtWidgets/QWidget>

#include "file_menu.h"
#include "edit_menu.h"
#include "tab_widget.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCenterWindow)
Q_DECLARE_LOGGING_CATEGORY(mainWindowUserInput)
Q_DECLARE_LOGGING_CATEGORY(mainWindowSearch)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabs)

namespace main_window {

	namespace {
		/**
		 * @brief bottom information label height
		 *
		 */
		const int labelHeight = 20;

		/**
		 * @brief horizontal spacing between widgets
		 *
		 */
		const int horizontalWidgetSpacing = 0;

		/**
		 * @brief vertical spacing between widgets
		 *
		 */
		const int verticalWidgetSpacing = 0;

		/**
		 * @brief left margin between widget and window
		 *
		 */
		const int leftMargin = 0;

		/**
		 * @brief right margin between widget and window
		 *
		 */
		const int rightMargin = 0;

		/**
		 * @brief top margin between widget and window
		 *
		 */
		const int topMargin = 0;

		/**
		 * @brief bottom margin between widget and window
		 *
		 */
		const int bottomMargin = 0;

		/**
		 * @brief invalid tab index - default value of optional argument index of executeActionOnTab function
		 *
		 */
		const int emptyUserInput = 0;

		/**
		 * @brief default serch engine is duckduckgo
		 *
		 */
		const QString defaultSearchEngine("http://www.duckduckgo.com/?q=%1");


	}

	class MainWindow : public QMainWindow {

		Q_OBJECT

		// ================================ START ENUMERATION ========================================//
		/**
		 * @brief states
		 *
		 */
		typedef enum class state_list {
			IDLE,             /**< Idle state - no user input */
			OPEN_TAB,         /**< Open new tab */
			CLOSE_TAB,        /**< Close tab */
			MOVE_LEFT,        /**< Move to tab to the left */
			MOVE_RIGHT,       /**< Move to tab to the right */
			TAB_MOVE,         /**< Move tab */
			SEARCH            /**< Search on same tab */
		} state_e;

		/**
		 * @brief Function: QDebug & operator<< (QDebug & os, const main_window::MainWindow::state_e & state)
		 *
		 * \param os: output stream
		 * \param state: state to print
		 *
		 * Overload << operator to print state
		 */
		friend QDebug & operator<< (QDebug & os, const main_window::MainWindow::state_e & state);

		/**
		 * @brief states
		 *
		 */
		typedef enum class move_value_list {
			IDLE,             /**< Idle state - no user input */
			LEFT,             /**< Left movement */
			RIGHT,            /**< Right movement */
			ABSOLUTE          /**< Absolute value - action on the tab index equal to value */
		} move_value_e;

		/**
		 * @brief Function: QDebug & operator<< (QDebug & os, const main_window::MainWindow::move_value_e & value_type)
		 *
		 * \param os: output stream
		 * \param state: state to print
		 *
		 * Overload << operator to print state
		 */
		friend QDebug & operator<< (QDebug & os, const main_window::MainWindow::move_value_e & value_type);

		/**
		 * @brief states
		 *
		 */
		typedef enum class text_action_list {
			SET,              /**< Set text */
			APPEND,           /**< Append text */
			CLEAR             /**< Clear text */
		} text_action_e;

		/**
		 * @brief Function: QDebug & operator<< (QDebug & os, const main_window::text_action_e & action)
		 *
		 * \param os: output stream
		 * \param state: state to print
		 *
		 * Overload << operator to print state
		 */
		friend QDebug & operator<< (QDebug & os, const main_window::MainWindow::text_action_e & action);

		// ================================ END ENUMERATION ========================================//

		public:

			/**
			 * @brief Function: explicit MainWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window constructor
			 */
			explicit MainWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: QMenuBar * getMenuBar()
			 *
			 * This function returns the menubar attached to the main window
			 */
			QMenuBar * getMenuBar();

			/**
			 * @brief Function: QLabel * getcenterWindow()
			 *
			 * This function returns the centerWindow attached to the main window
			 */
			QLabel * getcenterWindow();

		protected:
		#ifndef QT_NO_CONTEXTMENU
			/**
			 * @brief Function: void contextMenuEvent(QContextMenuEvent * event) override
			 *
			 * \param parent: event that must occur to trigger the context menu
			 *
			 * This function triggers the opening of the context menu
			 */
//			void contextMenuEvent(QContextMenuEvent * event) override;
		#endif // QT_NO_CONTEXTMENU

		signals:
			/**
			 * @brief Function: void updateInfoSignal(int index)
			 *
			 * \param index: index of tab either closed or clicked
			 *
			 * This function is a signal to inform that the info label needs to be updated
			 */
			void updateInfoSignal(int index);

			/**
			 * @brief Function: void updateWebsiteSignal(int index)
			 *
			 * \param index: index of tab where the website is searched
			 *
			 * This function is a signal to inform that the info label needs to be updated
			 */
			void updateWebsiteSignal(int index);

			/**
			 * @brief Function: void updateUserInputSignal(const main_window::MainWindow::text_action_e action, QString text = Q_NULLPTR)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function is the slot to update the user input label
			 */
			void updateUserInputSignal(const main_window::MainWindow::text_action_e action, QString text = Q_NULLPTR);

		private slots:

			/**
			 * @brief Function: void closeSlot()
			 *
			 * This function closes the main window
			 */
			void closeSlot();

			/**
			 * @brief Function: void openNewTabSlot()
			 *
			 * This function opens a new tab
			 */
			void openNewTabSlot();

			/**
			 * @brief Function: void closeTabSlot()
			 *
			 * This function closes a tab
			 */
			void closeTabSlot();

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
			 * @brief Function: void updateInfoSlot(int index)
			 *
			 * \param index: index of tab either closed or clicked
			 *
			 * This function is the slot to update the info label
			 */
			void updateInfoSlot(int index);

			/**
			 * @brief Function: void updateUserInputSlot(const main_window::MainWindow::text_action_e action, QString text = Q_NULLPTR)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function is the slot to update the user input label
			 */
			void updateUserInputSlot(const main_window::MainWindow::text_action_e action, QString text = Q_NULLPTR);

			/**
			 * @brief Function: void updateWebsiteSlot(int index)
			 *
			 * \param index: index of tab where the website has to be updated
			 *
			 * This function is the slot to update the info label
			 */
			void updateWebsiteSlot(int index);

			/**
			 * @brief Function: void toggleShowMenubarSlot()
			 *
			 * This function is the slot to hide the menubar
			 */
			void toggleShowMenubarSlot();

			/**
			 * @brief Function: void setCenterWindow(QString str)
			 *
			 * \param str: text to write in the widget
			 *
			 * This function writes the widget with the content of the file read (stored in input argument str)
			 */
			void setCenterWindow(QString str);

		private:

			// main widget
			/**
			 * @brief main widget
			 *
			 */
			QWidget * mainWidget;

			// File dropdown menu
			/**
			 * @brief File menu
			 *
			 */
			file_menu::FileMenu * fileMenu;

			// Edit dropdown menu
			/**
			 * @brief Edit menu
			 *
			 */
			edit_menu::EditMenu * editMenu;

			/**
			 * @brief Tabs of browser
			 *
			 */
			tab_widget::TabWidget * tabs;

			/**
			 * @brief user input
			 *
			 */
			QLabel * userInputText;

			/**
			 * @brief website
			 *
			 */
			QLabel * websiteText;

			/**
			 * @brief info
			 *
			 */
			QLabel * infoText;

			/**
			 * @brief user text
			 *
			 */
			QString userText;

			/**
			 * @brief state of the main window
			 *
			 */
			main_window::MainWindow::state_e mainWindowState;

			/**
			 * @brief type of value of movements in tab bar
			 *
			 */
			main_window::MainWindow::move_value_e moveValueType;

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
			 * @brief Function: void createMainWidget()
			 *
			 * This function creates and customizes the main widget
			 */
			void createMainWidget();

			/**
			 * @brief Function: void createTabs()
			 *
			 * This function creates and customizes QTabWidget
			 */
			void createTabs();

			/**
			 * @brief Function: void fillMainWindow()
			 *
			 * This function fills the the main window
			 */
			void fillMainWindow();

			/**
			 * @brief Function: void fillMenuBar()
			 *
			 * This function fills the menu bar of the main window
			 */
			void fillMenuBar();

			/**
			 * @brief Function: void mainWindowLayout()
			 *
			 * This function defined the layout of the main window
			 */
			void mainWindowLayout();

			/**
			 * @brief Function: void createShortcuts()
			 *
			 * This function creates shortcuts for the items on the window
			 */
			void createShortcuts();

			/**
			 * @brief Function: void addNewTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function adds a new tab to the main window
			 */
			void addNewTab(QString search);

			/**
			 * @brief Function: void executeAction(int userInput = main_window::emptyUserInput)
			 *
			 * \param userInput: user input to execute action. If not specified it is default to main_window::emptyUserInput
			 *
			 * This function executes action on a based on user input
			 */
			void executeAction(int userInput = main_window::emptyUserInput);

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
			 * @brief Function: void move(int offset, int sign = 0)
			 *
			 * \param offset: offset of tab to execute action on
			 * \param sign: direction of movement. -1 for left move and 1 for right move
			 *
			 * This function moves to a different tab as specified by the user
			 */
			void move(int offset, int sign = 0);

			/**
			 * @brief Function: void closeTab(int index)
			 *
			 * \param index: index of tab to close
			 *
			 * This function closes a tab
			 */
			void closeTab(int index);

			/**
			 * @brief Function: void processTabIndex(QString userInputStr)
			 *
			 * This function converts the string indexStr to an integer and executes desired action on it
			 */
			void processTabIndex(QString userInputStr);

			/**
			 * @brief Function: void newSearchCurrentTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the current tab
			 */
			void newSearchCurrentTab(QString search);

			/**
			 * @brief Function: void newSearchTab(int index, QString search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the tab at index index
			 */
			void newSearchTab(int index, QString search);

			/**
			 * @brief Function: QLabel * newWindowLabel()
			 *
			 * \return configured label
			 *
			 * Configure window label
			 */
			QLabel * newWindowLabel();

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: key event
			 *
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

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

	};

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
