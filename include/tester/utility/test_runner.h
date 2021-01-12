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

#include "tester/shared/enums.h"
#include "app/shared/constructor_macros.h"
#include "app/utility/log/printable_object.h"

/** @defgroup UtilityGroup Utility Doxygen Group
 *  Utility functions and classes
 *  @{
 */
namespace tester {
	namespace factory {
		class TestFactory;
	}

	namespace base {
		class Suite;
		class Test;
	}

	namespace utility {

		/**
		 * @brief TestRunner class
		 *
		 */
		class TestRunner : public app::printable_object::PrintableObject {

			public:

				/**
				 * @brief type of test error container
				 *
				 */
				typedef std::list<std::shared_ptr<tester::base::Test>> test_list_container_t;

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
				std::shared_ptr<tester::factory::TestFactory> factory;

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
				 * @brief Function: void addTestFromSuiteToTestList(const std::shared_ptr<tester::base::Suite> & suite, const std::string & testName)
				 *
				 * \param suite: suite to search test into
				 * \param testName: name of the test
				 *
				 * This function search a test in a suite to add it to a suite.
				 * If the name of the test is all, then all tests in the suite are added to the test list
				 */
				void addTestFromSuiteToTestList(const std::shared_ptr<tester::base::Suite> & suite, const std::string & testName);

				// Move and copy constructor
				/**
				 * @brief Disable move and copy constructors and operator= overloading for class TestRunner
				 *
				 */
				DISABLE_COPY_MOVE(TestRunner)

		};

	}

}
/** @} */ // End of UtilityGroup group

#endif // TEST_RUNNER_H
