#ifndef MAIN_WINDOW_CTRL_BASE_H
#define MAIN_WINDOW_CTRL_BASE_H
/**
 * @copyright
 * @file ctrl_base.h
 * @author Andrea Gianarda
 * @date 29th of January 2020
 * @brief Main Window Control base class header file
*/

#include <memory>

#include <QtWidgets/QWidget>

#include "app/shared/constructor_macros.h"
#include "app/windows/main_window/window/base.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace json {

			class Action;

		}

		namespace window {

			/**
			 * @brief CtrlBase class
			 *
			 */
			class CtrlBase : public QWidget, public app::main_window::window::Base {

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit CtrlBase(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core)
					 *
					 * \param core: main window core
					 * \param parent: parent windget
					 *
					 * Main window control base class constructor
					 */
					explicit CtrlBase(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core);

					/**
					 * @brief Function: virtual ~CtrlBase()
					 *
					 * Main window control base class destructor
					 */
					virtual ~CtrlBase();

					/**
					 * @brief Function: virtual void keyPressEvent(QKeyEvent * event) override final
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles events coming from the keyboard
					 * Escape is not triggered in keyPressedEvent
					 * Re-implement key pressed event
					 */
					virtual void keyPressEvent(QKeyEvent * event) override final;

					/**
					 * @brief Function: virtual void keyReleaseEvent(QKeyEvent * event) override final
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles event coming from the keyboard
					 * Re-implement key released event
					 */
					virtual void keyReleaseEvent(QKeyEvent * event) override final;

				signals:

					/**
					 * @brief Function: void windowStateChangeRequested(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess)
					 *
					 * \param nextState: state the window is requested to go into.
					 * \param postprocess: flag to execute post process after chaning state.
					 *
					 * This function is a signal to request a change of the state of window
					 */
					void windowStateChangeRequested(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess);

					/**
					 * @brief Function: void saveCurrentState()
					 *
					 * This function is a signal to save the current state of the controller
					 */
					void saveCurrentState();

					/**
					 * @brief Function: void restoreSavedState()
					 *
					 * This function is a signal to restore the saved state of the controller
					 */
					void restoreSavedState();

				protected:

					/**
					 * @brief Function: virtual void createShortcuts()
					 *
					 * This function creates shortcuts for the items on the window
					 */
					virtual void createShortcuts() = 0;

					/**
					 * @brief Function: virtual void connectSignals()
					 *
					 * This function connects extra signals and slots within main window controller
					 */
					virtual void connectSignals() = 0;

					/**
					 * @brief Function: virtual void actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event)
					 *
					 * \param windowState: state the window is into.
					 * \param event: key event.
					 *
					 * This function is abstract and it executes an action when a key is released
					 */
					virtual void actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) = 0;

					/**
					 * @brief Function: virtual void executeAction(const app::main_window::state_e & windowState)
					 *
					 * \param windowState: state the window is into.
					 *
					 * This function is abstract and it executes the actions required when the window is a given state
					 */
					virtual void executeAction(const app::main_window::state_e & windowState) = 0;

					/**
					 * @brief Function: virtual void prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event)
					 *
					 * \param windowState: state the window is into.
					 * \param event: key event.
					 *
					 * This function is abstract and it executes a command on a based on user input and the window state
					 */
					virtual void prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) = 0;

					/**
					 * @brief Function: virtual void executeCommand(const QString & userCommand, const app::main_window::state_postprocessing_e & postprocess) final
					 *
					 * \param userCommand: command to execute.
					 * \param postprocess: flag to execute post process after chaning state.
					 *
					 * This function executes a command on a based on user input
					 */
					virtual void executeCommand(const QString & userCommand, const app::main_window::state_postprocessing_e & postprocess) final;

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
					 * @brief Function: void moveToCommandStateFromNonIdleState(const app::main_window::state_e & windowState)
					 *
					 * \param nextState: state the window is requested to go into.
					 *
					 * This function move to command state from another state
					 */
					void moveToCommandStateFromNonIdleState(const app::main_window::state_e & windowState);

					/**
					 * @brief Function: void resetWindowState()
					 *
					 * this function resets the window state to IDLE and clear user input
					 */
					void resetWindowState();

					/**
					 * @brief Function: virtual void focusInEvent(QFocusEvent * event) override
					 *
					 * \param event: focus event
					 *
					 * This function handles incoming focus event
					 */
					virtual void focusInEvent(QFocusEvent * event) override;

					/**
					 * @brief Function: virtual void focusOutEvent(QFocusEvent * event) override
					 *
					 * \param event: focus event
					 *
					 * This function handles outgoing focus event
					 */
					virtual void focusOutEvent(QFocusEvent * event) override;

				private:
					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class CtrlBase
					 *
					 */
					DISABLE_COPY_MOVE(CtrlBase)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CTRL_BASE_H
