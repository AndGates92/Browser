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

namespace file_menu {

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

			open_button_window::OpenButtonWindow * getOpenWindow();
		protected:

		private slots:

			/**
			 * @brief Function: void undoSlot()
			 *
			 * This function is the slot of the undo menu item
			 */
			void openSlot();

			/**
			 * @brief Function: void openTabSlot()
			 *
			 * This function is the slot of the open tab menu item
			 */
//			void openTabSlot();

			/**
			 * @brief Function: void saveSlot()
			 *
			 * This function is the slot of the save menu item
			 */
//			void saveSlot();

			/**
			 * @brief Function: void printSlot()
			 *
			 * This function is the slot of the print menu item
			 */
//			void printSlot();

			/**
			 * @brief Function: void exitSlot()
			 *
			 * This function is the slot of the exit menu item
			 */
//			void exitSlot();

		private:

			/**
			 * @brief open action
			 *
			 */
			QAction * openAction;

			/**
			 * @brief open tab action
			 *
			 */
//			QAction * openTabAction;

			/**
			 * @brief save action
			 *
			 */
//			QAction * saveAction;

			/**
			 * @brief print action
			 *
			 */
//			QAction * printAction;

			/**
			 * @brief exit action
			 *
			 */
//			QAction * exitAction;

			/**
			 * @brief window opened following the opened action being clicked
			 *
			 */
			open_button_window::OpenButtonWindow * OpenWindow;

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
	};
}
/** @} */ // End of FileMenuGroup group

#endif // FILE_MENU_H
