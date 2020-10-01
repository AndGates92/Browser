#ifndef TAB_LOAD_MANAGER_H
#define TAB_LOAD_MANAGER_H
/**
 * @copyright
 * @file tab_load_manager.h
 * @author Andrea Gianarda
 * @date 09th of April 2020
 * @brief Tab Load Manager header file
*/

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QLoggingCategory>

#include <QtWidgets/QWidget>

#include "global_enums.h"
#include "tab_shared_types.h"
#include "constructor_macros.h"

/** @defgroup TabLoadManagerGroup Tab Load Manager Doxygen Group
 *  Tab Load Manager functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(tabLoadManagerOverall)
Q_DECLARE_LOGGING_CATEGORY(tabLoadManagerStatus)

namespace tab {
	class Tab;
}

namespace tab_load_manager {

	/**
	 * @brief TabLoadManager class
	 *
	 */
	class TabLoadManager : public QWidget {
		friend class tab::Tab;

		Q_OBJECT

		public:
			/**
			 * @brief Function: explicit TabLoadManager(QWidget * parent)
			 *
			 * \param parent: parent widget
			 *
			 * Tab Load Manager constructor
			 */
			explicit TabLoadManager(QWidget * parent);

			/**
			 * @brief Function: virtual ~TabLoadManager()
			 *
			 * Tab Load Manager destructor
			 */
			virtual ~TabLoadManager();

			/**
			 * @brief Function: const int & getProgress() const
			 *
			 * \return value of the progress
			 *
			 * This function returns the value of the progress
			 */
			const int & getProgress() const;

			/**
			 * @brief Function: const tab_shared_types::load_status_e & getStatus() const
			 *
			 * \return value of the status
			 *
			 * This function returns the value of the status
			 */
			const tab_shared_types::load_status_e & getStatus() const;

		signals:
			/**
			 * @brief Function: void progressChanged(int value)
			 *
			 * \param value: value of the progress
			 *
			 * This function is a signal to notify that the value of progress changed
			 */
			void progressChanged(int value);

			/**
			 * @brief Function: void statusChanged(tab_shared_types::load_status_e value)
			 *
			 * \param value: value of the status
			 *
			 * This function is a signal to notify that the status of loading changed
			 */
			void statusChanged(tab_shared_types::load_status_e value);

		protected:
			/**
			 * @brief load status
			 *
			 */
			tab_shared_types::load_status_e status;

			/**
			 * @brief load value
			 *
			 */
			int progress;

			/**
			 * @brief Function: void startLoading()
			 *
			 * This function sets progress to 0
			 */
			void startLoading();

			/**
			 * @brief Function: void setProgress(const int & value)
			 *
			 * \param value: value of the progress
			 *
			 * This function sets progress to value provided as argument
			 */
			void setProgress(const int & value);

			/**
			 * @brief Function: void endLoading(const bool & success)
			 *
			 * \param success: boolean storing the information of weather the load was successful or not
			 *
			 * This function ends loading
			 */
			void endLoading(const bool & success);

		private:
			/**
			 * @brief Function: void setStatus(const tab_shared_types::load_status_e & value);
			 *
			 * \param value: new status of the load manager
			 *
			 * This function sets the status to value provided as argument
			 */
			void setStatus(const tab_shared_types::load_status_e & value);

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
