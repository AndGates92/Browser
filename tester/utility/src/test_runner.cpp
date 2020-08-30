/**
 * @copyright
 * @file test_runner.cpp
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Test runner functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "logging_macros.h"
#include "test_factory.h"
#include "base_suite.h"
#include "test_runner.h"
#include "exception_macros.h"

Q_LOGGING_CATEGORY(testRunnerOverall, "testRunner.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(testRunnerResult, "testRunner.result", MSG_TYPE_LEVEL)

test_runner::TestRunner::TestRunner(int & argc, char** argv) : factory(new test_factory::TestFactory(argc, argv)), parser(new command_line_parser::CommandLineParser(argc, argv)), testList(test_runner::TestRunner::test_list_container_t()), failedTests(test_runner::TestRunner::test_list_container_t()) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerOverall,  "Creating test runner");

	this->factory->populate();
	this->fillTestList();
}

test_runner::TestRunner::~TestRunner() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerOverall,  "Test runner destructor");
}

void test_runner::TestRunner::fillTestList() {

	const command_line_parser::CommandLineParser::argument_map_t & argumentMap = this->parser->getDecodedArguments();

	const auto & suiteArgument = argumentMap.find("Suite");
	QEXCEPTION_ACTION_COND((suiteArgument == argumentMap.cend()), throw, "Unable to find key suite in command line argument map");
	const std::string & suiteName = suiteArgument->second;

	const auto & testArgument = argumentMap.find("Test");
	QEXCEPTION_ACTION_COND((testArgument == argumentMap.cend()), throw, "Unable to find key test in command line argument map");
	const std::string & testName = testArgument->second;

	if (suiteName.compare("all") == 0) {
		const base_factory::BaseFactory::suite_container_t & suites = this->factory->getSuites();
		for (const auto & suite : suites) {
			this->addTestFromSuiteToTestList(suite, testName);
		}
	} else {
		const std::shared_ptr<base_suite::BaseSuite> & suite = this->factory->findSuite(suiteName);
		this->addTestFromSuiteToTestList(suite, testName);
	}
}

void test_runner::TestRunner::addTestFromSuiteToTestList(const std::shared_ptr<base_suite::BaseSuite> & suite, const std::string & testName) {
	if (testName.compare("all") == 0) {
		const base_suite::BaseSuite::tests_container_t & tests = suite->getTests();
		for (const auto & test : tests) {
			this->testList.push_back(test);
		}
	} else {
		const std::shared_ptr<base_test::BaseTest> & test = suite->findTest(testName);
		if (test != nullptr) {
			this->testList.push_back(test);
		}
	}
}

void test_runner::TestRunner::run() {
	for (const auto & test : this->testList) {
		test->run();
		test_enums::test_status_e status = test->getStatus();
		if (status == test_enums::test_status_e::FAIL) {
			this->failedTests.push_back(test);
		}
	}
}

void test_runner::TestRunner::printResults() const {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "Runner results");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "Statistics:");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "- test run: " << this->testList.size());
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "- test failed: " << this->failedTests.size());
	for (const auto & test : this->failedTests) {
		const base_test::BaseTest::test_error_container_t & errorMap = test->getErrorMap();
		if (errorMap.empty() == false) {
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "Test errors:");
			for (const auto & e : errorMap) {
				QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "- type " << e.first << " error data " << e.second);
			}
		}

		const base_test::BaseTest::test_error_container_t & expectedErrors = test->getExpectedErrors();
		if (expectedErrors.empty() == false) {
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "Test expected errors:");
			for (const auto & e : expectedErrors) {
				QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testRunnerResult,  "- type " << e.first << " error data " << e.second);
			}
		}
	}
}

const std::string test_runner::TestRunner::print() const {
	std::string runnerInfo;

	if (this->testList.empty() == false) {
		runnerInfo = runnerInfo + "Runner tests:\n";
		for (const auto & test : this->testList) {
			runnerInfo = runnerInfo + "- test " + test->getName() + " in suite " + test->getSuite()->getName() + "\n";
		}
	}

	if (this->failedTests.empty() == false) {
		runnerInfo = runnerInfo + "Failed tests:\n";
		for (const auto & test : this->failedTests) {
			runnerInfo = runnerInfo + "- test " + test->getName() + " in suite " + test->getSuite()->getName() + "\n";
		}
	}
	return runnerInfo;
}
