#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H
/**
 * @copyright
 * @file test_runner.h
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Test runner header file
 */

#include <list>

#include "common/include/test_enums.h"
#include "common/include/constructor_macros.h"
#include "utility/log/include/printable_object.h"
#include "settings/include/command_line_parser.h"

/** @defgroup TestRunnerGroup Test Runner Group
 *  Test runner functions and classes
 *  @{
 */

namespace test_factory {
	class TestFactory;
}

namespace base_suite {
	class BaseSuite;
}

namespace base_test {
	class BaseTest;
}

namespace test_runner {

	/**
	 * @brief TestRunner class
	 *
	 */
	class TestRunner : public printable_object::PrintableObject {

		public:

			/**
			 * @brief type of test error container
			 *
			 */
			typedef std::list<std::shared_ptr<base_test::BaseTest>> test_list_container_t;

			/**
			 * @brief Function: explicit TestRunner(int & argc, char** argv)
			 *
			 * \param argc: number of arguments
			 * \param argv: value of arguments
			 *
			 * Test Runner constructor
			 */
			explicit TestRunner(int & argc, char** argv);

			/**
			 * @brief Function: virtual ~TestRunner()
			 *
			 * Test Runner destructor
			 */
			virtual ~TestRunner();

			/**
			 * @brief Function: void run()
			 *
			 * This function runs all the selected tests
			 */
			void run();

			/**
			 * @brief Function: void printResults() const
			 *
			 * This function prints the results of the runner
			 */
			void printResults() const;

			/**
			 * @brief Function: const std::string print() const override
			 *
			 * \return runner informations to std::string
			 *
			 * This functions prints runner informations to std::string
			 */
			const std::string print() const override;

		private:
			/**
			 * @brief factory of the tester
			 *
			 */
			std::shared_ptr<test_factory::TestFactory> factory;

			/**
			 * @brief list of tests to run
			 *
			 */
			test_list_container_t testList;

			/**
			 * @brief list of failed tests
			 *
			 */
			test_list_container_t failedTests;

			/**
			 * @brief Function: void fillTestList()
			 *
			 * This function fills the testlist based on the parsed data
			 */
			void fillTestList();

			/**
			 * @brief Function: void addTestFromSuiteToTestList(const std::shared_ptr<base_suite::BaseSuite> & suite, const std::string & testName)
			 *
			 * \param suite: suite to search test into
			 * \param testName: name of the test
			 *
			 * This function search a test in a suite to add it to a suite.
			 * If the name of the test is all, then all tests in the suite are added to the test list
			 */
			void addTestFromSuiteToTestList(const std::shared_ptr<base_suite::BaseSuite> & suite, const std::string & testName);

			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class TestRunner
			 *
			 */
			DISABLE_COPY_MOVE(TestRunner)

	};

}
/** @} */ // End of TestRunnerGroup group

#endif // TEST_RUNNER_H
