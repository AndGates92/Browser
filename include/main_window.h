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
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>

#include "file_menu.h"
#include "edit_menu.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCenterWindow)

namespace main_window {

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
			 * @brief Function: void disableMenubar()
			 *
			 * This function is the slot to hide the menubar
			 */
			void disableMenubar();

			/**
			 * @brief Function: void setCenterWindow(QString str)
			 *
			 * \param str: text to set the label to
			 *
			 * This function returns the menubar attached to the main window
			 */
			void setCenterWindow(QString str);

		private:
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
			 * @brief Label at the centre of the window
			 *
			 */
			QLabel * centerWindow;

			QWidget * topWidget;
			QWidget * bottomWidget;

			/**
			 * @brief Function: void fillMainWindow(QWidget * mainWidget)
			 *
			 * \param mainWidget: main widget
			 *
			 * This function fills the the main window
			 */
			void fillMainWindow(QWidget * mainWidget);

			/**
			 * @brief Function: void fillMenuBar()
			 *
			 * This function fills the menu bar of the main window
			 */
			void fillMenuBar();

			/**
			 * @brief Function: void mainWindowLayout(QWidget * mainWidget)
			 *
			 * \param mainWidget: main widget
			 *
			 * This function defined the layout of the main window
			 */
			void mainWindowLayout(QWidget * mainWidget);


			/**
			 * @brief Function: void createShortcuts()
			 *
			 * This function creates shortcuts for the items on the window
			 */
			void createShortcuts();
	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
