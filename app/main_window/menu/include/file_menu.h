#ifndef FILE_MENU_H
#define FILE_MENU_H
/**
 * @copyright
 * @file file_menu.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief File Menu header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtGui/QKeySequence>

#include "open_button_window.h"
#include "menu.h"

/** @defgroup FileMenuGroup File Menu Doxygen Group
 *  File Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(fileMenuOverall)
Q_DECLARE_LOGGING_CATEGORY(fileMenuOpenAction)
Q_DECLARE_LOGGING_CATEGORY(fileMenuOpenTabAction)
Q_DECLARE_LOGGING_CATEGORY(fileMenuSaveAction)
Q_DECLARE_LOGGING_CATEGORY(fileMenuPrintAction)
Q_DECLARE_LOGGING_CATEGORY(fileMenuExitAction)

namespace file_menu {

	/**
	 * @brief FileMenu class
	 *
	 */
	class FileMenu : public menu::Menu {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit FileMenu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR, const char* menuName = "Unknown", const QKeySequence & key = QKeySequence::UnknownKey)
			 *
			 * \param window: pointer to the window the menu belongs to
			 * \param menuBar: menubar the menu is part of
			 * \param menuName: name of the menu
			 * \param key: keyboard shortcut
			 *
			 * Constructor of file menu
			 */
			explicit FileMenu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR, const char* menuName = "Unknown", const QKeySequence & key = QKeySequence::UnknownKey);

			/**
			 * @brief open tab action
			 *
			 */
			QAction * openTabAction;

			/**
			 * @brief save action
			 *
			 */
			QAction * saveAction;

			/**
			 * @brief print action
			 *
			 */
			QAction * printAction;

			/**
			 * @brief exit action
			 *
			 */
			QAction * exitAction;

			/**
			 * @brief Function: ~FileMenu()
			 *
			 * Destructor of file menu
			 */
			~FileMenu();

		protected:

		private slots:

			/**
			 * @brief Function: void undo()
			 *
			 * This function is the slot of the undo menu item
			 */
			void open();

			/**
			 * @brief Function: void save()
			 *
			 * This function is the slot of the save menu item
			 */
			void save();

			/**
			 * @brief Function: void print()
			 *
			 * This function is the slot of the print menu item
			 */
			void print();

			/**
			 * @brief Function: void updateCenterWindow(const QString & title, const QString & content)
			 *
			 * \param title: title of window
			 * \param content: content of the window
			 *
			 * This function is a slot to emit the signal informing the main window that the center window must be updated
			 */
			void updateCenterWindow(const QString & title, const QString & content);

		private:

			/**
			 * @brief open action
			 *
			 */
			QAction * openAction;

			/**
			 * @brief window opened following the opened action being clicked
			 *
			 */
			open_button_window::OpenButtonWindow * openWindow;

			/**
			 * @brief Function: void createMenu()
			 *
			 * This function adds the actions to the menu
			 */
			void createMenu();

			/**
			 * @brief Function: void createActions()
			 *
			 * This function creates actions that will be added to the menu
			 */
			void createActions();

		signals:
			/**
			 * @brief Function: void updateCenterWindowSignal(const QString & title, const QString & content)
			 *
			 * \param title: title of the widget
			 * \param content: content of the file read
			 *
			 * This function is a signal to inform the main window that the center window must be updated
			 */
			void updateCenterWindowSignal(const QString & title, const QString & content);

	};
}
/** @} */ // End of FileMenuGroup group

#endif // FILE_MENU_H