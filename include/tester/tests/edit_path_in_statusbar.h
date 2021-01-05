#ifndef EDIT_PATH_IN_STATUSBAR_TEST_H
#define EDIT_PATH_IN_STATUSBAR_TEST_H
/**
 * @copyright
 * @file edit_path_in_statusbar.h
 * @author Andrea Gianarda
 * @date 16th January 2021
 * @brief Edit path in statusbar header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief EditPathInStatusbar class
		 *
		 */
		class EditPathInStatusbar : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit EditPathInStatusbar(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Edit path in statusbar constructor
				 */
				explicit EditPathInStatusbar(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~EditPathInStatusbar()
				 *
				 * Edit path in statusbar destructor
				 */
				virtual ~EditPathInStatusbar();

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

#endif // EDIT_PATH_IN_STATUSBAR_TEST_H
