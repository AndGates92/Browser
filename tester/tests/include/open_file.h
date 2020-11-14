#ifndef OPEN_FILE_TEST_H
#define OPEN_FILE_TEST_H
/**
 * @copyright
 * @file open_file.h
 * @author Andrea Gianarda
 * @date 13th October 2020
 * @brief Open file header file
 */

#include "base/tester/include/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief OpenFile class
		 *
		 */
		class OpenFile : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit OpenFile(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts)
				 *
				 * \param testSuite: test suite
				 * \param useShortcut: test uses shortcuts to send commands
				 *
				 * Open file constructor
				 */
				explicit OpenFile(const std::shared_ptr<tester::base::Suite> & testSuite, const bool useShortcuts);

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

}
/** @} */ // End of TesterTestGroup group

#endif // OPEN_FILE_TEST_H
