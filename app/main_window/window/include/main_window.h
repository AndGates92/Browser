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

#include "main_window_ctrl.h"
#include "main_window_base.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowCenterWindow)
Q_DECLARE_LOGGING_CATEGORY(mainWindowTabs)

namespace main_window {

	namespace {
		/**
		 * @brief vertical spacing between widgets
		 *
		 */
		constexpr int verticalWidgetSpacing = 0;

		/**
		 * @brief left margin between widget and window
		 *
		 */
		constexpr int leftMargin = 0;

		/**
		 * @brief right margin between widget and window
		 *
		 */
		constexpr int rightMargin = 0;

		/**
		 * @brief top margin between widget and window
		 *
		 */
		constexpr int topMargin = 0;

		/**
		 * @brief bottom margin between widget and window
		 *
		 */
		constexpr int bottomMargin = 0;

	}

	/**
	 * @brief MainWindow class
	 *
	 */
	class MainWindow : public QMainWindow, public main_window_base::MainWindowBase {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit MainWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags())
			 *
			 * \param parent: parent window
			 * \param flags: window flags
			 *
			 * Main window constructor
			 */
			explicit MainWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());

			/**
			 * @brief Function: ~MainWindow()
			 *
			 * Main window destructor
			 */
			~MainWindow();

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
			main_window_ctrl::MainWindowCtrl * ctrl;

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

			/**
			 * @brief Function: void keyPressEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard 
			 *
			 * This function handles event coming from the keyboard
			 * Escape is not triggered in keyPressedEvent 
			 * Re-implement key pressed event
			 */
			void keyPressEvent(QKeyEvent * event);

			/**
			 * @brief Function: void keyReleaseEvent(QKeyEvent * event)
			 *
			 * \param event: event coming from keyboard
			 *
			 * This function handles event coming from the keyboard
			 * Re-implement key released event
			 */
			void keyReleaseEvent(QKeyEvent * event);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindow(const main_window::MainWindow & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindow copy constructor
			 */
			explicit MainWindow(const main_window::MainWindow & rhs) = delete;

			/**
			 * @brief Function: MainWindow(main_window::MainWindow && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindow move constructor
			 */
			explicit MainWindow(main_window::MainWindow && rhs) = delete;

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindow & operator=(const main_window::MainWindow & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Command MainWindow copy assignment operator
			 */
			MainWindow & operator=(const main_window::MainWindow & rhs) = delete;

			/**
			 * @brief Function: MainWindow & operator=(main_window::MainWindow && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Command MainWindow move assignment operator
			 */
			MainWindow & operator=(main_window::MainWindow && rhs) = delete;

	};

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
