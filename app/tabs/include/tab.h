#ifndef TAB_H
#define TAB_H
/**
 * @copyright
 * @file tab.h
 * @author Andrea Gianarda
 * @date 03rd of April 2020
 * @brief Tab header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabOverall)

namespace tab {

	/**
	 * @brief Tab class
	 *
	 */
	class Tab : public QWidget {

		public:
			/**
			 * @brief Function: explicit Tab(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Tab constructor
			 */
			explicit Tab(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~Tab()
			 *
			 * Tab destructor
			 */
			virtual ~Tab();

		protected:

			/**
			 * @brief Function: virtual void reload()
			 *
			 * This function reloads the content of the tab
			 */
			virtual void reload() = 0;

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class Tab
			 *
			 */
			DISABLE_COPY_MOVE(Tab)

	};
}
/** @} */ // End of TabGroup group

#endif // TAB_H
