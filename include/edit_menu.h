#ifndef EDIT_MENU_H
#define EDIT_MENU_H
/**
 * @copyright
 * @file edit_menu.h
 * @author Andrea Gianarda
 * @date 25th of September 2019
 * @brief Edit Menu header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "open_button_window.h"
#include "menu.h"

/** @defgroup EditMenuGroup Edit Menu Doxygen Group
 *  Edit Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(editMenuOverall)

namespace edit_menu {

	class EditMenu : public QObject, public menu::Menu {

		Q_OBJECT

		public:
			explicit EditMenu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR);

		protected:

		private slots:
			void undoSlot();
/*			void redoSlot();
			void cutSlot();
			void copySlot();
			void pasteSlot();
			void selectAllSlot();
			void findSlot();
*/

		private:
			QAction * undoAction;
/*			QAction * redoAction;
			QAction * copyAction;
			QAction * pasteAction;
			QAction * selectAllAction;
			QAction * findAction;
*/

			void createMenu();
			void createActions();
	};
}
/** @} */ // End of EditMenuGroup group

#endif // EDIT_MENU_H
