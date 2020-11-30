#ifndef MAIN_WINDOW_WRAPPER_H
#define MAIN_WINDOW_WRAPPER_H
/**
 * @copyright
 * @file wrapper.h
 * @author Andrea Gianarda
 * @date 30th of January 2020
 * @brief Main Window wrapper class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "app/windows/main_window/window/main_window.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace window {

			/**
			 * @brief Wrapper class
			 *
			 */
			class Wrapper {

				public:
					/**
					 * @brief Function: explicit Wrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
					 *
					 * \param parent: parent window
					 * \param flags: window flags
					 *
					 * Main window wrapper constructor
					 */
					explicit Wrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

					// Move constructor
					/**
					 * @brief Function: Wrapper(app::main_window::window::Wrapper && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * Command Wrapper move constructor
					 */
					explicit Wrapper(app::main_window::window::Wrapper && rhs);

					// Move assignment operators
					/**
					 * @brief Function: Wrapper & operator=(app::main_window::window::Wrapper && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * Command Wrapper move assignment operator
					 */
					Wrapper & operator=(app::main_window::window::Wrapper && rhs);

					/**
					 * @brief Function: virtual ~Wrapper()
					 *
					 * Main window wrapper destructor
					 */
					virtual ~Wrapper();

					/**
					 * @brief Function: void show()
					 *
					 * Show main window
					 */
					void show();

					/**
					 * @brief Function: const std::unique_ptr<app::main_window::window::MainWindow> & getWindow() const
					 *
					 * \return main window
					 *
					 * This function returns the main window
					 */
					const std::unique_ptr<app::main_window::window::MainWindow> & getWindow() const;

				protected:

				private:
					/**
					 * @brief Function: Wrapper(const app::main_window::window::Wrapper & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * Command Wrapper copy constructor
					 */
					explicit Wrapper(const app::main_window::window::Wrapper & rhs) = delete;

					/**
					 * @brief Function: Wrapper & operator=(const app::main_window::window::Wrapper & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * Command Wrapper copy assignment operator
					 */
					Wrapper & operator=(const app::main_window::window::Wrapper & rhs) = delete;

					/**
					 * @brief Main window
					 *
					 */
					std::unique_ptr<app::main_window::window::MainWindow> window;

			};

		}

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_WRAPPER_H
