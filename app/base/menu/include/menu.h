#ifndef MENU_H
#define MENU_H
/**
 * @copyright
 * @file menu.h
 * @author Andrea Gianarda
 * @date 23th of September 2019
 * @brief Menu header file
*/

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMenu>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QShortcut>

#include "key_sequence.h"
#include "constructor_macros.h"
#include "printable_object.h"

/** @defgroup MenuGroup Menu Doxygen Group
 *  Menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(menuOverall)

namespace menu {

	/**
	 * @brief Menu class
	 *
	 */
	class Menu : public QWidget, public printable_object::PrintableObject {

		Q_OBJECT

		public:

			/**
			 * @brief Function: explicit Menu(QWidget * parent = Q_NULLPTR, std::weak_ptr<QMenuBar> menuBar = std::weak_ptr<QMenuBar>(), const char* menuName = "Unknown", const key_sequence::KeySequence & key = key_sequence::KeySequence(QKeySequence::UnknownKey))
			 *
			 * \param parent: pointer to the parent of the menu
			 * \param menuBar: menubar the menu is part of
			 * \param menuName: name of the menu
			 * \param key: keyboard shortcut
			 *
			 * Constructor of base class menu
			 */
			explicit Menu(QWidget * parent = Q_NULLPTR, std::weak_ptr<QMenuBar> menuBar = std::weak_ptr<QMenuBar>(), const char* menuName = "Unknown", const key_sequence::KeySequence & key = key_sequence::KeySequence(QKeySequence::UnknownKey));

			/**
			 * @brief Function: virtual ~Menu()
			 *
			 * Destructor of base class menu
			 */
			virtual ~Menu();

			/**
			 * @brief Function: const std::string print() const
			 *
			 * \return menu information converted to std::string
			 *
			 * This functions prints menu info to std::string
			 */
			const std::string print() const;

		public slots:

			/**
			 * @brief Function: void setEnabledProperty(const bool & enabled)
			 *
			 * \param enabled: value of enabled property
			 *
			 * This function sets the enabled property of the menu
			 */
			void setEnabledProperty(const bool & enabled);

		protected:

			/**
			 * @brief menu bar
			 *
			 */
			std::weak_ptr<QMenuBar> menuBar;

			/**
			 * @brief menu
			 *
			 */
			std::unique_ptr<QMenu> winMenu;

			/**
			 * @brief shortcut to expand menu
			 *
			 */
			std::unique_ptr<QShortcut> expandMenu;

			/**
			 * @brief menu name
			 *
			 */
			const char * menuName;

			/**
			 * @brief shortcut key sequence
			 *
			 */
			const key_sequence::KeySequence key;

		private slots:
			/**
			 * @brief Function: void expand()
			 *
			 * This function is the slot to expand or open the menu
			 */
			void expand();

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

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class Menu
			 *
			 */
			DISABLE_COPY_MOVE(Menu)

	};
}
/** @} */ // End of MenuGroup group

#endif // MENU_H
