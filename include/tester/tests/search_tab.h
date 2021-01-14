#ifndef SEARCH_TAB_TEST_H
#define SEARCH_TAB_TEST_H
/**
 * @copyright
 * @file search_tab.h
 * @author Andrea Gianarda
 * @date 15th January 2021
 * @brief Search tab header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief SearchTab class
		 *
		 */
		class SearchTab : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit SearchTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Search tab constructor
				 */
				explicit SearchTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~SearchTab()
				 *
				 * Search tab destructor
				 */
				virtual ~SearchTab();

			protected:

				/**
				 * @brief Function: virtual void testBody() override
				 *
				 * This function contains the body of the test
				 */
				virtual void testBody() override;

			private:

		};

	}

}
/** @} */ // End of TesterTestGroup group

#endif // SEARCH_TAB_TEST_H
