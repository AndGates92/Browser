#ifndef MENU_BAR_H
#define MENU_BAR_H
/**
 * @copyright
 * @file menu_bar.h
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Menu bar class header file
*/

// Qt libraries
#include <QtWidgets/QMenuBar>

#include "app/shared/constructor_macros.h"

/** @defgroup MenuGroup Menu Doxygen Group
 *  Menu functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace menu {

			/**
			 * @brief MenuBar class
			 *
			 */
			class MenuBar : public QMenuBar {

				public:
					/**
					 * @brief Function: explicit MenuBar(QWidget * parent)
					 *
					 * \param parent: pointer to the parent of the menu bar
					 *
					 * Constructor of menu bar
					 */
					explicit MenuBar(QWidget * parent);

					/**
					 * @brief Function: virtual ~MenuBar()
					 *
					 * Destructor of menu bar
					 */
					virtual ~MenuBar();

				protected:

					/**
					 * @brief Function: virtual void createMenus()
					 *
					 * This function creates all menu belonging to the menu bar
					 */
					virtual void createMenus() = 0;

				private:
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
/** @} */ // End of Menu group

#endif // MENU_BAR_H
