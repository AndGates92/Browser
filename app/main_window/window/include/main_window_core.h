#ifndef MAIN_WINDOW_CORE_H
#define MAIN_WINDOW_CORE_H
/**
 * @copyright
 * @file main_window_core.h
 * @author Andrea Gianarda
 * @date 30th of January 2020
 * @brief Main Window core class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "command_menu.h"
#include "main_window_menu_bar.h"
#include "main_window_tab_widget.h"
#include "main_window_status_bar.h"
#include "main_window_shared_types.h"
#include "main_window_prompt_menu.h"

/** @defgroup MainWindowCoreGroup Main Window Core Doxygen Group
 *  Main Window core functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCoreOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCoreUserInput)

namespace main_window_core {

	/**
	 * @brief MainWindowCore class
	 *
	 */
	class MainWindowCore final {

		public:

			/**
			 * @brief Function: explicit MainWindowCore()
			 *
			 * \param parent: parent widget
			 *
			 * Main window core constructor
			 */
			explicit MainWindowCore(QWidget * parent);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowCore(const main_window_core::MainWindowCore & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowCore copy constructor
			 */
			explicit MainWindowCore(const main_window_core::MainWindowCore & rhs);

			/**
			 * @brief Function: MainWindowCore(main_window_core::MainWindowCore && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowCore move constructor
			 */
			explicit MainWindowCore(main_window_core::MainWindowCore && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowCore & operator=(const main_window_core::MainWindowCore & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowCore copy assignment operator
			 */
			MainWindowCore & operator=(const main_window_core::MainWindowCore & rhs);

			/**
			 * @brief Function: MainWindowCore & operator=(main_window_core::MainWindowCore && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowCore move assignment operator
			 */
			MainWindowCore & operator=(main_window_core::MainWindowCore && rhs);

			/**
			 * @brief Function: ~MainWindowCore()
			 *
			 * Main window core destructor
			 */
			~MainWindowCore();

			// Getters
			// Control members
			/**
			 * Function: main_window_shared_types::state_e getMainWindowState() const
			 *
			 * \return the state of the main window
			 *
			 * This function returns the state of the main window
			 */
			main_window_shared_types::state_e getMainWindowState() const;

			/**
			 * Function: main_window_shared_types::offset_type_e getOffsetType() const
			 *
			 * \return the type of value of movements in tab bar
			 *
			 * This function returns the type of value of movements in the tab bar
			 */
			main_window_shared_types::offset_type_e getOffsetType() const;

			/**
			 * Function: const QString getUserText() const
			 *
			 * \return the text typed by the user
			 *
			 * This function returns the text typed by the user
			 */
			const QString getUserText() const;

			/**
			 * @brief Function: int getTabCount() const
			 *
			 * \return the number of tabs in the window
			 *
			 * This function returns the number of openend tabs
			 */
			int getTabCount() const;

			/**
			 * @brief Function: QString getActionName() const
			 *
			 * \return string with the text to display as action
			 *
			 * Get action name to display in the userInputText label
			 */
			QString getActionName() const;

			/**
			 * @brief Function: int getCurrentTabIndex() const
			 *
			 * \return the index of the current tab
			 *
			 * This function returns the index of the current tab
			 */
			int getCurrentTabIndex() const;

			// Setters
			/**
			 * Function: main_window_shared_types::state_e setMainWindowState(main_window_shared_types::state_e windowState)
			 *
			 * \param windowState: state of the main window
			 *
			 * This function returns the state of the main window
			 */
			void setMainWindowState(main_window_shared_types::state_e windowState);

			/**
			 * Function: void setOffsetType(main_window_shared_types::offset_type_e type)
			 *
			 * \param type: type of value of movements in tab bar
			 *
			 * This function returns the type of value of movements in the tab bar
			 */
			void setOffsetType(main_window_shared_types::offset_type_e type);

			/**
			 * @brief Function: void updateUserInput(const main_window_shared_types::text_action_e action, QString text = QString::null)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function updates the user input string
			 */
			void updateUserInput(const main_window_shared_types::text_action_e action, QString text = QString::null);

			// main widget
			/**
			 * @brief main widget
			 *
			 */
			QWidget * mainWidget;

			/**
			 * @brief Tabs of browser
			 *
			 */
			main_window_tab_widget::MainWindowTabWidget * tabs;

			/**
			 * @brief Top menu bar of browser
			 *
			 */
			main_window_menu_bar::MainWindowMenuBar * topMenuBar;

			/**
			 * @brief Prompt widget of the main window
			 *
			 */
			main_window_prompt_menu::MainWindowPromptMenu * promptMenu;

			/**
			 * @brief Bottom menu bar of browser
			 *
			 */
			main_window_status_bar::MainWindowStatusBar * bottomStatusBar;

			/**
			 * @brief Command menu 
			 *
			 */
			command_menu::CommandMenu * cmdMenu;

		private:

			// Control members
			/**
			 * @brief state of the main window
			 *
			 */
			main_window_shared_types::state_e mainWindowState;

			/**
			 * @brief type of value of movements in tab bar
			 *
			 */
			main_window_shared_types::offset_type_e offsetType;

			/**
			 * @brief Text typed by the user
			 *
			 */
			QString userText;

	};

}
/** @} */ // End of MainWindowCoreGroup group

#endif // MAIN_WINDOW_CORE_H
