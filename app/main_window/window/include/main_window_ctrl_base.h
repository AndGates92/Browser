#ifndef MAIN_WINDOW_CTRL_BASE_H
#define MAIN_WINDOW_CTRL_BASE_H
/**
 * @copyright
 * @file main_window_ctrl_base.h
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>

#include "main_window_base.h"
#include "json_parser.h"

/** @defgroup MainWindowCtrlBaseGroup Main Window Doxygen Group
 *  Main Window base control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlBaseOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCtrlBaseUserInput)

namespace main_window_ctrl_base {

	/**
	 * @brief MainWindowCtrlBase class
	 *
	 */
	class MainWindowCtrlBase : public QObject, public main_window_base::MainWindowBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlBase(main_window_core::MainWindowCore * core, QWidget * parent = QString::null, QString jsonFileName = QString::null)
			 *
			 * \param core: main window core
			 * \param parent: parent window
			 * \param jsonFileName: JSON filename
			 *
			 * Main window control base class constructor
			 */
			explicit MainWindowCtrlBase(main_window_core::MainWindowCore * core, QWidget * parent = Q_NULLPTR, QString jsonFileName = QString::null);

			/**
			 * @brief Function: ~MainWindowCtrlBase()
			 *
			 * Main window control base class destructor
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
			 * @brief Function: void printUserInput(const main_window_shared_types::text_action_e action, QString text = QString::null)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function updates the user input label
			 */
			void printUserInput(const main_window_shared_types::text_action_e action, QString text = QString::null);

			/**
			 * @brief Function: void createTabInfo()
			 *
			 * \return QString with the information
			 *
			 * This function creates the string with the tab information to be displayed at the bottom of the window
			 */
			QString createTabInfo();

			/**
			 * @brief Function: void setAllShortcutEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void setAllShortcutEnabledProperty(bool enabled);

		private:
	};

}
/** @} */ // End of MainWindowCtrlBaseGroup group

#endif // MAIN_WINDOW_CTRL_BASE_H
