#ifndef MENU_BAR_H
#define MENU_BAR_H
/**
 * @copyright
 * @file menu_bar.h
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Menu bar class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenuBar>

#include "constructor_macros.h"

/** @defgroup MenuBarGroup Menu Bar Doxygen Group
 *  Menu bar functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(menuBarOverall)

namespace menu_bar {

	/**
	 * @brief MenuBar class
	 *
	 */
	class MenuBar : public QMenuBar {

		public:
			/**
			 * @brief Function: explicit MenuBar(QWidget * window = Q_NULLPTR)
			 *
			 * \param window: pointer to the window the menu belongs to
			 *
			 * Constructor of menu bar
			 */
			explicit MenuBar(QWidget * window = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~MenuBar()
			 *
			 * Destructor of menu bar
			 */
			virtual ~MenuBar();

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MenuBar
			 *
			 */
			DISABLE_COPY_MOVE(MenuBar)

	};

}
/** @} */ // End of MenuBar group

#endif // MENU_BAR_H
