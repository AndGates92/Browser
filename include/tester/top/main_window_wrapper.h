#ifndef TESTER_MAIN_WINDOW_WRAPPER_H
#define TESTER_MAIN_WINDOW_WRAPPER_H
/**
 * @copyright
 * @file main_window_wrapper.h
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Main Window Tester wrapper class header file
*/

#include <QtWidgets/QWidget>

#include "app/windows/main_window/window/wrapper.h"

/** @defgroup MainWindowWrapperGroup Main Window Tester Wrapper Doxygen Group
 *  Main Window Tester wrapper functions and classes
 *  @{
 */

namespace app {

	namespace main_window {

		namespace popup {

			class PopupContainer;

		}

		namespace tab {

			class Tab;

		}

		namespace window {

			class CtrlWrapper;
			class Core;

		}

	}

}

namespace tester {

	namespace main_window_wrapper {

		/**
		 * @brief MainWindowWrapper class
		 *
		 */
		class MainWindowWrapper final : public app::main_window::window::Wrapper {

			public:
				/**
				 * @brief Function: explicit MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
				 *
				 * \param parent: parent window
				 * \param flags: window flags
				 *
				 * Main window tester wrapper constructor
				 */
				explicit MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

				// Move constructor
				/**
				 * @brief Function: MainWindowWrapper(tester::main_window_wrapper::MainWindowWrapper && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * Command MainWindowWrapper move constructor
				 */
				explicit MainWindowWrapper(tester::main_window_wrapper::MainWindowWrapper && rhs);

				// Move assignment operators
				/**
				 * @brief Function: MainWindowWrapper & operator=(tester::main_window_wrapper::MainWindowWrapper && rhs)
				 *
				 * \param rhs: class to move
				 *
				 * Command MainWindowWrapper move assignment operator
				 */
				MainWindowWrapper & operator=(tester::main_window_wrapper::MainWindowWrapper && rhs);

				/**
				 * @brief Function: virtual ~MainWindowWrapper()
				 *
				 * Main window wrapper destructor
				 */
				virtual ~MainWindowWrapper();

				/**
				 * @brief Function: const std::unique_ptr<app::main_window::window::CtrlWrapper> & getWindowCtrl() const
				 *
				 * \return main window controller
				 *
				 * This function returns the main window controller
				 */
				const std::unique_ptr<app::main_window::window::CtrlWrapper> & getWindowCtrl() const;

				/**
				 * @brief Function: const std::shared_ptr<app::main_window::window::Core> & getWindowCore() const
				 *
				 * \return window core
				 *
				 * This method return the window core
				 */
				const std::shared_ptr<app::main_window::window::Core> & getWindowCore() const;

				/**
				 * @brief Function: const std::shared_ptr<app::main_window::popup::PopupContainer> & getPopupContainer() const
				 *
				 * \return popup container
				 *
				 * This method return the popup container of the window
				 */
				const std::shared_ptr<app::main_window::popup::PopupContainer> & getPopupContainer() const;

				/**
				 * @brief Function: const std::shared_ptr<app::main_window::tab::Tab> getCurrentTab() const
				 *
				 * \return tab at the position of the current index or nullptr if none is opened
				 *
				 * This method return the tab at the position of the current index
				 */
				const std::shared_ptr<app::main_window::tab::Tab> getCurrentTab() const;

			protected:

			private:
				/**
				 * @brief Function: MainWindowWrapper(const tester::main_window_wrapper::MainWindowWrapper & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * Command MainWindowWrapper copy constructor
				 */
				explicit MainWindowWrapper(const tester::main_window_wrapper::MainWindowWrapper & rhs) = delete;

				/**
				 * @brief Function: MainWindowWrapper & operator=(const tester::main_window_wrapper::MainWindowWrapper & rhs)
				 *
				 * \param rhs: class to copy
				 *
				 * Command MainWindowWrapper copy assignment operator
				 */
				MainWindowWrapper & operator=(const tester::main_window_wrapper::MainWindowWrapper & rhs) = delete;

		};

	}

}

/** @} */ // End of MainWindowWrapperGroup group

#endif // TESTER_MAIN_WINDOW_WRAPPER_H
