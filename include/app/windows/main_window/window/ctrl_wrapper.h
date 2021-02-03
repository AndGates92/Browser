#ifndef MAIN_WINDOW_CTRL_WRAPPER_H
#define MAIN_WINDOW_CTRL_WRAPPER_H
/**
 * @copyright
 * @file ctrl_wrapper.h
 * @author Andrea Gianarda
 * @date 26th of April 2020
 * @brief Main Window Control Wrapper header file
*/

#include <QtWidgets/QWidget>

#include "app/windows/main_window/shared/shared_types.h"
#include "app/windows/main_window/window/base.h"
#include "app/windows/main_window/window/types.h"
#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace json {

			class Data;

		}

		namespace window {

			class MainWindow;
			class Ctrl;
			class CtrlTab;

			/**
			 * @brief CtrlWrapper class
			 *
			 */
			class CtrlWrapper final : public QWidget, public app::main_window::window::Base {
				friend class app::main_window::window::MainWindow;

				Q_OBJECT

				public:

					/**
					 * @brief Function: explicit CtrlWrapper(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core)
					 *
					 * \param core: main window core
					 * \param parent: parent windget
					 *
					 * Main window control constructor
					 */
					explicit CtrlWrapper(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core);

					/**
					 * @brief Function: virtual ~CtrlWrapper()
					 *
					 * Main window control constructor
					 */
					virtual ~CtrlWrapper();

					/**
					 * @brief Function: virtual void keyPressEvent(QKeyEvent * event) override
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles events coming from the keyboard
					 * Escape is not triggered in keyPressedEvent
					 * Re-implement key pressed event
					 */
					virtual void keyPressEvent(QKeyEvent * event) override;

					/**
					 * @brief Function: virtual void keyReleaseEvent(QKeyEvent * event) override
					 *
					 * \param event: event coming from keyboard
					 *
					 * This function handles events coming from the keyboard
					 * Re-implement key released event
					 */
					virtual void keyReleaseEvent(QKeyEvent * event) override;

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

					/**
					 * @brief Function: const app::main_window::window::ctrl_data_s & getSavedData() const
					 *
					 * \return saved data to restore
					 *
					 * This function returns the data to restore
					 */
					const app::main_window::window::ctrl_data_s & getSavedData() const;

				signals:
					/**
					 * @brief Function: void windowStateChanged(const app::main_window::state_e & nextState)
					 *
					 * \param nextState: state the window is requested to go into.
					 *
					 * This function sets the state of window
					 */
					void windowStateChanged(const app::main_window::state_e & nextState);

				protected:

				private:

					/**
					 * @brief Main window control
					 *
					 */
					std::unique_ptr<app::main_window::window::Ctrl> winctrl;

					/**
					 * @brief main window tab control
					 *
					 */
					std::unique_ptr<app::main_window::window::CtrlTab> tabctrl;

					/**
					 * @brief state to restore when the window gets the focus
					 *
					 */
					app::main_window::window::ctrl_data_s savedData;

					/**
					 * @brief Function: virtual void connectSignals() final
					 *
					 * This function connects signals and slots within main window controller
					 */
					virtual void connectSignals() final;

					/**
					 * @brief Function: virtual void setupWindowState(const app::main_window::state_e & previousState) final
					 *
					 * \param previousState: state the window was into before the transition.
					 *
					 * This function perform set up operations when entering a state
					 */
					virtual void setupWindowState(const app::main_window::state_e & previousState) final;

					/**
					 * @brief Function: virtual void postprocessWindowStateChange(const app::main_window::state_e & previousState) final
					 *
					 * \param previousState: state the window was into before the transition.
					 *
					 * This function defines the action to be taken immediately after the window has changed state
					 */
					virtual void postprocessWindowStateChange(const app::main_window::state_e & previousState) final;

					/**
					 * @brief Function: virtual void changeWindowStateWrapper(const std::unique_ptr<app::main_window::json::Data> & commandData, const app::main_window::state_postprocessing_e & postprocess) final
					 *
					 * \param commandData: data relative to a command.
					 * \param postprocess: flag to execute post process after chaning state.
					 *
					 * This function is a wrapper to change the state of window
					 */
					virtual void changeWindowStateWrapper(const std::unique_ptr<app::main_window::json::Data> & commandData, const app::main_window::state_postprocessing_e & postprocess) final;

					/**
					 * @brief Function: virtual bool isValidWindowState(const app::main_window::state_e & windowState) final
					 *
					 * \param windowState: state the window is requested to go into.
					 *
					 * \return boolean whether the state is valid or not. true if the state is valid and false otherwise.
					 *
					 * This function is abstract and it checks that the state is valid
					 * It is recommend to call it within changeWindowState
					 */
					virtual bool isValidWindowState(const app::main_window::state_e & windowState) final;

					/**
					 * @brief Function: void setAllShortcutEnabledProperty(const bool enabled)
					 *
					 * \param enabled: value of enabled property
					 *
					 * This function sets the enabled property of all shortcuts of the main window and menus of the main window
					 */
					void setAllShortcutEnabledProperty(const bool enabled);

					/**
					 * @brief Function: virtual void executeAction(const app::main_window::state_e & windowState) final 
					 *
					 * \param windowState: state the window is into.
					 *
					 * This function executes the actions required when the window is a given state
					 */
					virtual void executeAction(const app::main_window::state_e & windowState) final;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class CtrlWrapper
					 *
					 */
					DISABLE_COPY_MOVE(CtrlWrapper)

				private slots:

					/**
					 * @brief Function: virtual void changeWindowState(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess, const Qt::Key key = Qt::Key_unknown) final
					 *
					 * \param nextState: state the window is requested to go into.
					 * \param postprocess: flag to execute post process after chaning state.
					 * \param key: key pressed that supports the request for a state change.
					 *
					 * This function changes the state of window
					 */
					virtual void changeWindowState(const app::main_window::state_e & nextState, const app::main_window::state_postprocessing_e postprocess, const Qt::Key key = Qt::Key_unknown) final;

					/**
					 * @brief Function: void saveData()
					 *
					 * This function saves the current status of the controller
					 */
					void saveData();

					/**
					 * @brief Function: void restoreSavedData()
					 *
					 * This function restores the controller at the point where it was saved
					 */
					void restoreSavedData();

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CTRL_WRAPPER_H
