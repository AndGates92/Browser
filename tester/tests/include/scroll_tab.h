#ifndef SCROLL_TAB_H
#define SCROLL_TAB_H
/**
 * @copyright
 * @file scroll_tab.h
 * @author Andrea Gianarda
 * @date 15th October 2020
 * @brief Scroll tab header file
 */
// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "command_test.h"

/** @defgroup ScrollTabGroup Scroll Tab Group
 *  Scroll tab functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(scrollTabOverall)
Q_DECLARE_LOGGING_CATEGORY(scrollTabTest)

namespace scroll_tab {

	/**
	 * @brief ScrollTab class
	 *
	 */
	class ScrollTab : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit ScrollTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Scroll tab constructor
			 */
			explicit ScrollTab(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

			/**
			 * @brief Function: virtual ~ScrollTab()
			 *
			 * Scroll tab destructor
			 */
			virtual ~ScrollTab();

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
/** @} */ // End of ScrollTabGroup group

#endif // SCROLL_TAB_H
