#ifndef MENU_H
#define MENU_H
/**
 * @copyright
 * @file menu.h
 * @author Andrea Gianarda
 * @date 23th of September 2019
 * @brief Menu header file
*/

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtGui/QKeySequence>
#include <qt5/QtWidgets/QShortcut>

Q_DECLARE_LOGGING_CATEGORY(menuOverall)

/** @defgroup MenuGroup Menu Doxygen Group
 *  Menu functions and classes
 *  @{
 */

namespace menu {

	/**
	 * @brief Menu class
	 *
	 */
	class Menu : public QObject {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit Menu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR, const char* menuName = "Unknown", const QKeySequence & key = QKeySequence::UnknownKey)
			 *
			 * \param window: pointer to the window the menu belongs to
			 * \param menuBar: menubar the menu is part of
			 * \param menuName: name of the menu
			 * \param key: keyboard shortcut
			 *
			 * Constructor of base class menu
			 */
			explicit Menu(QWidget * window = Q_NULLPTR, QMenuBar * menuBar = Q_NULLPTR, const char* menuName = "Unknown", const QKeySequence & key = QKeySequence::UnknownKey);

		public slots:

			/**
			 * @brief Function: void enabledPropertySlot(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function is a slot setting the enabled property of the menu
			 */
			void enabledPropertySlot(bool enabled);

		protected:

			/**
			 * @brief parent window
			 *
			 */
			QWidget * window;

			/**
			 * @brief menu bar
			 *
			 */
			QMenuBar * menuBar;

			/**
			 * @brief menu
			 *
			 */
			QMenu * winMenu;

			/**
			 * @brief shortcut to expand menu
			 *
			 */
			QShortcut * expandMenu;

			/**
			 * @brief menu name
			 *
			 */
			const char * menuName;

			/**
			 * @brief shortcut key sequence
			 *
			 */
			const QKeySequence key;

		private slots:
			/**
			 * @brief Function: void expandSlot()
			 *
			 * This function is the slot to expand or open the menu
			 */
			void expandSlot();

		private:
			/**
			 * @brief Function: void createMenu()
			 *
			 * This function adds the menu to the menubar
			 */
			void createMenu();

			/**
			 * @brief Function: void createShortcuts()
			 *
			 * This function create a shortcut for a menu
			 */
			void createShortcuts();

			/**
			 * @brief Function: void setEnabledProperty(bool enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of the menu
			 */
			void setEnabledProperty(bool enabled);

	};
}
/** @} */ // End of MenuGroup group

#endif // GRAPHICS_H
