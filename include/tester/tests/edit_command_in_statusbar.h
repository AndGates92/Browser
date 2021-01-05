#ifndef EDIT_COMMAND_IN_STATUSBAR_TEST_H
#define EDIT_COMMAND_IN_STATUSBAR_TEST_H
/**
 * @copyright
 * @file edit_command_in_statusbar.h
 * @author Andrea Gianarda
 * @date 08th January 2021
 * @brief Edit command in statusbar header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief EditCommandInStatusbar class
		 *
		 */
		class EditCommandInStatusbar : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit EditCommandInStatusbar(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Edit command in statusbar constructor
				 */
				explicit EditCommandInStatusbar(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~EditCommandInStatusbar()
				 *
				 * Edit command in statusbar destructor
				 */
				virtual ~EditCommandInStatusbar();

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

#endif // EDIT_COMMAND_IN_STATUSBAR_TEST_H
