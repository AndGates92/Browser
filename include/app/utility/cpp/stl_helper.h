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
#include <list>

#include "app/shared/exception.h"

/** @defgroup StlHelperGroup Stl Helper Doxygen Group
 *  Stl Helper
 *  @{
 */
namespace app {

	namespace utility {

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

		/**
		 * @brief Function: const std::string removeTrailingCharacter(std::string text, const std::string & trailingCharacters)
		 *
		 * \param text: text to pruned trailing characters from
		 * \param trailingCharacters: set of trailing characters to search
		 *
		 * \return: modified string
		 *
		 * This function removes trailing characters from a string
		 */
		const std::string removeTrailingCharacter(std::string text, const std::string & trailingCharacters);

		/**
		 * @brief Function: const Container<std::string> splitStringByDelimiter(const std::string & text, const std::string & delimiter)
		 *
		 * \param text: text to split
		 * \param delimiter: delimiters of the split
		 *
		 * \return: container containing splits of the string text at every instance of delimiter
		 *
		 * This function splits a string by the delimiter
		 */
		template <template <class> class Container>
		const Container<std::string> splitStringByDelimiter(const std::string & text, const std::string & delimiter);

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

	}

}
/** @} */ // End of StlHelperGroup group

template <template <class> class Container>
const Container<std::string> app::utility::splitStringByDelimiter(const std::string & text, const std::string & delimiter) {
	std::size_t pos = 0;
	const auto delimiterSize = delimiter.size();
	Container<std::string> splits;

	while (pos != std::string::npos) {
		auto nextPos = text.find_first_of(delimiter, pos);
		const auto split = text.substr(pos, (nextPos - pos));
		splits.push_back(split);
		if (nextPos != std::string::npos) {
			nextPos += delimiterSize;
			if (nextPos < text.size()) {
				pos = nextPos;
			} else {
				pos = std::string::npos;
			}
		} else {
			pos = std::string::npos;
		}
	}

	return splits;
}

template<typename type>
void app::utility::moveListElements(std::list<type> & l, const int & from, const int & to) {

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

#endif // STL_HELPER_H
