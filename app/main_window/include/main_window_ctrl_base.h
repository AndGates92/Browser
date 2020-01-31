#ifndef MAIN_WINDOW_CTRL_BASE_H
#define MAIN_WINDOW_CTRL_BASE_H
/**
 * @copyright
 * @file main_window_ctrl_base.h
 * @author Andrea Gianarda
 * @date 29th of January 2019
 * @brief Main Window Control base class header file
*/

#include <qt5/QtCore/QLoggingCategory>

#include "main_window_core.h"
#include "json_parser.h"

/** @defgroup MainWindowCtrlBaseGroup Main Window Doxygen Group
 *  Main Window control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlBaseOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlBaseUserInput)

namespace main_window_ctrl_base {

	/**
	 * @brief MainWindowCtrlBase class
	 *
	 */
	class MainWindowCtrlBase : public QObject {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlBase(main_window_core::MainWindowCore * windowCore, QWidget * parent = QString::null, QString jsonFileName = QString::null)
			 *
			 * \param windowCore: main window core
			 * \param parent: parent window
			 * \param jsonFileName: JSON filename
			 *
			 * Main window control constructor
			 */
			explicit MainWindowCtrlBase(main_window_core::MainWindowCore * windowCore, QWidget * parent = Q_NULLPTR, QString jsonFileName = QString::null);

			/**
			 * @brief Function: ~MainWindowCtrlBase()
			 *
			 * Main window base class control destructor
			 */
			virtual ~MainWindowCtrlBase();

			/**
			 * @brief Function: void updateInfo()
			 *
			 * This function is updates the info label
			 */
			void updateInfo();

		protected:
			/**
			 * @brief parent widget
			 *
			 */
			QWidget * parent;

			/**
			 * @brief main window core
			 *
			 */
			main_window_core::MainWindowCore * mainWindowCore;

			/**
			 * @brief tab commands and information
			 *
			 */
			json_parser::JsonParser commands;

			/**
			 * @brief Function: void createShortcuts()
			 *
			 * This function creates shortcuts for the items on the window
			 */
			virtual void createShortcuts() = 0;

			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots within main window controller
			 */
			virtual void connectSignals() = 0;

			/**
			 * @brief Function: int getTabCount()
			 *
			 * \return the number of tabs in the window
			 *
			 * This function returns the number of openend tabs
			 */
			int getTabCount();

			/**
			 * @brief Function: int getCurrentTabIndex()
			 *
			 * \return the index of the current tab
			 *
			 * This function returns the index of the current tab
			 */
			int getCurrentTabIndex();

			/**
			 * @brief Function: void printUserInput(const main_window_shared_types::text_action_e action, QString text = QString::null)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function is the slot to update the user input label
			 */
			void printUserInput(const main_window_shared_types::text_action_e action, QString text = QString::null);

			/**
			 * @brief Function: QString getActionName()
			 *
			 * \return string with the text to display as action
			 *
			 * Get action name to display in the userInputText label
			 */
			QString getActionName();

		private:

	};

}
/** @} */ // End of MainWindowCtrlBaseGroup group

#endif // MAIN_WINDOW_CTRL_BASE_H
