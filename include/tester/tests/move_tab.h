#ifndef MOVE_TAB_TEST_H
#define MOVE_TAB_TEST_H
/**
 * @copyright
 * @file move_tab.h
 * @author Andrea Gianarda
 * @date 14th October 2020
 * @brief Move tab header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief MoveTab class
		 *
		 */
		class MoveTab : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit MoveTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Move tab constructor
				 */
				explicit MoveTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~MoveTab()
				 *
				 * Move tab destructor
				 */
				virtual ~MoveTab();

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

#endif // MOVE_TAB_TEST_H
