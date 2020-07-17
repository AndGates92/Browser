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

#include "open_button_window.h"
#include "menu.h"
#include "constructor_macros.h"

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
	class FileMenu final : public menu::Menu {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit FileMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key)
			 *
			 * \param parent: pointer to the parent of the menu
			 * \param menuBar: menubar the menu is part of
			 * \param menuName: name of the menu
			 * \param key: keyboard shortcut
			 *
			 * Constructor of file menu
			 */
			explicit FileMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key);

			/**
			 * @brief open tab action
			 *
			 */
			std::unique_ptr<QAction> openTabAction;

			/**
			 * @brief save action
			 *
			 */
			std::unique_ptr<QAction> saveAction;

			/**
			 * @brief print action
			 *
			 */
			std::unique_ptr<QAction> printAction;

			/**
			 * @brief exit action
			 *
			 */
			std::unique_ptr<QAction> exitAction;

			/**
			 * @brief Function: virtual ~FileMenu()
			 *
			 * Destructor of file menu
			 */
			virtual ~FileMenu();

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
			 * @brief Function: void updateCenterWindow(const QString & contentSource, const void * data) const
			 *
			 * \param contentSource: path of the file
			 * \param data: extra data to be passed through
			 *
			 * This function is a slot to emit the signal informing the main window that the center window must be updated
			 */
			void updateCenterWindow(const QString & contentSource, const void * data) const;

		signals:
			/**
			 * @brief Function: void updateCenterWindowSignal(const QString & contentSource, const void * data) const
			 *
			 * \param contentSource: path of the file
			 * \param data: extra data to be passed through
			 *
			 * This function is a signal to inform the main window that the center window must be updated
			 */
			void updateCenterWindowSignal(const QString & contentSource, const void * data) const;

		private:

			/**
			 * @brief open action
			 *
			 */
			std::unique_ptr<QAction> openAction;

			/**
			 * @brief window opened following the open action being triggered
			 *
			 */
			std::unique_ptr<open_button_window::OpenButtonWindow> openWindow;

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

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class FileMenu
			 *
			 */
			DISABLE_COPY_MOVE(FileMenu)

	};
}
/** @} */ // End of FileMenuGroup group

#endif // FILE_MENU_H
