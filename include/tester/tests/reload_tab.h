#ifndef RELOAD_TAB_TEST_H
#define RELOAD_TAB_TEST_H
/**
 * @copyright
 * @file reload_tab.h
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Reload tab header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief ReloadTab class
		 *
		 */
		class ReloadTab : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit ReloadTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Reload tab constructor
				 */
				explicit ReloadTab(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

				/**
				 * @brief Function: virtual ~ReloadTab()
				 *
				 * Reload tab destructor
				 */
				virtual ~ReloadTab();

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

#endif // RELOAD_TAB_TEST_H
