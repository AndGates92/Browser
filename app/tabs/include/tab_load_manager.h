#ifndef TAB_LOAD_MANAGER_H
#define TAB_LOAD_MANAGER_H
/**
 * @copyright
 * @file tab_load_manager.h
 * @author Andrea Gianarda
 * @date 09rd of April 2020
 * @brief Tab Load Manager header file
*/

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QLoggingCategory>

#include <qt5/QtWidgets/QWidget>

#include "global_types.h"
#include "constructor_macros.h"

/** @defgroup TabLoadManagerGroup Tab Load Manager Doxygen Group
 *  Tab Load Manager functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabLoadManagerOverall)

namespace tab_load_manager {

	/**
	 * @brief TabLoadManager class
	 *
	 */
	class TabLoadManager : public QWidget {

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabLoadManager(QWidget * parent = Q_NULLPTR)
			 *
			 * \param parent: parent widget
			 *
			 * Tab Load Manager constructor
			 */
			explicit TabLoadManager(QWidget * parent = Q_NULLPTR);

			/**
			 * @brief Function: virtual ~TabLoadManager()
			 *
			 * Tab Load Manager destructor
			 */
			virtual ~TabLoadManager();

			/**
			 * @brief Function: int getProgress() const
			 *
			 * \return value of the progress
			 *
			 * This function returns the value of the progress
			 */
			int getProgress() const;

		signals:
			/**
			 * @brief Function: void progressChanged(int value)
			 *
			 * \param value: value of the progress
			 *
			 * This function is a signal to notify that the value of progress changed
			 */
			void progressChanged(int value);

		protected:
			/**
			 * @brief load value
			 *
			 */
			int progress;

		protected slots:
			/**
			 * @brief Function: void resetProgress()
			 *
			 * This function sets progress to 0
			 */
			void resetProgress();

			/**
			 * @brief Function: void setProgress(int value)
			 *
			 * \param value: value of the progress
			 *
			 * This function sets progress to value provided as argument
			 */
			void setProgress(int value);

		private:

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TabLoadManager
			 *
			 */
			DISABLE_COPY_MOVE(TabLoadManager)

	};
}
/** @} */ // End of TabLoadManagerGroup group

#endif // TAB_LOAD_MANAGER_H
