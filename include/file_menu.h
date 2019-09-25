#ifndef FILE_MENU_H
#define FILE_MENU_H
/**
 * @copyright
 * @file file_menu.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief File Menu header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>

#include "menu.h"

/** @defgroup FileMenuGroup File Menu Doxygen Group
 *  File Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(fileMenuOverall)

namespace file_menu {

	class FileMenu : public QObject, public menu::Menu {

		Q_OBJECT

		public:
			explicit FileMenu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR);

		protected:

		protected slots:
			void openSlot();
//			void saveSlot();
//			void printSlot();

		private:
			QAction * openAction;
//			QAction * saveAction;
//			QAction * printAction;

			void createMenu();
			void createActions();
	};
}
/** @} */ // End of FileMenuGroup group

#endif // FILE_MENU_H
