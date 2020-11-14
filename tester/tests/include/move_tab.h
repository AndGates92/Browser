#ifndef MOVE_TAB_H
#define MOVE_TAB_H
/**
 * @copyright
 * @file move_tab.h
 * @author Andrea Gianarda
 * @date 14th October 2020
 * @brief Move tab header file
 */

#include "base/tester/include/command_test.h"

/** @defgroup MoveTabGroup Move Tab Group
 *  Move tab functions and classes
 *  @{
 */

namespace move_tab {

	/**
	 * @brief MoveTab class
	 *
	 */
	class MoveTab : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit MoveTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Move tab constructor
			 */
			explicit MoveTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

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
/** @} */ // End of MoveTabGroup group

#endif // MOVE_TAB_H
