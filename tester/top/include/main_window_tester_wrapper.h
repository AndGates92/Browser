#ifndef MAIN_WINDOW_TESTER_WRAPPER_H
#define MAIN_WINDOW_TESTER_WRAPPER_H
/**
 * @copyright
 * @file main_window_tester_wrapper.h
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Main Window Tester wrapper class header file
*/

#include <QtWidgets/QWidget>

#include "windows/main_window/window/include/wrapper.h"

/** @defgroup MainWindowTesterWrapperGroup Main Window Tester Wrapper Doxygen Group
 *  Main Window Tester wrapper functions and classes
 *  @{
 */

namespace main_window_tester_wrapper {

	/**
	 * @brief MainWindowTesterWrapper class
	 *
	 */
	class MainWindowTesterWrapper final : public app::main_window::window::Wrapper {

		public:
			/**
			 * @brief Function: explicit MainWindowTesterWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window tester wrapper constructor
			 */
			explicit MainWindowTesterWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			// Move constructor
			/**
			 * @brief Function: MainWindowTesterWrapper(main_window_tester_wrapper::MainWindowTesterWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowTesterWrapper move constructor
			 */
			explicit MainWindowTesterWrapper(main_window_tester_wrapper::MainWindowTesterWrapper && rhs);

			// Move assignment operators
			/**
			 * @brief Function: MainWindowTesterWrapper & operator=(main_window_tester_wrapper::MainWindowTesterWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowTesterWrapper move assignment operator
			 */
			MainWindowTesterWrapper & operator=(main_window_tester_wrapper::MainWindowTesterWrapper && rhs);

			/**
			 * @brief Function: virtual ~MainWindowTesterWrapper()
			 *
			 * Main window wrapper destructor
			 */
			virtual ~MainWindowTesterWrapper();

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
			 * @brief Function: MainWindowTesterWrapper(const main_window_tester_wrapper::MainWindowTesterWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowTesterWrapper copy constructor
			 */
			explicit MainWindowTesterWrapper(const main_window_tester_wrapper::MainWindowTesterWrapper & rhs) = delete;

			/**
			 * @brief Function: MainWindowTesterWrapper & operator=(const main_window_tester_wrapper::MainWindowTesterWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowTesterWrapper copy assignment operator
			 */
			MainWindowTesterWrapper & operator=(const main_window_tester_wrapper::MainWindowTesterWrapper & rhs) = delete;

	};

}

/** @} */ // End of MainWindowTesterWrapperGroup group

#endif // MAIN_WINDOW_TESTER_WRAPPER_H
