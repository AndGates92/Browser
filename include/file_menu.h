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
#include <qt5/QtGui/QKeySequence>

#include "menu.h"

/** @defgroup FileMenuGroup File Menu Doxygen Group
 *  File Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(fileMenuOverall)

namespace file_menu {

	class FileMenu : public menu::Menu {

		Q_OBJECT

		public:
			explicit FileMenu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR, const char* menuName = "Unknown", const QKeySequence & key = QKeySequence::UnknownKey);

		protected:

		private slots:
			void openSlot();
//			void openTabSlot();
//			void saveSlot();
//			void printSlot();
//			void exitSlot();

		private:
			QAction * openAction;
//			QAction * openTabAction;
//			QAction * saveAction;
//			QAction * printAction;
//			QAction * exitAction;

			void createMenu();
			void createActions();
	};
}
/** @} */ // End of FileMenuGroup group

#endif // FILE_MENU_H
