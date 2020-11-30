/**
 * @copyright
 * @file test_runner.cpp
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Test runner functions
 */

// Qt libraries
#include <QtCore/QUnhandledException>

#include "app/shared/exception.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "tester/factories/test_factory.h"
#include "tester/base/suite.h"
#include "tester/utility/test_runner.h"
#include "app/settings/global.h"

LOGGING_CONTEXT(testRunnerOverall, testRunner.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(testRunnerResult, testRunner.result, TYPE_LEVEL, INFO_VERBOSITY)

namespace tester {

	namespace utility {

		namespace test_runner {

			namespace {
				/**
				 * @brief Path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonPath("json/");

				/**
				 * @brief Filename storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonName("tester_arguments.json");

				/**
				 * @brief Full path towards JSON file storing informations about commands and shortcuts
				 *
				 */
				static const std::string jsonFullPath(jsonPath + jsonName);
			}

		}

	}

}

tester::utility::TestRunner::TestRunner(int & argc, char** argv) : factory(new tester::factory::TestFactory(argc, argv)), testList(tester::utility::TestRunner::test_list_container_t()), failedTests(tester::utility::TestRunner::test_list_container_t()) {
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerOverall,  "Creating test runner");

	std::unique_ptr<app::command_line::Parser> runnerArgumentParser = std::make_unique<app::command_line::Parser>(argc, argv, tester::utility::test_runner::jsonFullPath);
	const app::command_line::argument_map_t & runnerArgumentMap = runnerArgumentParser->getDecodedArguments();
	app::settings::Global::getInstance()->addArguments(runnerArgumentMap);

	this->factory->populate();
	this->fillTestList();
}

tester::utility::TestRunner::~TestRunner() {
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerOverall,  "Test runner destructor");
}

void tester::utility::TestRunner::fillTestList() {

	const app::command_line::argument_map_t & settingsMap = app::settings::Global::getInstance()->getSettingsMap();

	const auto & suiteArgument = settingsMap.find("Suite");
	EXCEPTION_ACTION_COND((suiteArgument == settingsMap.cend()), throw, "Unable to find key suite in command line argument map");
	const std::string & suiteName = suiteArgument->second;

	const auto & testArgument = settingsMap.find("Test");
	EXCEPTION_ACTION_COND((testArgument == settingsMap.cend()), throw, "Unable to find key test in command line argument map");
	const std::string & testName = testArgument->second;

	if (suiteName.compare("all") == 0) {
		const tester::base::Factory::suite_container_t & suites = this->factory->getSuites();
		for (const auto & suite : suites) {
			this->addTestFromSuiteToTestList(suite, testName);
		}
	} else {
		const std::shared_ptr<tester::base::Suite> & suite = this->factory->findSuite(suiteName);
		this->addTestFromSuiteToTestList(suite, testName);
	}
}

void tester::utility::TestRunner::addTestFromSuiteToTestList(const std::shared_ptr<tester::base::Suite> & suite, const std::string & testName) {
	if (testName.compare("all") == 0) {
		const tester::base::Suite::tests_container_t & tests = suite->getTests();
		for (const auto & test : tests) {
			this->testList.push_back(test);
		}
	} else {
		const std::shared_ptr<tester::base::Test> & test = suite->findTest(testName);
		if (test != nullptr) {
			this->testList.push_back(test);
		}
	}
}

void tester::utility::TestRunner::run() {
	for (const auto & test : this->testList) {
		try {
				test->run();
				tester::shared::test_status_e status = test->getStatus();
				if (status == tester::shared::test_status_e::FAIL) {
					this->failedTests.push_back(test);
				}
		} catch (const app::exception::Exception & bexc) {
			test->addExceptionThrown(bexc.getLine(), bexc.getFilename(), bexc.getCondition(), bexc.getMessage());
			this->failedTests.push_back(test);
		} catch (const QUnhandledException & unhandledexc) {
			const std::string condition = std::string();
			const std::string message("Got unhandled exception");
			test->addExceptionThrown(__LINE__, __FILE__, condition, message);
			this->failedTests.push_back(test);
		} catch (const std::exception & exc) {
			const std::string condition = std::string();
			test->addExceptionThrown(__LINE__, __FILE__, condition, exc.what());
			this->failedTests.push_back(test);
		}
	}
}

void tester::utility::TestRunner::printResults() const {
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "Runner results");
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "Statistics:");
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "- test run: " << this->testList.size());
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "- test failed: " << this->failedTests.size());
	for (const auto & test : this->failedTests) {
		const tester::base::Test::test_error_container_t & errorMap = test->getErrorMap();
		if (errorMap.empty() == false) {
			LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "Test errors:");
			for (const auto & e : errorMap) {
				LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "- type " << e.first << " error data " << e.second);
			}
		}

		const tester::base::Test::test_error_container_t & expectedErrors = test->getExpectedErrors();
		if (expectedErrors.empty() == false) {
			LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "Test expected errors:");
			for (const auto & e : expectedErrors) {
				LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult,  "- type " << e.first << " error data " << e.second);
			}
		}
	}
}

const std::string tester::utility::TestRunner::print() const {
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
