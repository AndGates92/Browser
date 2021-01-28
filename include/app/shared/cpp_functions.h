#ifndef APP_CPP_FUNCTIONS_H
#define APP_CPP_FUNCTIONS_H
/**
 * @copyright
 * @file cpp_functions.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Functions header file
*/

#include <string>

#include "app/utility/logger/macros.h"

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */

namespace app {

	namespace shared {

		/**
		 * @brief Function: std::string readFile(const std::string & filename)
		 *
		 * \param filename: file to read
		 *
		 * \return: content of the file
		 *
		 * This function reads a file and returns its content
		 */
		std::string readFile(const std::string & filename);

	}

}
/** @} */ // End of SharedGroup group

#endif // APP_CPP_FUNCTIONS_H
