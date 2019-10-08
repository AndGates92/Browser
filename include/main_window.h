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
Q_DECLARE_LOGGING_CATEGORY(mainWindowSearch)

namespace main_window {

	namespace {
		/**
		 * @brief bottom information label height
		 *
		 */
		const int labelHeight = 20;
	}

	class MainWindow : public QMainWindow {

		Q_OBJECT

		/**
		 * @brief Verbosity levels
		 *
		 */
		typedef enum class state_list {
			IDLE,         /**< Idle state - no user input */
			OPEN_TAB,     /**< Open new tab */
			SEARCH        /**< Search on same tab */
		} state_e;

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

		private slots:

			/**
			 * @brief Function: void openNewTabSlot()
			 *
			 * This function opens a new tab
			 */
			void openNewTabSlot();

			/**
			 * @brief Function: void newSearchTabSlot()
			 *
			 * This function changes the title of a tab
			 */
			void newSearchTabSlot();

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
			 * @brief search
			 *
			 */
			QLabel * searchText;

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
			state_e mainWindowState;

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
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: key event
			 *
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);
	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
