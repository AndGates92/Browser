#ifndef MAIN_WINDOW_WRAPPER_H
#define MAIN_WINDOW_WRAPPER_H
/**
 * @copyright
 * @file main_window_wrapper.h
 * @author Andrea Gianarda
 * @date 30th of January 2020
 * @brief Main Window wrapper class header file
*/

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QWidget>

#include "main_window.h"

/** @defgroup MainWindowWrapperGroup Main Window Wrapper Doxygen Group
 *  Main Window wrapper functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowWrapperOverall)

namespace main_window_wrapper {

	/**
	 * @brief MainWindowWrapper class
	 *
	 */
	class MainWindowWrapper {

		public:
			/**
			 * @brief Function: explicit MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window wrapper constructor
			 */
			explicit MainWindowWrapper(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			// Move constructor
			/**
			 * @brief Function: MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowWrapper move constructor
			 */
			explicit MainWindowWrapper(main_window_wrapper::MainWindowWrapper && rhs);

			// Move assignment operators
			/**
			 * @brief Function: MainWindowWrapper & operator=(main_window_wrapper::MainWindowWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindowWrapper move assignment operator
			 */
			MainWindowWrapper & operator=(main_window_wrapper::MainWindowWrapper && rhs);

			/**
			 * @brief Function: virtual ~MainWindowWrapper()
			 *
			 * Main window wrapper destructor
			 */
			virtual ~MainWindowWrapper();

			/**
			 * @brief Function: void show()
			 *
			 * Show main window
			 */
			void show();

			/**
			 * @brief Function: const std::unique_ptr<main_window::MainWindow> & getWindow() const
			 *
			 * \return main window
			 *
			 * This function returns the main window
			 */
			const std::unique_ptr<main_window::MainWindow> & getWindow() const;

		protected:

		private:
			/**
			 * @brief Function: MainWindowWrapper(const main_window_wrapper::MainWindowWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowWrapper copy constructor
			 */
			explicit MainWindowWrapper(const main_window_wrapper::MainWindowWrapper & rhs) = delete;

			/**
			 * @brief Function: MainWindowWrapper & operator=(const main_window_wrapper::MainWindowWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindowWrapper copy assignment operator
			 */
			MainWindowWrapper & operator=(const main_window_wrapper::MainWindowWrapper & rhs) = delete;

			/**
			 * @brief Main window
			 *
			 */
			std::unique_ptr<main_window::MainWindow> window;

	};

}

/** @} */ // End of MainWindowWrapperGroup group

#endif // MAIN_WINDOW_WRAPPER_H
