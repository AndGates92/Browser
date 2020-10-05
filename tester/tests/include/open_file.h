#ifndef OPEN_FILE_H
#define OPEN_FILE_H
/**
 * @copyright
 * @file open_file.h
 * @author Andrea Gianarda
 * @date 13th October 2020
 * @brief Open file header file
 */
// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "command_test.h"

/** @defgroup OpenFileGroup Open File Group
 *  Open file functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(openFileOverall)
Q_DECLARE_LOGGING_CATEGORY(openFileTest)

namespace open_file {

	/**
	 * @brief OpenFile class
	 *
	 */
	class OpenFile : public command_test::CommandTest {

		public:
			/**
			 * @brief Function: explicit OpenFile(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts)
			 *
			 * \param testSuite: test suite
			 * \param useShortcut: test uses shortcuts to send commands
			 *
			 * Open file constructor
			 */
			explicit OpenFile(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const bool useShortcuts);

			/**
			 * @brief Function: virtual ~OpenFile()
			 *
			 * Open file destructor
			 */
			virtual ~OpenFile();

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
/** @} */ // End of OpenFileGroup group

#endif // OPEN_FILE_H
