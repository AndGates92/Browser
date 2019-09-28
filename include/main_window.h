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
#include "edit_menu.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(mainWindowOverall)

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

		private slots:
			void disableMenubar();

		private:
			// File dropdown menu
			file_menu::FileMenu * fileMenu;

			// Edit dropdown menu
			edit_menu::EditMenu * editMenu;

			QLabel * centerWindow;

			void createShortcuts();
	};
}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_H
