#ifndef APP_LOGGING_H
#define APP_LOGGING_H
/**
 * @copyright
 * @file logging.h
 * @author Andrea Gianarda
 * @date 17th of April 2020
 * @brief Logging Functions header file
*/

#include <QtCore/QString>

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */
namespace app {

	namespace shared {

		/**
		 * @brief Function: QString getDateTime()
		 *
		 * \return date and time as a QString
		 *
		 * This function returns the current date and time as a QString
		 */
		QString getDateTime();

	}

}
/** @} */ // End of SharedGroup group

#endif // APP_LOGGING_H
