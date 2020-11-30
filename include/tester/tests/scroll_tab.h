#ifndef SCROLL_TAB_TEST_H
#define SCROLL_TAB_TEST_H
/**
 * @copyright
 * @file scroll_tab.h
 * @author Andrea Gianarda
 * @date 15th October 2020
 * @brief Scroll tab header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief ScrollTab class
		 *
		 */
		class ScrollTab : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit ScrollTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Scroll tab constructor
				 */
				explicit ScrollTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~ScrollTab()
				 *
				 * Scroll tab destructor
				 */
				virtual ~ScrollTab();

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

#endif // SCROLL_TAB_TEST_H
