#ifndef LONG_COMMAND_WITH_SPACES_TEST_H
#define LONG_COMMAND_WITH_SPACES_TEST_H
/**
 * @copyright
 * @file long_command_with_spaces.h
 * @author Andrea Gianarda
 * @date 09th February 2021
 * @brief Long command with spaces header file
 */

#include "tester/base/command_test.h"

/** @defgroup TesterTestGroup Test Doxygen Group
 *  Test functions and classes
 *  @{
 */
namespace tester {

	namespace test {

		/**
		 * @brief LongCommandWithSpaces class
		 *
		 */
		class LongCommandWithSpaces : public tester::base::CommandTest {

			public:
				/**
				 * @brief Function: explicit LongCommandWithSpaces(const std::shared_ptr<tester::base::Suite> & testSuite, const bool withArgument)
				 *
				 * \param testSuite: test suite
				 * \param withArgument: pass argument to command
				 *
				 * Long command with spaces constructor
				 */
				explicit LongCommandWithSpaces(const std::shared_ptr<tester::base::Suite> & testSuite, const bool withArgument);

				/**
				 * @brief Function: virtual ~LongCommandWithSpaces()
				 *
				 * Long command with spaces destructor
				 */
				virtual ~LongCommandWithSpaces();

			protected:

				/**
				 * @brief Function: virtual void testBody() override
				 *
				 * This function contains the body of the test
				 */
				virtual void testBody() override;

			private:
				/**
				 * @brief send command argument
				 *
				 */
				bool sendCommandArgument;

		};

	}

}
/** @} */ // End of TesterTestGroup group

#endif // LONG_COMMAND_WITH_SPACES_TEST_H
