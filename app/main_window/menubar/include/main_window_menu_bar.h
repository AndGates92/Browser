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
			 * @brief Function: explicit MenuBar(QWidget * window = Q_NULLPTR)
			 *
			 * \param window: pointer to the window the menu belongs to
			 *
			 * Constructor of menu bar
			 */
			explicit MainWindowMenuBar(QWidget * window = Q_NULLPTR);

			/**
			 * @brief Function: ~MenuBar()
			 *
			 * Destructor of menu bar
			 */
			~MainWindowMenuBar();

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
			file_menu::FileMenu * fileMenu;

			// Edit dropdown menu
			/**
			 * @brief Edit menu
			 *
			 */
			edit_menu::EditMenu * editMenu;

			/**
			 * @brief Function: void fillMenuBar() override
			 *
			 * This function fills the menu bar of the main window
			 */
			void fillMenuBar() override;

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowMenuBar(const main_window_menu_bar::MainWindowMenuBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowMenuBar copy constructor
			 */
			explicit MainWindowMenuBar(const main_window_menu_bar::MainWindowMenuBar & rhs) = delete;

			/**
			 * @brief Function: MainWindowMenuBar(main_window_menu_bar::MainWindowMenuBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowMenuBar move constructor
			 */
			explicit MainWindowMenuBar(main_window_menu_bar::MainWindowMenuBar && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowMenuBar & operator=(const main_window_menu_bar::MainWindowMenuBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowMenuBar copy assignment operator
			 */
			MainWindowMenuBar & operator=(const main_window_menu_bar::MainWindowMenuBar & rhs) = delete;

			/**
			 * @brief Function: MainWindowMenuBar & operator=(main_window_menu_bar::MainWindowMenuBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowMenuBar move assignment operator
			 */
			MainWindowMenuBar & operator=(main_window_menu_bar::MainWindowMenuBar && rhs) = delete;

	};

}
/** @} */ // End of MainWindowMenuBarGroup group

#endif // MAIN_WINDOW_MENU_BAR_H
