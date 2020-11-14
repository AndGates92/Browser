#ifndef LAUNCH_APP_TEST_H
#define LAUNCH_APP_TEST_H
/**
 * @copyright
 * @file launch_app.h
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Launch app header file
 */

#include "base/tester/include/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief LaunchApp class
		 *
		 */
		class LaunchApp : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit LaunchApp(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Launch app constructor
				 */
				explicit LaunchApp(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~LaunchApp()
				 *
				 * Launch app destructor
				 */
				virtual ~LaunchApp();

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

#endif // LAUNCH_APP_TEST_H
