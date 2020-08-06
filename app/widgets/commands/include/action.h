#ifndef ACTION_H
#define ACTION_H
/**
 * @copyright
 * @file action.h
 * @author Andrea Gianarda
 * @date 12th of June 2020
 * @brief Action class header file
*/

#include <list>

#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QAction>

#include "constructor_macros.h"

#include "key_sequence.h"

/** @defgroup ActionGroup Action Widget Doxygen Group
 *  Action menu functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(actionOverall)

namespace action {

	/**
	 * @brief Action class
	 *
	 */
	class Action final : public QAction {

		public:
			/**
			 * @brief Function: explicit Action(QObject * parent, const QString & text = QString::null, const QIcon & icon = QIcon())
			 *
			 * \param parent: parent window
			 * \param text: descriptive text
			 * \param icon: icon linked to the action
			 *
			 * Main window popup menu constructor
			 */
			explicit Action(QObject * parent, const QString & text = QString::null, const QIcon & icon = QIcon());

			/**
			 * @brief Function: ~Action()
			 *
			 * Main window popup menu destructor
			 */
			virtual ~Action();

			/**
			 * @brief Function: void setShortcut(const key_sequence::KeySequence & shortcut)
			 *
			 * \param shortcut: primary shortcut key
			 *
			 * This function sets the primary shortcut key
			 */
			 void setShortcut(const key_sequence::KeySequence & shortcut);

			/**
			 * @brief Function: void setShortcuts(const std::list<key_sequence::KeySequence> & shortcuts)
			 *
			 * \param shortcuts: list of shortcuts that trigger the action
			 *
			 * This function sets the primary shortcut key
			 */
			 void setShortcuts(const std::list<key_sequence::KeySequence> & shortcuts);

			/**
			 * @brief Function: key_sequence::KeySequence shortcut() const
			 *
			 * \return primary shortcut key
			 *
			 * This function returns the primary shortcut key
			 */
			key_sequence::KeySequence shortcut() const;

			/**
			 * @brief Function: std::list<key_sequence::KeySequence> shortcuts() const
			 *
			 * \return a list of shortcuts
			 *
			 * This function returns a list of shortcuts where the primary one is at the head of the list
			 */
			std::list<key_sequence::KeySequence> shortcuts() const;

			/**
			 * @brief Function: friend QDebug & operator<<(QDebug & os, const action::Action & action)
			 *
			 * \param os: output stream to append the action to
			 * \param action: action to print
			 *
			 * action operator << overloading with QDebug
			 */
			friend QDebug & operator<<(QDebug & os, const action::Action & action);

			/**
			 * @brief Function: friend QString & operator<<(QString & str, const action::Action & action)
			 *
			 * \param str: string to append the action to
			 * \param action: action to print
			 *
			 * action operator << overloading with QString
			 */
			friend QString & operator<<(QString & str, const action::Action & action);

			/**
			 * @brief Function: friend std::string & operator<<(std::string & str, const action::Action & action)
			 *
			 * \param str: string to append the action to
			 * \param action: action to print
			 *
			 * action operator << overloading with std::string
			 */
			friend std::string & operator<<(std::string & str, const action::Action & action);

			/**
			 * @brief Function: std::string print() const
			 *
			 * \return action to print converted to std::string
			 *
			 * This functions prints action to print info to std::string
			 */
			std::string print() const;

			/**
			 * @brief Function: QString qprint() const
			 *
			 * \return action to print converted to QString
			 *
			 * This functions prints action to print to QString
			 */
			const QString qprint() const;

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class Action
			 *
			 */
			DISABLE_COPY_MOVE(Action)

	};

}

/** @} */ // End of ActionGroup group

#endif // ACTION_H
