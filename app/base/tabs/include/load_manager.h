#ifndef TAB_LOAD_MANAGER_H
#define TAB_LOAD_MANAGER_H
/**
 * @copyright
 * @file load_manager.h
 * @author Andrea Gianarda
 * @date 09th of April 2020
 * @brief Tab Load Manager header file
*/

// Qt libraries
#include <QtWidgets/QWidget>

#include "common/include/global_enums.h"
#include "base/tabs/include/tab_shared_types.h"
#include "common/include/constructor_macros.h"

/** @defgroup TabGroup Tab Doxygen Group
 *  Tab functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace tab {

			class Tab;

			/**
			 * @brief LoadManager class
			 *
			 */
			class LoadManager : public QWidget {
				friend class app::base::tab::Tab;

				Q_OBJECT

				public:
					/**
					 * @brief Function: explicit LoadManager(QWidget * parent)
					 *
					 * \param parent: parent widget
					 *
					 * Tab Load Manager constructor
					 */
					explicit LoadManager(QWidget * parent);

					/**
					 * @brief Function: virtual ~LoadManager()
					 *
					 * Tab Load Manager destructor
					 */
					virtual ~LoadManager();

					/**
					 * @brief Function: const int & getProgress() const
					 *
					 * \return value of the progress
					 *
					 * This function returns the value of the progress
					 */
					const int & getProgress() const;

					/**
					 * @brief Function: const app::base::tab::load_status_e & getStatus() const
					 *
					 * \return value of the status
					 *
					 * This function returns the value of the status
					 */
					const app::base::tab::load_status_e & getStatus() const;

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
					 * @brief Function: void statusChanged(app::base::tab::load_status_e value)
					 *
					 * \param value: value of the status
					 *
					 * This function is a signal to notify that the status of loading changed
					 */
					void statusChanged(app::base::tab::load_status_e value);

				protected:
					/**
					 * @brief load status
					 *
					 */
					app::base::tab::load_status_e status;

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
					 * @brief Function: void setStatus(const app::base::tab::load_status_e & value);
					 *
					 * \param value: new status of the load manager
					 *
					 * This function sets the status to value provided as argument
					 */
					void setStatus(const app::base::tab::load_status_e & value);

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class LoadManager
					 *
					 */
					DISABLE_COPY_MOVE(LoadManager)

			};

		}

	}

}
/** @} */ // End of TabGroup group

#endif // TAB_LOAD_MANAGER_H
