#ifndef MAIN_WINDOW_CORE_H
#define MAIN_WINDOW_CORE_H
/**
 * @copyright
 * @file core.h
 * @author Andrea Gianarda
 * @date 30th of January 2020
 * @brief Main Window core class header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "widgets/command_menu/include/command_menu.h"
#include "windows/main_window/menu/include/menu_bar.h"
#include "windows/main_window/tabs/include/tab_widget.h"
#include "windows/main_window/statusbar/include/status_bar.h"
#include "windows/main_window/common/include/shared_types.h"
#include "windows/main_window/popup/include/popup_container.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and class
 *  @{
 */

namespace main_window {

	/**
	 * @brief Core class
	 *
	 */
	class Core final {

		public:

			/**
			 * @brief Function: explicit Core()
			 *
			 * \param parent: parent widget
			 *
			 * Main window core constructor
			 */
			explicit Core(QWidget * parent);

			// Move constructor
			/**
			 * @brief Function: Core(main_window::Core && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Core move constructor
			 */
			explicit Core(main_window::Core && rhs);

			// Move assignment operators
			/**
			 * @brief Function: Core & operator=(main_window::Core && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Core move assignment operator
			 */
			Core & operator=(main_window::Core && rhs);

			/**
			 * @brief Function: virtual ~Core()
			 *
			 * Main window core destructor
			 */
			virtual ~Core();

			// Getters
			// Control members
			/**
			 * Function: const main_window::state_e & getMainWindowState() const
			 *
			 * \return the state of the main window
			 *
			 * This function returns the state of the main window
			 */
			const main_window::state_e & getMainWindowState() const;

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
			 * Function: main_window::state_e setMainWindowState(const main_window::state_e & value)
			 *
			 * \param value: state of the main window
			 *
			 * This function returns the state of the main window
			 */
			void setMainWindowState(const main_window::state_e & value);

			/**
			 * Function: void setOffsetType(const global_enums::offset_type_e & value)
			 *
			 * \param value: type of value of movements in tab bar
			 *
			 * This function returns the type of value of movements in the tab bar
			 */
			void setOffsetType(const global_enums::offset_type_e & value);

			/**
			 * @brief Function: void updateUserInput(const main_window::text_action_e & action, const QString & text = QString())
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function updates the user input string
			 */
			void updateUserInput(const main_window::text_action_e & action, const QString & text = QString());

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
			std::unique_ptr<main_window::TabWidget> tabs;

			/**
			 * @brief Top menu bar of browser
			 *
			 */
			std::shared_ptr<main_window::MenuBar> topMenuBar;

			/**
			 * @brief Prompt widget of the main window
			 *
			 */
			std::shared_ptr<main_window::PopupContainer> popup;

			/**
			 * @brief Bottom menu bar of browser
			 *
			 */
			std::unique_ptr<main_window::StatusBar> bottomStatusBar;

			/**
			 * @brief Command menu 
			 *
			 */
			std::unique_ptr<command_menu::CommandMenu> cmdMenu;

		private:

			/**
			 * @brief Function: Core(const main_window::Core & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Core copy constructor
			 */
			explicit Core(const main_window::Core & rhs) = delete;

			/**
			 * @brief Function: Core & operator=(const main_window::Core & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Core copy assignment operator
			 */
			Core & operator=(const main_window::Core & rhs) = delete;


			// Control members
			/**
			 * @brief state of the main window
			 *
			 */
			main_window::state_e mainWindowState;

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
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CORE_H
