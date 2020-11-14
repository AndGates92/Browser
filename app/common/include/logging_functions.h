#ifndef LOGGING_FUNCTIONS_H
#define LOGGING_FUNCTIONS_H
/**
 * @copyright
 * @file logging_functions.h
 * @author Andrea Gianarda
 * @date 17th of April 2020
 * @brief Logging Functions header file
*/

#include <QtCore/Qt>

/** @defgroup CommonGroup Common Macros and Functions Doxygen Group
 *  Common Macros and Functions
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
/** @} */ // End of CommonGroup group

#endif // LOGGING_FUNCTIONS_H
