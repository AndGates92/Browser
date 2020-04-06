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
#include "constructor_macros.h"

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
	class MainWindowCtrlBase : public QWidget, public main_window_base::MainWindowBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindowCtrlBase(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent = QString::null, QString jsonFileName = QString::null)
			 *
			 * \param core: main window core
			 * \param parent: parent window
			 * \param jsonFileName: JSON filename
			 *
			 * Main window control base class constructor
			 */
			explicit MainWindowCtrlBase(QSharedPointer<main_window_core::MainWindowCore> core, QWidget * parent = Q_NULLPTR, QString jsonFileName = QString::null);

			/**
			 * @brief Function: virtual ~MainWindowCtrlBase()
			 *
			 * Main window control base class destructor
			 */
			virtual ~MainWindowCtrlBase();

			/**
			 * @brief Function: virtual void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			virtual void keyPressEvent(QKeyEvent * event) = 0;

			/**
			 * @brief Function: virtual void keyReleaseEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			virtual void keyReleaseEvent(QKeyEvent * event) = 0;

		public slots:

			/**
			 * @brief Function: void updateInfo(const int & currIndex)
			 *
			 * \param currIndex: current page index or -1 if no tabs
			 *
			 * This function is updates the info label
			 */
			void updateInfo(const int & currIndex);

		protected:
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
			 * @brief Function: void printUserInput(const main_window_shared_types::text_action_e action, const QString text = QString::null)
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function updates the user input label
			 */
			void printUserInput(const main_window_shared_types::text_action_e action, const QString text = QString::null);

			/**
			 * @brief Function: QString tabInfoStr(const int & currIndex) const
			 *
			 * \param currIndex: current page index or -1 if no tabs
			 *
			 * \return QString with the information
			 *
			 * This function creates the string with the tab information to be displayed at the bottom of the window
			 */
			QString tabInfoStr(const int & currIndex) const;

			/**
			 * @brief Function: void setAllShortcutEnabledProperty(const bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of all shortcuts of the main window and menus of the main window
			 */
			void setAllShortcutEnabledProperty(const bool enabled);

			/**
			 * @brief Function: virtual void setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event)
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function is abstract and it executes a command on a based on user input and the window state
			 */
			virtual void setStateAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) = 0;

			/**
			 * @brief Function: virtual bool changeWindowState(const main_window_shared_types::state_e & windowState)
			 *
			 * \param windowState: state the window is requested to go into.
			 *
			 * \return boolean whether the change was made or not. true if the state was changes and false otherwise.
			 *
			 * This function is abstract and it changes the window state
			 */
			virtual bool changeWindowState(const main_window_shared_types::state_e & windowState) = 0;

			/**
			 * @brief Function: virtual bool isValidWindowState(const main_window_shared_types::state_e & windowState)
			 *
			 * \param windowState: state the window is requested to go into.
			 *
			 * \return boolean whether the state is valid or not. true if the state is valid and false otherwise.
			 *
			 * This function is abstract and it checks that the state is valid
			 * It is recommend to call it within changeWindowState
			 */
			virtual bool isValidWindowState(const main_window_shared_types::state_e & windowState) = 0;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindowCtrlBase
			 *
			 */
			DISABLE_COPY_MOVE(MainWindowCtrlBase)

	};

}
/** @} */ // End of MainWindowCtrlBaseGroup group

#endif // MAIN_WINDOW_CTRL_BASE_H
