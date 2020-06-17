#ifndef MAIN_WINDOW_MENU_BAR_H
#define MAIN_WINDOW_MENU_BAR_H
/**
 * @copyright
 * @file main_window_menu_bar.h
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>

#include "menu_bar.h"
#include "file_menu.h"
#include "edit_menu.h"
#include "constructor_macros.h"

/** @defgroup MainWindowMenuBarGroup Main Window Menu Bar Doxygen Group
 *  Main Window Menu bar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowMenuBarOverall)

namespace main_window_menu_bar {

	/**
	 * @brief MainWindowMenuBar class
	 *
	 */
	class MainWindowMenuBar final : public menu_bar::MenuBar {

		public:
			/**
			 * @brief Function: explicit MenuBar(QWidget * parent)
			 *
			 * \param parent: pointer to the parent the menu belongs to
			 *
			 * Constructor of menu bar
			 */
			explicit MainWindowMenuBar(QWidget * parent);

			/**
			 * @brief Function: ~MenuBar()
			 *
			 * Destructor of menu bar
			 */
			virtual ~MainWindowMenuBar();

			/**
			 * @brief Function: ~getFileMenu() const
			 *
			 * \return the file menu
			 *
			 * This function returns the file menu
			 */
			file_menu::FileMenu * getFileMenu() const;

			/**
			 * @brief Function: ~getEditMenu() const
			 *
			 * \return the edit menu
			 *
			 * This function returns the edit menu
			 */
			edit_menu::EditMenu * getEditMenu() const;
		protected:

		private:
			// File dropdown menu
			/**
			 * @brief File menu
			 *
			 */
			file_menu::FileMenu * const fileMenu;

			// Edit dropdown menu
			/**
			 * @brief Edit menu
			 *
			 */
			edit_menu::EditMenu * const editMenu;

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowMenuBar
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowMenuBar)

	};

}
/** @} */ // End of MainWindowMenuBarGroup group

#endif // MAIN_WINDOW_MENU_BAR_H
