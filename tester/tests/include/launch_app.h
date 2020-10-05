#ifndef LAUNCH_APP_H
#define LAUNCH_APP_H
/**
 * @copyright
 * @file launch_app.h
 * @author Andrea Gianarda
 * @date 30th August 2020
 * @brief Launch app header file
 */
// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "command_test.h"

/** @defgroup LaunchAppGroup Launch App Group
 *  Launch app functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(launchAppOverall)
Q_DECLARE_LOGGING_CATEGORY(launchAppTest)

namespace launch_app {

	/**
	 * @brief LaunchApp class
	 *
	 */
	class LaunchApp : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit LaunchApp(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Launch app constructor
			 */
			explicit LaunchApp(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

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
/** @} */ // End of LaunchAppGroup group

#endif // LAUNCH_APP_H
