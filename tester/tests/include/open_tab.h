#ifndef OPEN_TAB_H
#define OPEN_TAB_H
/**
 * @copyright
 * @file open_tab.h
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Open tab header file
 */

#include "base/tester/include/command_test.h"

/** @defgroup OpenTabGroup Open Tab Group
 *  Open tab functions and classes
 *  @{
 */

namespace open_tab {

	/**
	 * @brief OpenTab class
	 *
	 */
	class OpenTab : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit OpenTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Open tab constructor
			 */
			explicit OpenTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

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

	};

}
/** @} */ // End of OpenTabGroup group

#endif // OPEN_TAB_H
