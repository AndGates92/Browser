#ifndef RELOAD_TAB_H
#define RELOAD_TAB_H
/**
 * @copyright
 * @file reload_tab.h
 * @author Andrea Gianarda
 * @date 05th October 2020
 * @brief Reload tab header file
 */

#include "command_test.h"

/** @defgroup ReloadTabGroup Reload Tab Group
 *  Reload tab functions and classes
 *  @{
 */

namespace reload_tab {

	/**
	 * @brief ReloadTab class
	 *
	 */
	class ReloadTab : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit ReloadTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Reload tab constructor
			 */
			explicit ReloadTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

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
/** @} */ // End of ReloadTabGroup group

#endif // RELOAD_TAB_H
