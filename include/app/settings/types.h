#ifndef COMMAND_LINE_TYPES_H
#define COMMAND_LINE_TYPES_H
/**
 * @copyright
 * @file types.h
 * @author Andrea Gianarda
 * @date 13th of November 2020
 * @brief Command line types header file
*/

#include <map>
#include <string>

/** @defgroup Command LineGroup Command Line Doxygen Group
 *  Colland line functions and classes
 *  @{
 */
namespace app {

	namespace command_line {

		/**
		 * @brief argument map type
		 *
		 */
		using argument_map_t = std::map<std::string, std::string>;

	}

}
/** @} */ // End of Group group

#endif // COMMAND_LINE_TYPES_H
