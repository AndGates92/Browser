#ifndef MAIN_WINDOW_CTRL_BASE_H
#define MAIN_WINDOW_CTRL_BASE_H
/**
 * @copyright
 * @file main_window_ctrl_base.h
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "common/include/constructor_macros.h"
#include "windows/main_window/window/include/main_window_base.h"
#include "windows/main_window/json/include/main_window_json_action.h"

/** @defgroup MainWindowCtrlBaseGroup Main Window Control base Doxygen Group
 *  Main Window Control base functions and classes
 *  @{
 */

namespace main_window_ctrl_base {

	/**
	 * @brief MainWindowCtrlBase class
	 *
	 */
	class MainWindowCtrlBase : public QWidget, public main_window_base::MainWindowBase, public main_window_json_action::MainWindowJsonAction {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit MainWindowCtrlBase(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core, const QString & jsonFileName = QString())
			 *
			 * \param core: main window core
			 * \param parent: parent windget
			 * \param jsonFileName: JSON filename
			 *
			 * Main window control base class constructor
			 */
			explicit MainWindowCtrlBase(QWidget * parent, const std::shared_ptr<main_window_core::MainWindowCore> & core, const QString & jsonFileName = QString());

			/**
			 * @brief Function: virtual ~MainWindowCtrlBase()
			 *
			 * Main window control base class destructor
			 */
			virtual ~MainWindowCtrlBase();

			/**
			 * @brief Function: virtual void keyPressEvent(QKeyEvent * event) final
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent
			 * Re-implement key pressed event
			 */
			virtual void keyPressEvent(QKeyEvent * event) final;

			/**
			 * @brief Function: virtual void keyReleaseEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			virtual void keyReleaseEvent(QKeyEvent * event);

		signals:
			/**
			 * @brief Function: void windowStateChanged(const main_window_shared_types::state_e & nextState)
			 *
			 * \param nextState: state the window is requested to go into.
			 *
			 * This function sets the state of window
			 */
			void windowStateChanged(const main_window_shared_types::state_e & nextState);

			/**
			 * @brief Function: void updatePrompt(QWidget * widget)
			 *
			 * This function requests to update window layout
			 */
			void updatePrompt(QWidget * widget);

		protected:

			/**
			 * @brief Function: virtual void createExtraShortcuts()
			 *
			 * This function creates shortcuts for the items on the window a part from those listed in the JSON file
			 */
			virtual void createExtraShortcuts() = 0;

			/**
			 * @brief Function: virtual void connectExtraSignals()
			 *
			 * This function connects extra signals and slots within main window controller a part from those listed in the JSON file
			 */
			virtual void connectExtraSignals() = 0;

			/**
			 * @brief Function: virtual void actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event)
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function is abstract and it executes an action when a key is released
			 */
			virtual void actionOnReleasedKey(const main_window_shared_types::state_e & windowState, QKeyEvent * event) = 0;

			/**
			 * @brief Function: virtual void executeAction(const main_window_shared_types::state_e & windowState)
			 *
			 * \param windowState: state the window is into.
			 *
			 * This function is abstract and it executes the actions required when the window is a given state
			 */
			virtual void executeAction(const main_window_shared_types::state_e & windowState) = 0;

			/**
			 * @brief Function: virtual void prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event)
			 *
			 * \param windowState: state the window is into.
			 * \param event: key event.
			 *
			 * This function is abstract and it executes a command on a based on user input and the window state
			 */
			virtual void prepareAction(const main_window_shared_types::state_e & windowState, QKeyEvent * event) = 0;

			/**
			 * @brief Function: virtual void postprocessWindowStateChange(const main_window_shared_types::state_e & previousState)
			 *
			 * \param previousState: state the window was into before the transition.
			 *
			 * This function is abstract and it defines action to be taken immediately after the window has changed state
			 */
			virtual void postprocessWindowStateChange(const main_window_shared_types::state_e & previousState) = 0;

			/**
			 * @brief Function: virtual void executeCommand(const QString & userCommand, const main_window_shared_types::state_postprocessing_e & postprocess) final
			 *
			 * \param userCommand: command to execute.
			 * \param postprocess: flag to execute post process after chaning state.
			 *
			 * This function executes a command on a based on user input
			 */
			virtual void executeCommand(const QString & userCommand, const main_window_shared_types::state_postprocessing_e & postprocess) final;

			/**
			 * @brief Function: virtual void changeWindowStateWrapper(const std::unique_ptr<main_window_json_data::MainWindowJsonData> & commandData, const main_window_shared_types::state_postprocessing_e & postprocess) final
			 *
			 * \param commandData: data relative to a command.
			 * \param postprocess: flag to execute post process after chaning state.
			 *
			 * This function is a wrapper to change the state of window
			 */
			virtual void changeWindowStateWrapper(const std::unique_ptr<main_window_json_data::MainWindowJsonData> & commandData, const main_window_shared_types::state_postprocessing_e & postprocess) final;

			/**
			 * @brief Function: virtual void changeWindowState(const main_window_shared_types::state_e & nextState, const main_window_shared_types::state_postprocessing_e postprocess, const Qt::Key key = Qt::Key_unknown) final
			 *
			 * \param nextState: state the window is requested to go into.
			 * \param postprocess: flag to execute post process after chaning state.
			 * \param key: key pressed that supports the request for a state change.
			 *
			 * This function changes the state of window
			 */
			virtual void changeWindowState(const main_window_shared_types::state_e & nextState, const main_window_shared_types::state_postprocessing_e postprocess, const Qt::Key key = Qt::Key_unknown) final;

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

			/**
			 * @brief Function: void updateScroll(const int & currIndex)
			 *
			 * \param currIndex: current page index or -1 if no tabs
			 *
			 * This function updates the scroll position
			 */
			void updateScroll();

			/**
			 * @brief Function: void updateInfo(const int & currIndex)
			 *
			 * \param currIndex: current page index or -1 if no tabs
			 *
			 * This function updates the info label
			 */
			void updateInfo(const int & currIndex);

			/**
			 * @brief Function: void printUserInput(const main_window_shared_types::text_action_e & action, const QString & text = QString())
			 *
			 * \param action: action to execute - valid values are: SET, APPEND and CLEAR
			 * \param text: text to append to userText
			 *
			 * This function updates the user input label
			 */
			void printUserInput(const main_window_shared_types::text_action_e & action, const QString & text = QString());

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
			 * @brief Function: virtual void createShortcuts() final
			 *
			 * This function creates shortcuts for the items on the window
			 */
			virtual void createShortcuts() final;

			/**
			 * @brief Function: virtual void connectSignals() final
			 *
			 * This function connects signals and slots within main window controller
			 */
			virtual void connectSignals() final;

			/**
			 * @brief Function: void moveToCommandStateFromNonIdleState(const main_window_shared_types::state_e & windowState, const Qt::Key & key)
			 *
			 * \param nextState: state the window is requested to go into.
			 * \param key: key typed by the user that supports this request.
			 *
			 * This function move to command state from another state
			 */
			void moveToCommandStateFromNonIdleState(const main_window_shared_types::state_e & windowState, const Qt::Key & key);

			/**
			 * @brief Function: void resetWindowState()
			 *
			 * this function resets the window state to IDLE and clear user input
			 */
			void resetWindowState();

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
