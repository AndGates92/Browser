#ifndef EDIT_MENU_H
#define EDIT_MENU_H
/**
 * @copyright
 * @file edit_menu.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief Edit Menu header file
*/

#include <memory>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QObject>

#include "logging_macros.h"
#include "global_enums.h"
#include "find_button_window.h"
#include "menu.h"
#include "constructor_macros.h"
#include "find_settings.h"

/** @defgroup EditMenuGroup Edit Menu Doxygen Group
 *  Edit Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(editMenuOverall)
Q_DECLARE_LOGGING_CATEGORY(editMenuUndoAction)
Q_DECLARE_LOGGING_CATEGORY(editMenuRedoAction)
Q_DECLARE_LOGGING_CATEGORY(editMenuCutAction)
Q_DECLARE_LOGGING_CATEGORY(editMenuCopyAction)
Q_DECLARE_LOGGING_CATEGORY(editMenuPasteAction)
Q_DECLARE_LOGGING_CATEGORY(editMenuSelectAllAction)
Q_DECLARE_LOGGING_CATEGORY(editMenuFindAction)

namespace edit_menu {

	/**
	 * @brief EditMenu class
	 *
	 */
	class EditMenu final : public menu::Menu {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit EditMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key)
			 *
			 * \param parent: pointer to the parent of the menu
			 * \param menuBar: menubar the menu is part of
			 * \param menuName: name of the menu
			 * \param key: keyboard shortcut
			 *
			 * Constructor of edit menu
			 */
			explicit EditMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key);

			/**
			 * @brief Function: virtual ~EditMenu()
			 *
			 * Destructor of edit menu
			 */
			virtual ~EditMenu();

		signals:
			/**
			 * @brief Function: void triggerSearch(const find_settings::FindSettings settings) const
			 *
			 * \param settings: search settings
			 *
			 * This function is the slot to trigger a search in the page
			 */
			void triggerSearch(const find_settings::FindSettings settings) const;

		protected:

		private slots:

			/**
			 * @brief Function: void undo()
			 *
			 * This function is the slot of the undo menu item
			 */
			void undo();
			
			/**
			 * @brief Function: void redo()
			 *
			 * This function is the slot of the redo menu item
			 */
			void redo();

			/**
			 * @brief Function: void cut()
			 *
			 * This function is the slot of the cut menu item
			 */
			void cut();

			/**
			 * @brief Function: void copy()
			 *
			 * This function is the slot of the copy menu item
			 */
			void copy();

			/**
			 * @brief Function: void paste()
			 *
			 * This function is the slot of the paste menu item
			 */
			void paste();

			/**
			 * @brief Function: void selectAll()
			 *
			 * This function is the slot of the selectAll menu item
			 */
			void selectAll();

			/**
			 * @brief Function: void find()
			 *
			 * This function is the slot of the find menu item
			 */
			void find();

			/**
			 * @brief Function: void doSearch(const find_settings::FindSettings settings) const
			 *
			 * \param settings: search settings
			 *
			 * This function is the slot to trigger a search in the page
			 */
			void doSearch(const find_settings::FindSettings settings) const;

		private:
			/**
			 * @brief undo action
			 *
			 */
			std::unique_ptr<QAction> undoAction;

			/**
			 * @brief redo action
			 *
			 */
			std::unique_ptr<QAction> redoAction;

			/**
			 * @brief cut action
			 *
			 */
			std::unique_ptr<QAction> cutAction;

			/**
			 * @brief copy action
			 *
			 */
			std::unique_ptr<QAction> copyAction;

			/**
			 * @brief paste action
			 *
			 */
			std::unique_ptr<QAction> pasteAction;

			/**
			 * @brief select all action
			 *
			 */
			std::unique_ptr<QAction> selectAllAction;

			/**
			 * @brief find action
			 *
			 */
			std::unique_ptr<QAction> findAction;

			/**
			 * @brief window opened following the find action being triggered
			 *
			 */
			std::unique_ptr<find_button_window::FindButtonWindow> findWindow;

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
			 * @brief Disable move and copy constructors and operator= overloading for class EditMenu
			 *
			 */
			DISABLE_COPY_MOVE(EditMenu)

	};
}
/** @} */ // End of EditMenuGroup group

#endif // EDIT_MENU_H
