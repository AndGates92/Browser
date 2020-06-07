#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
/**
 * @copyright
 * @file main_window.h
 * @author Andrea Gianarda
 * @date 23rd of September 2019
 * @brief Main Window header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QWidget>

#include "main_window_ctrl_wrapper.h"
#include "main_window_base.h"
#include "constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCenterWindow)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabs)

namespace main_window {

	/**
	 * @brief MainWindow class
	 *
	 */
	class MainWindow final : public QMainWindow, public main_window_base::MainWindowBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindow(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window constructor
			 */
			explicit MainWindow(QWidget * parent, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~MainWindow()
			 *
			 * Main window destructor
			 */
			~MainWindow();

			/**
			 * @brief Function: main_window_ctrl_wrapper::MainWindowCtrlWrapper * getCtrl()
			 *
			 * \return wrapper to the window controller
			 *
			 * This function returns the wrapper to the window controller
			 */
			main_window_ctrl_wrapper::MainWindowCtrlWrapper * getCtrl();

		protected:
		#ifndef QT_NO_CONTEXTMENU
			/**
			 * @brief Function: void contextMenuEvent(QContextMenuEvent * event) override
			 *
			 * \param event: event that must occur to trigger the context menu
			 *
			 * This function triggers the opening of the context menu
			 */
//			void contextMenuEvent(QContextMenuEvent * event) override;
		#endif // QT_NO_CONTEXTMENU

		signals:

		private slots:

			/**
			 * @brief Function: void closeWindow()
			 *
			 * This function closes the main window
			 */
			void closeWindow();

		private:

			/**
			 * @brief Main window control
			 *
			 */
			main_window_ctrl_wrapper::MainWindowCtrlWrapper * ctrl;

			/**
			 * @brief Function: void customizeMainWidget()
			 *
			 * This function customizes the main widget
			 */
			void customizeMainWidget();

			/**
			 * @brief Function: void customizeTabs()
			 *
			 * This function customizes QTabWidget
			 */
			void customizeTabs();

			/**
			 * @brief Function: void createCtrl()
			 *
			 * This function controls the main window
			 */
			void createCtrl();

			/**
			 * @brief Function: void fillMainWindow()
			 *
			 * This function fills the main window
			 */
			void fillMainWindow();

			/**
			 * @brief Function: void customizeTopMenuBar()
			 *
			 * This function customizes the menu bar of the main window
			 */
			void customizeTopMenuBar();

			/**
			 * @brief Function: void customizeBottomStatusBar()
			 *
			 * This function customizes the status bar of the main window
			 */
			void customizeBottomStatusBar();

			/**
			 * @brief Function: void mainWindowLayout()
			 *
			 * This function defined the layout of the main window
			 */
			void mainWindowLayout();

			/**
			 * @brief Function: void connectSignals()
			 *
			 * This function connects signals and slots between main window elements
			 */
			void connectSignals();

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class MainWindow
			 *
			 */
			DISABLE_COPY_MOVE(MainWindow)

	};

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
