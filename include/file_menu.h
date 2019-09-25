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

/** @defgroup FileMenuGroup File Menu Doxygen Group
 *  File Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(fileMenuOverall)

namespace file_menu {

	class FileMenu : public QObject {

		Q_OBJECT

		public:
			explicit FileMenu(QWidget * parent = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR);

		protected:
			void createMenu();
			void createActions();

		protected slots:
			void openSlot();

		private:
			QWidget * parent;
			QMenuBar * menuBar;
			QMenu * Menu;
			QAction * openAction;
	};
}
/** @} */ // End of FileMenuGroup group

#endif // FILE_MENU_H
