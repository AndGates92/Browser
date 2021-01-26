#ifndef APP_CPP_FUNCTIONS_H
#define APP_CPP_FUNCTIONS_H
/**
 * @copyright
 * @file cpp_functions.h
 * @author Andrea Gianarda
 * @date 19th of February 2020
 * @brief Global Functions header file
*/

#include <algorithm>
#include <string>
#include <list>

#include "app/utility/logger/macros.h"
#include "app/shared/exception.h"

/** @defgroup SharedGroup Shared Macros and Functions Doxygen Group
 *  Shared Macros and Functions
 *  @{
 */

namespace app {

	namespace shared {

		/**
		 * @brief Function: void moveListElements(std::list<type> & l, cons int & from, const int & to)
		 *
		 * \param l: list whose elements are to be moved
		 * \param from: position where the element to move is
		 * \param to: position where the element has to be moved
		 *
		 * This function moves an element of the list l from position from to position to
		 */
		template<typename type>
		void moveListElements(std::list<type> & l, const int & from, const int & to);

		/**
		 * @brief Function: std::vector<std::string> splitStringByDelimiter(const std::string & str, const std::string & delim)
		 *
		 * \param str: string to be split
		 * \param delim: delimiter
		 *
		 * \return: vector of sub-string containing the splits
		 *
		 * This function splits the string in multiple sub-strings
		 */
		std::vector<std::string> splitStringByDelimiter(const std::string & str, const std::string & delim);

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

template<typename type>
void app::shared::moveListElements(std::list<type> & l, const int & from, const int & to) {

	if (from != to) {
		const int lSize = l.size();

		auto fromIter = l.begin();
		EXCEPTION_ACTION_COND((lSize < from), throw, "Trying to access element at position " << from << " of a list that has " << lSize << " elements");
		std::advance(fromIter, from);

		auto toAdjustedIter = l.begin();
		// If from < to, we want to move the tab after index to meaning that we want to add it after index to, i.e. before the tab after index to
		// Assume tabs: a b c
		// Scenario 1 (from < to):
		// Move a at the position of c -> copy a after c (i.e. before index of c + 1) leading to the following situation a b c aCopy and then delete a
		// Result: b c aCopy
		// Scenario 2 (from > to):
		// Move c at the position of a -> copy c after a (i.e. before index of a + 1) leading to the following scenario cCopy a b c and then delete c
		// Result: cCopy a b
		const int adjustment = (from < to) ? 1 : 0;
		const int toAdjusted = to + adjustment;
		EXCEPTION_ACTION_COND((lSize < toAdjusted), throw, "Trying to move element at position " << from << " to position " << to << " of a list that has " << lSize << " elements");
		if (toAdjusted == lSize) {
			toAdjustedIter = l.end();
		} else {
			std::advance(toAdjustedIter, toAdjusted);
		}

		// copy element at index from at index to
		l.emplace(toAdjustedIter, *fromIter);

		// Delete element at position from as it has already copied at position to
		l.erase(fromIter);
	}

}

#endif // APP_CPP_FUNCTIONS_H
