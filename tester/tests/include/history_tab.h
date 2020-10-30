#ifndef HISTORY_TAB_H
#define HISTORY_TAB_H
/**
 * @copyright
 * @file history_tab.h
 * @author Andrea Gianarda
 * @date 23th October 2020
 * @brief History tab test header file
 */

#include "command_test.h"

/** @defgroup HistoryTabGroup History Tab Group
 *  History tab functions and classes
 *  @{
 */

namespace history_tab {

	/**
	 * @brief HistoryTab class
	 *
	 */
	class HistoryTab : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit HistoryTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * History tab constructor
			 */
			explicit HistoryTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

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
/** @} */ // End of HistoryTabGroup group

#endif // HISTORY_TAB_H
