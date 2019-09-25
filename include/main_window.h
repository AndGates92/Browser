#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
/**
 * @copyright
 * @file main_window.h
 * @author Andrea Gianarda
 * @date 23th of September 2019
 * @brief Main Window header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>

#include "file_menu.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowOverall)
Q_DECLARE_LOGGING_CATEGORY(mainWindowFileMenu)
Q_DECLARE_LOGGING_CATEGORY(mainWindowEditMenu)

namespace main_window {

	class MainWindow : public QMainWindow {

		Q_OBJECT

		public:

			explicit MainWindow(QWidget * parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
			QMenuBar  * getMenuBar();

		protected:
		#ifndef QT_NO_CONTEXTMENU
//			void contextMenuEvent(QContextMenuEvent * event) override;
		#endif // QT_NO_CONTEXTMENU

		private:
			void createActions();
			void createTopMenu();

			// File dropdown menu
			file_menu::FileMenu * fileMenu;
//			QMenu * fileMenu;
//			QAction * openAction;
//			QAction * saveAction;
//			QAction * printAction;

			// Edit dropdown menu
			QMenu * editMenu;
			QAction * undoAction;
/*			QAction * redoAction;
			QAction * copyAction;
			QAction * pasteAction;
			QAction * selectAllAction;
			QAction * findAction;
*/

			QLabel * centerWindow;

		private slots:
			// File dropdown menu
//			void openSlot();
//			void saveSlot();
//			void printSlot();

			// Edit dropdown menu
			void undoSlot();
/*			void redoSlot();
			void cutSlot();
			void copySlot();
			void pasteSlot();
			void selectAllSlot();
			void findSlot();
*/
	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
