#ifndef MAIN_WINDOW_CTRL_H
#define MAIN_WINDOW_CTRL_H
/**
 * @copyright
 * @file ctrl.h
 * @author Andrea Gianarda
 * @date 21st of December 2019
 * @brief Main Window Control header file
*/

#include <QtWidgets/QWidget>

#include "app/windows/main_window/shared/shared_types.h"
#include "app/windows/main_window/window/ctrl_base.h"
#include "app/shared/constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace window {

			class CtrlWrapper;

			/**
			 * @brief Ctrl class
			 *
			 */
			class Ctrl final : public app::main_window::window::CtrlBase {
				friend class app::main_window::window::CtrlWrapper;

				Q_OBJECT

				public:

					/**
					 * @brief Function: explicit Ctrl(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core)
					 *
					 * \param core: main window core
					 * \param parent: parent windget
					 *
					 * Main window control constructor
					 */
					explicit Ctrl(QWidget * parent, const std::shared_ptr<app::main_window::window::Core> & core);

					/**
					 * @brief Function: virtual ~Ctrl()
					 *
					 * Main window control constructor
					 */
					virtual ~Ctrl();

					/**
					 * @brief Function: virtual void actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) override
					 *
					 * \param windowState: state the window is into.
					 * \param event: key event.
					 *
					 * This function executes an action when a key is released
					 */
					virtual void actionOnReleasedKey(const app::main_window::state_e & windowState, QKeyEvent * event) override;

				protected:

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

				signals:
					/**
					 * @brief Function: void closeWindowSignal()
					 *
					 * This function is a signal to close the main window
					 */
					void closeWindowSignal();

				private slots:

					/**
					 * @brief Function: void close()
					 *
					 * This function closes the main window
					 */
					void closeWindow();

					/**
					 * @brief Function: void toggleShowMenubar()
					 *
					 * This function is the slot to show/hide the menubar
					 */
					void toggleShowMenubar();

				private:

					/**
					 * @brief Function: virtual void createShortcuts() override
					 *
					 * This function creates shortcuts for the items on the window
					 */
					virtual void createShortcuts() override;

					/**
					 * @brief Function: virtual void connectSignals() override
					 *
					 * This function connects signals and slots within main window controller
					 */
					virtual void connectSignals() override;

					/**
					 * @brief Function: virtual void prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) override
					 *
					 * \param windowState: state the window is into.
					 * \param event: key event.
					 *
					 * This function executes a command on a based on user input and the state the window is in
					 */
					virtual void prepareAction(const app::main_window::state_e & windowState, QKeyEvent * event) override;

					/**
					 * @brief Function: virtual void executeAction(const app::main_window::state_e & windowState) override
					 *
					 * \param windowState: state the window is into.
					 *
					 * This function executes the actions required when the window is a given state
					 */
					virtual void executeAction(const app::main_window::state_e & windowState) override;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Ctrl
					 *
					 */
					DISABLE_COPY_MOVE(Ctrl)

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_CTRL_H
