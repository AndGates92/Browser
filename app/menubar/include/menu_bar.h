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
			/**
			 * @brief Function: void fillMenuBar()
			 *
			 * This function fills the menu bar
			 */
			virtual void fillMenuBar() = 0;

		private:
			// Move and copy constructor
			/**
			 * @brief Function: MenuBar(const menu_bar::MenuBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Menu copy constructor
			 */
			explicit MenuBar(const menu_bar::MenuBar & rhs) = delete;

			/**
			 * @brief Function: MenuBar(menu_bar::MenuBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Menu move constructor
			 */
			explicit MenuBar(menu_bar::MenuBar && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: MenuBar & operator=(const menu_bar::MenuBar & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command Menu copy assignment operator
			 */
			MenuBar & operator=(const menu_bar::MenuBar & rhs) = delete;

			/**
			 * @brief Function: MenuBar & operator=(menu_bar::MenuBar && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command Menu move assignment operator
			 */
	
	};

}
/** @} */ // End of MenuBar group

#endif // MENU_BAR_H
