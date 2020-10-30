#ifndef MAIN_WINDOW_CORE_H
#define MAIN_WINDOW_CORE_H
/**
 * @copyright
 * @file main_window_core.h
 * @author Andrea Gianarda
 * @date 30th of January 2020
 * @brief Main Window core class header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "command_menu.h"
#include "main_window_menu_bar.h"
#include "main_window_tab_widget.h"
#include "main_window_status_bar.h"
#include "main_window_shared_types.h"
#include "main_window_popup_container.h"

/** @defgroup MainWindowCoreGroup Main Window Core Doxygen Group
 *  Main Window core functions and class
 *  @{
 */

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

			// Move constructor
			/**
			 * @brief Function: MainWindowCore(main_window_core::MainWindowCore && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * MainWindowCore move constructor
			 */
			explicit MainWindowCore(main_window_core::MainWindowCore && rhs);

			// Move assignment operators
			/**
			 * @brief Function: MainWindowCore & operator=(main_window_core::MainWindowCore && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * MainWindowCore move assignment operator
			 */
			MainWindowCore & operator=(main_window_core::MainWindowCore && rhs);

			/**
			 * @brief Function: virtual ~MainWindowCore()
			 *
			 * Main window core destructor
			 */
			virtual ~MainWindowCore();

			// Getters
			// Control members
			/**
			 * Function: const main_window_shared_types::state_e & getMainWindowState() const
			 *
			 * \return the state of the main window
			 *
			 * This function returns the state of the main window
			 */
			const main_window_shared_types::state_e & getMainWindowState() const;

			/**
			 * Function: const global_enums::offset_type_e & getOffsetType() const
			 *
			 * \return the type of value of movements in tab bar
			 *
			 * This function returns the type of value of movements in the tab bar
			 */
			const global_enums::offset_type_e & getOffsetType() const;

			/**
			 * Function: const QString & getUserText() const
			 *
			 * \return the text typed by the user
			 *
			 * This function returns the text typed by the user
			 */
			const QString & getUserText() const;

			/**
			 * @brief Function: int getTabCount() const
			 *
			 * \return the number of tabs in the window
			 *
			 * This function returns the number of openend tabs
			 */
			int getTabCount() const;

			/**
			 * @brief Function: const QString getActionName() const
			 *
			 * \return string with the text to display as action
			 *
			 * Get action name to display in the userInputText label
			 */
			const QString getActionName() const;

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
			 * Function: main_window_shared_types::state_e setMainWindowState(const main_window_shared_types::state_e & value)
			 *
			 * \param value: state of the main window
			 *
			 * This function returns the state of the main window
			 */
			void setMainWindowState(const main_window_shared_types::state_e & value);

			/**
			 * Function: void setOffsetType(const global_enums::offset_type_e & value)
			 *
			 * \param value: type of value of movements in tab bar
			 *
			 * This function returns the type of value of movements in the tab bar
			 */
			void setOffsetType(const global_enums::offset_type_e & value);

			/**
			 * @brief Function: void updateUserInput(const main_window_shared_types::text_action_e & action, const QString & text = QString())
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function updates the user input string
			 */
			void updateUserInput(const main_window_shared_types::text_action_e & action, const QString & text = QString());

			// main widget
			/**
			 * @brief main widget
			 *
			 */
			std::unique_ptr<QWidget> mainWidget;

			/**
			 * @brief Tabs of browser
			 *
			 */
			std::unique_ptr<main_window_tab_widget::MainWindowTabWidget> tabs;

			/**
			 * @brief Top menu bar of browser
			 *
			 */
			std::shared_ptr<main_window_menu_bar::MainWindowMenuBar> topMenuBar;

			/**
			 * @brief Prompt widget of the main window
			 *
			 */
			std::shared_ptr<main_window_popup_container::MainWindowPopupContainer> popup;

			/**
			 * @brief Bottom menu bar of browser
			 *
			 */
			std::unique_ptr<main_window_status_bar::MainWindowStatusBar> bottomStatusBar;

			/**
			 * @brief Command menu 
			 *
			 */
			std::unique_ptr<command_menu::CommandMenu> cmdMenu;

		private:

			/**
			 * @brief Function: MainWindowCore(const main_window_core::MainWindowCore & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * MainWindowCore copy constructor
			 */
			explicit MainWindowCore(const main_window_core::MainWindowCore & rhs) = delete;

			/**
			 * @brief Function: MainWindowCore & operator=(const main_window_core::MainWindowCore & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * MainWindowCore copy assignment operator
			 */
			MainWindowCore & operator=(const main_window_core::MainWindowCore & rhs) = delete;


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
			global_enums::offset_type_e offsetType;

			/**
			 * @brief Text typed by the user
			 *
			 */
			QString userText;

	};

}
/** @} */ // End of MainWindowCoreGroup group

#endif // MAIN_WINDOW_CORE_H
