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
			 * @brief Function: ~MenuBar()
			 *
			 * Destructor of menu bar
			 */
			virtual ~MenuBar();

		protected:
			/**
			 * @brief window the menu bar belongs to
			 *
			 */
			QWidget * window;

			/**
			 * @brief Function: void fillMenuBar()
			 *
			 * This function fills the menu bar of the main window
			 */
			virtual void fillMenuBar() = 0;

		private:
	};

}
/** @} */ // End of MenuBar group

#endif // MENU_BAR_H
