#ifndef OPEN_PROMPT_H
#define OPEN_PROMPT_H
/**
 * @copyright
 * @file open_prompt.h
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Main Window prompt menu class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLineEdit>

#include "main_window_prompt_menu.h"
#include "constructor_macros.h"

/** @defgroup OpenPromptGroup Main Window Prompt Widget Doxygen Group
 *  Main Window prompt menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(openPromptOverall)

namespace open_prompt {

	/**
	 * @brief OpenPrompt class
	 *
	 */
	class OpenPrompt : public main_window_prompt_menu::MainWindowPromptMenu {

		public:
			/**
			 * @brief Function: explicit OpenPrompt(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window prompt menu constructor
			 */
			explicit OpenPrompt(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~OpenPrompt()
			 *
			 * Main window prompt menu destructor
			 */
			~OpenPrompt();

		protected:
			/**
			 * @brief Function: virtual void promptLayout() override
			 *
			 * This function creates the layout of the prompt menu
			 */
			virtual void promptLayout() override;

			/**
			 * @brief Function: virtual void fillWindow() override
			 *
			 * This function creates menus that are part of the prompt menu
			 */
			virtual void fillPrompt() override;

			/**
			 * @brief Function: virtual void connectSignals() override
			 *
			 * This function connects signals and slots between main prompt menu elements
			 */
			virtual void connectSignals() override;

		private:
			/**
			 * @brief user typed text
			 *
			 */
			QLineEdit * text;


			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class OpenPrompt
			 *
			 */
			DISABLE_COPY_MOVE(OpenPrompt)

	};

}

/** @} */ // End of OpenPromptGroup group

#endif // OPEN_PROMPT_H
