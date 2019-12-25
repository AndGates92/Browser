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

#include "main_window_shared_types.h"
#include "file_menu.h"
#include "edit_menu.h"
#include "tab_widget.h"
#include "main_window_ctrl.h"

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
	 * @brief MainWindow class
	 *
	 */
	class MainWindow : public QMainWindow {

		Q_OBJECT

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
			 * @brief Function: QLabel * getCenterWindow()
			 *
			 * This function returns the centerWindow attached to the main window
			 */
			QLabel * getCenterWindow();

		protected:
		#ifndef QT_NO_CONTEXTMENU
			/**
			 * @brief Function: void contextMenuEvent(QContextMenuEvent * event) override
			 *
			 * \param event: event that must occur to trigger the context menu
			 *
			 * This function triggers the opening of the context menu
			 */
//			void contextMenuEvent(QContextMenuEvent * event) override;
		#endif // QT_NO_CONTEXTMENU

		signals:
			/**
			 * @brief Function: void sendCurrentTabIndexSignal(int currentTabIndex)
			 *
			 * \param currentTabIndex: index of the current tab
			 *
			 * This function is a signal to send the value of the current tab index
			 */
			void sendCurrentTabIndexSignal(int currentTabIndex);

			/**
			 * @brief Function: void sendTabCountSignal(int tabCount)
			 *
			 * \param tabCount: number of tabs
			 *
			 * This function is a signal to send the value of the number of opened tab
			 */
			void sendTabCountSignal(int tabCount);

		private slots:

			/**
			 * @brief Function: void closeWindow()
			 *
			 * This function closes the main window
			 */
			void closeWindow();

			/**
			 * @brief Function: void updateInfoSlot(int index)
			 *
			 * \param index: index of tab either closed or clicked
			 *
			 * This function is the slot to update the info label
			 * Note: argument index is not used
			 */
			void updateInfoSlot(int index);

			/**
			 * @brief Function: void toggleShowMenubar()
			 *
			 * This function is the slot to show/hide the menubar
			 */
			void toggleShowMenubar();

			/**
			 * @brief Function: void setCenterWindow(QString str)
			 *
			 * \param str: text to write in the widget
			 *
			 * This function writes the widget with the content of the file read (stored in input argument str)
			 */
			void setCenterWindow(QString str);

			/**
			 * @brief Function: void updateUserInputBar(QString textLabel)
			 *
			 * \param text: text to append to userText
			 *
			 * This function is the slot to update the user input label
			 */
			void updateUserInputBar(QString textLabel);

			/**
			 * @brief Function: void addNewTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function adds a new tab to the main window
			 */
			void addNewTab(QString search);

			/**
			 * @brief Function: void closeTab(int index)
			 *
			 * \param index: index of tab to close
			 *
			 * This function closes a tab
			 */
			void closeTab(int index);

			/**
			 * @brief Function: void updateWebsite(int index)
			 *
			 * \param index: index of tab where the website has to be updated
			 *
			 * This function updates the website label
			 */
			void updateWebsite(int index);

			/**
			 * @brief Function: void moveCursor(int tabIndex)
			 *
			 * \param tabIndex: index to move the cursor to
			 *
			 * This function moves the cursor to a different tab as specified by the user
			 */
			void moveCursor(int tabIndex);

			/**
			 * @brief Function: void moveTab(int tabIndex)
			 *
			 * \param tabIndex: index to move the tab to
			 *
			 * This function moves the current tab to a different tab as specified by the user
			 */
			void moveTab(int tabIndex);

			/**
			 * @brief Function: void refreshUrl(int tabIndex)
			 *
			 * \param tabIndex: tab index to refresh
			 *
			 * This function refreshes a tab as specified by the user
			 */
			void refreshUrl(int tabIndex);

			/**
			 * @brief Function: void searchCurrentTab(QString search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the current tab
			 */
			void searchCurrentTab(QString search);

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
			 * @brief Main window control
			 *
			 */
			main_window_ctrl::MainWindowCtrl * ctrl;

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
			 * @brief Function: void createCtrl()
			 *
			 * This function controls the main window
			 */
			void createCtrl();

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
			 * @brief Function: QLabel * newWindowLabel()
			 *
			 * \return configured label
			 *
			 * Configure window label
			 */
			QLabel * newWindowLabel();

			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots between main window elements
			 */
			void connectSignals();

			/**
			 * @brief Function: void updateInfo()
			 *
			 * This function is updates the info label
			 */
			void updateInfo();

			/**
			 * @brief Function: void newSearchTab(int index, QString search)
			 *
			 * \param search: string to search
			 *
			 * This function search on the tab at index index
			 */
			void newSearchTab(int index, QString search);

			/**
			 * @brief Function: void getCurrentTabIndex()
			 *
			 * This function sends the current tab index
			 */
			void getCurrentTabIndex();

			/**
			 * @brief Function: void getTabCount()
			 *
			 * This function sends the number of openend tabs
			 */
			void getTabCount();

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

	};

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
