#ifndef MAIN_WINDOW_FILE_MENU_H
#define MAIN_WINDOW_FILE_MENU_H
/**
 * @copyright
 * @file file_menu.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief File Menu header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenuBar>

#include "app/base/menu/menu.h"
#include "app/shared/constructor_macros.h"
#include "app/windows/secondary_windows/open_window/window.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace menu {

			/**
			 * @brief FileMenu class
			 *
			 */
			class FileMenu final : public app::base::menu::Menu {

				Q_OBJECT

				public:

					/**
					 * @brief Function: explicit FileMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const app::key_sequence::KeySequence & key)
					 *
					 * \param parent: pointer to the parent of the menu
					 * \param menuBar: menubar the menu is part of
					 * \param menuName: name of the menu
					 * \param key: keyboard shortcut
					 *
					 * Constructor of file menu
					 */
					explicit FileMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const app::key_sequence::KeySequence & key);

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
					std::unique_ptr<app::open_window::Window> openWindow;

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

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_FILE_MENU_H
