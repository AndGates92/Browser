#ifndef OPEN_TAB_TEST_H
#define OPEN_TAB_TEST_H
/**
 * @copyright
 * @file open_tab.h
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Open tab header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief OpenTab class
		 *
		 */
		class OpenTab : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit OpenTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts, const tester::shared::text_type_e type)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 * \param type: type of text given to the command to open the tab
				 *
				 * Open tab constructor
				 */
				explicit OpenTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts, const tester::shared::text_type_e type);

				/**
				 * @brief Function: virtual ~OpenTab()
				 *
				 * Open tab destructor
				 */
				virtual ~OpenTab();

			protected:

				/**
				 * @brief Function: virtual void testBody() override
				 *
				 * This function contains the body of the test
				 */
				virtual void testBody() override;

			private:

				/**
				 * @brief type of text to type as argument to open tab command
				 *
				 */
				tester::shared::text_type_e searchType;
		};

	}

}
/** @} */ // End of TesterTestGroup group

#endif // OPEN_TAB_TEST_H
