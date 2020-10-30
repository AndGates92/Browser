#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
/**
 * @copyright
 * @file main_window.h
 * @author Andrea Gianarda
 * @date 23rd of September 2019
 * @brief Main Window header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#include "main_window_ctrl_wrapper.h"
#include "main_window_base.h"
#include "overlayed_widget.h"
#include "constructor_macros.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

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
			 * @brief Function: virtual ~MainWindow()
			 *
			 * Main window destructor
			 */
			virtual ~MainWindow();

			/**
			 * @brief Function: const std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> & getCtrl() const
			 *
			 * \return window controller
			 *
			 * This method return the window controller
			 */
			const std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> & getCtrl() const;

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

			/**
			 * @brief Function: void updateWidgetGeometry(const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget)
			 *
			 * \param widget: widget that is requesting to update its geometry
			 *
			 * This function updates the geometry of an overlayed widget
			 */
			void updateWidgetGeometry(const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget);

		private:

			/**
			 * @brief Main window control
			 *
			 */
			std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> ctrl;

			/**
			 * @brief list of overlayed widgets
			 *
			 */
			std::list<std::shared_ptr<overlayed_widget::OverlayedWidget>> overlayedWidgets;

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
			 * @brief Function: void resizeEvent(QResizeEvent * event)
			 *
			 * \param event: resize event
			 *
			 * This function is called when the widget is resized
			 */
			void resizeEvent(QResizeEvent * event);

			/**
			 * @brief Function: void addOverlayedWidget(const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget)
			 *
			 * \param widget: widget to add
			 *
			 * This function adds a widget to the overlayed widget list
			 */
			void addOverlayedWidget(const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget);

			/**
			 * @brief Function: void populateOverlayedWidgetList()
			 *
			 * This function populates overlayed widget list.
			 * It must be called before connectSignals in order to properly connect overlayed widget signal with main window slot to update they geometry automatically
			 */
			void populateOverlayedWidgetList();

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
