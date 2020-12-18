#ifndef MAIN_WINDOW_MENU_BAR_H
#define MAIN_WINDOW_MENU_BAR_H
/**
 * @copyright
 * @file menu_bar.h
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar class header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMenu>

#include "app/base/menu/menu_bar.h"
#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace menu {

			class EditMenu;
			class FileMenu;

			/**
			 * @brief MenuBar class
			 *
			 */
			class MenuBar final : public std::enable_shared_from_this<MenuBar>, public app::base::menu::MenuBar {

				public:
					/**
					 * @brief Function: explicit MenuBar(QWidget * parent)
					 *
					 * \param parent: pointer to the parent the menu belongs to
					 *
					 * Constructor of menu bar
					 */
					explicit MenuBar(QWidget * parent);

					/**
					 * @brief Function: ~MenuBar()
					 *
					 * Destructor of menu bar
					 */
					virtual ~MenuBar();

					/**
					 * @brief Function: const std::unique_ptr<app::main_window::menu::FileMenu> & getFileMenu() const
					 *
					 * \return the file menu
					 *
					 * This function returns the file menu
					 */
					const std::unique_ptr<app::main_window::menu::FileMenu> & getFileMenu() const;

					/**
					 * @brief Function: const std::unique_ptr<app::main_window::menu::EditMenu> & getEditMenu() const
					 *
					 * \return the edit menu
					 *
					 * This function returns the edit menu
					 */
					const std::unique_ptr<app::main_window::menu::EditMenu> & getEditMenu() const;

					/**
					 * @brief Function: void createMenus()
					 *
					 * This function creates all menu belonging to the menu bar 
					 */
					void createMenus();

				protected:

				private:
					// File dropdown menu
					/**
					 * @brief File menu
					 *
					 */
					std::unique_ptr<app::main_window::menu::FileMenu> fileMenu;

					// Edit dropdown menu
					/**
					 * @brief Edit menu
					 *
					 */
					std::unique_ptr<app::main_window::menu::EditMenu> editMenu;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class MenuBar
					 *
					 */
					DISABLE_COPY_MOVE(MenuBar)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_MENU_BAR_H
