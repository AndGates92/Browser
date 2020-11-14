#ifndef HISTORY_TAB_TEST_H
#define HISTORY_TAB_TEST_H
/**
 * @copyright
 * @file history_tab.h
 * @author Andrea Gianarda
 * @date 23th October 2020
 * @brief History tab test header file
 */

#include "base/tester/include/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief HistoryTab class
		 *
		 */
		class HistoryTab : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit HistoryTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * History tab constructor
				 */
				explicit HistoryTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~HistoryTab()
				 *
				 * History tab destructor
				 */
				virtual ~HistoryTab();

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

#endif // HISTORY_TAB_TEST_H
