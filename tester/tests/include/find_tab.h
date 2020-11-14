#ifndef FIND_TAB_H
#define FIND_TAB_H
/**
 * @copyright
 * @file find_tab.h
 * @author Andrea Gianarda
 * @date 25th October 2020
 * @brief Find tab header file
 */

#include <regex>
#include <vector>

#include "base/tester/include/command_test.h"

/** @defgroup FindTabGroup Find Tab Group
 *  Find tab functions and classes
 *  @{
 */

namespace find_tab {

	/**
	 * @brief FindTab class
	 *
	 */
	class FindTab : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit FindTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Find tab constructor
			 */
			explicit FindTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

			/**
			 * @brief Function: virtual ~FindTab()
			 *
			 * Find tab destructor
			 */
			virtual ~FindTab();

		protected:

			/**
			 * @brief Function: virtual void testBody() override
			 *
			 * This function contains the body of the test
			 */
			virtual void testBody() override;

		private:

			/**
			 * @brief Function: std::vector<std::string> extractDataFromSearchResult(const std::regex & numberRegex, const int & expectedNumberOfMatches)
			 *
			 * \param numberRegex: regex to extract data from the search result label
			 * \param expectedNumberOfMatches: expected number of matches
			 *
			 * \return a vector of strings with the matches of the regular expression
			 *
			 * This function extracts the data from the search result label
			 */
			std::vector<std::string> extractDataFromSearchResult(const std::regex & numberRegex, const int & expectedNumberOfMatches);

			/**
			 * @brief Function: int computeNextMatchNumber(const std::string & command, const std::vector<int> & initialMatchPosition)
			 *
			 * \param command: command sent to the window
			 * \param initialMatchPosition: initial match position vector. The first element is the current match position and the second element is the total number of matches
			 *
			 * \return expected next match position
			 *
			 * This function computes the expected next match position
			 */
			int computeNextMatchNumber(const std::string & command, const std::vector<int> & initialMatchPosition);

			/**
			 * @brief Function: std::vector<int> checkMatchPosition(const std::string & command, const std::regex & numberRegex, const int & expectedNumberOfMatches, const std::vector<int> & initialMatchPosition)
			 *
			 * \param command: command sent to the window
			 * \param numberRegex: regex to extract data from the search result label
			 * \param expectedNumberOfMatches: expected number of matches
			 * \param initialMatchPosition: initial match position vector. The first element is the current match position and the second element is the total number of matches
			 *
			 * \return a vector of integers with the matches of the regular expression. This method only uses the first two elements. The first element is the current match position and the second element is the total number of matches
			 *
			 * This method checks that the match position is the one that is expected
			 */
			std::vector<int> checkMatchPosition(const std::string & command, const std::regex & numberRegex, const int & expectedNumberOfMatches, const std::vector<int> & initialMatchPosition);

			/**
			 * @brief Function: int checkVScrolling(const int & initialVScroll, const std::string & command, const bool wrapping)
			 *
			 * \param initialVScroll: vertical scrolling before search
			 * \param command: command sent to the window
			 * \param wrapping: whether the search is expected to wrap around the page in order ot look for a match
			 *
			 * \return the current value of the vertical scrolling
			 *
			 * This method checks that the vertical scrolling change through the command
			 */
			int checkVScrolling(const int & initialVScroll, const std::string & command, const bool wrapping);

			/**
			 * @brief Function: int checkVScrolling(const int & initialVScroll, const int & initialMatchPosition, const int & finalMatchPosition)
			 *
			 * \param initialVScroll: vertical scrolling before search
			 * \param initialMatchPosition: match position before search
			 * \param currentMatchPosition: match position after search
			 *
			 * \return the current value of the vertical scrolling
			 *
			 * This method checks that the vertical scrolling change through the match information
			 */
			int checkVScrolling(const int & initialVScroll, const int & initialMatchPosition, const int & finalMatchPosition);
	};

}
/** @} */ // End of FindTabGroup group

#endif // FIND_TAB_H
