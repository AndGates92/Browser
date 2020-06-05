#ifndef MAIN_WINDOW_PROMPT_MENU_H
#define MAIN_WINDOW_PROMPT_MENU_H
/**
 * @copyright
 * @file main_window_prompt_menu.h
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window prompt menu class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "constructor_macros.h"

/** @defgroup MainWindowPromptMenuGroup Main Window Prompt Widget Doxygen Group
 *  Main Window prompt menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowPromptMenuOverall)

namespace main_window_prompt_menu {

	/**
	 * @brief MainWindowPromptMenu class
	 *
	 */
	class MainWindowPromptMenu : public QWidget {

		public:
			/**
			 * @brief Function: explicit MainWindowPromptMenu(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window prompt menu constructor
			 */
			explicit MainWindowPromptMenu(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~MainWindowPromptMenu()
			 *
			 * Main window prompt menu destructor
			 */
			~MainWindowPromptMenu();

		protected:
			/**
			 * @brief Function: virtual void promptLayout()
			 *
			 * This function creates the layout of the prompt menu
			 */
			virtual void promptLayout() = 0;

			/**
			 * @brief Function: virtual void fillWindow()
			 *
			 * This function creates menus that are part of the prompt menu
			 */
			virtual void fillPrompt() = 0;

			/**
			 * @brief Function: virtual void connectSignals()
			 *
			 * This function connects signals and slots between main prompt menu elements
			 */
			virtual void connectSignals() = 0;

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowPromptMenu
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowPromptMenu)

	};

}

/** @} */ // End of MainWindowPromptMenuGroup group

#endif // MAIN_WINDOW_PROMPT_MENU_H
