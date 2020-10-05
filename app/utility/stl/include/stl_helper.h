#ifndef STL_HELPER_H
#define STL_HELPER_H
/**
 * @copyright
 * @file stl_helper.h
 * @author Andrea Gianarda
 * @date 06th of October 2020
 * @brief STL helper header file
*/

#include <algorithm>
#include <string>

/** @defgroup StlHelperGroup Stl Helper Doxygen Group
 *  Stl Helper
 *  @{
 */

namespace stl_helper {

	/**
	 * @brief Function: const std::string findAndReplaceString(std::string text, const std::string & searchString, const std::string & replacingString)
	 *
	 * \param text: text to search and replace strings
	 * \param searchString: content to be searched and replaced
	 * \param replacingString: string that replaces the found content in the text
	 *
	 * \return: modified string
	 *
	 * This function searches and replaces content in a std::string
	 */
	const std::string findAndReplaceString(std::string text, const std::string & searchString, const std::string & replacingString);

}
/** @} */ // End of StlHelperGroup group

#endif // STL_HELPER_H
