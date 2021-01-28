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
#include "app/settings/global.h"
#include "app/utility/logger/macros.h"
#include "tester/base/suite.h"
#include "tester/factories/test_factory.h"
#include "tester/shared/error_data.h"
#include "tester/utility/test_runner.h"

LOGGING_CONTEXT(testRunnerOverall, testRunner.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(testRunnerTests, testRunner.test, TYPE_LEVEL, INFO_VERBOSITY)
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

tester::utility::TestRunner::TestRunner(int & argc, char** argv) : factory(new tester::factory::TestFactory(argc, argv)), testList(tester::base::Suite::tests_container_t()), failedTests(tester::base::Suite::tests_container_t()) {
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerOverall, "Creating test runner");

	app::settings::Global::getInstance()->appendActionData(tester::utility::test_runner::jsonFullPath);
	this->factory->populate();

	this->fillTestList();
}

tester::utility::TestRunner::~TestRunner() {
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerOverall, "Test runner destructor");
}

void tester::utility::TestRunner::fillTestList() {

	const app::command_line::argument_map_t & settingsMap = app::settings::Global::getInstance()->getSettingsMap();

	const auto & suiteArgument = settingsMap.find("Suite");
	EXCEPTION_ACTION_COND((suiteArgument == settingsMap.cend()), throw, "Unable to find key suite in command line argument map");
	const std::string & suiteName = suiteArgument->second;
	EXCEPTION_ACTION_COND((suiteName.empty() == true), throw, "Unable to set up runner if name of suiteName is an empty string. Choose a suite or keep the default value that ensures that you runs all tests.");

	const auto & listArgument = settingsMap.find("List");
	EXCEPTION_ACTION_COND((listArgument == settingsMap.cend()), throw, "Unable to find key list in command line argument map");
	const std::string & listElements = listArgument->second;
	EXCEPTION_ACTION_COND((listElements.empty() == true), throw, "Unable to set up runner because no argument is attached to comand line argument list.");

	const auto & searchModeArgument = settingsMap.find("Search Mode");
	EXCEPTION_ACTION_COND((searchModeArgument == settingsMap.cend()), throw, "Unable to find key search mode in command line argument map");
	const std::string & searchMode = searchModeArgument->second;
	EXCEPTION_ACTION_COND((searchMode.empty() == true), throw, "Unable to set up runner because search mode is not defined.");

	// Strict search if running tests and search mode is set to strict
	bool strictSearch = (listElements.compare("none") == 0) && (searchMode.compare("strict") == 0);

	this->addSuitesToTestList(suiteName, strictSearch);

	for (const auto & test : this->testList) {
		LOG_INFO(app::logger::info_level_e::ZERO, testRunnerTests, "Adding test " << test->getName() << " from suite " << test->getSuite()->getName() << " to the list of tests to run");
	}
}


void tester::utility::TestRunner::addSuitesToTestList(const std::string & suiteName, bool strictSearch) {

	tester::base::Factory::suite_container_t suites;

	if (suiteName.compare("all") == 0) {
		const auto & matchedSuites = this->factory->getSuites();
		if (matchedSuites.empty() == false) {
			suites.insert(matchedSuites.begin(), matchedSuites.end());
		}
	} else {
		if (strictSearch == true) {
			const auto & suite = this->factory->findSuite(suiteName);
			EXCEPTION_ACTION_COND((suite == nullptr), throw, "Unable to find suite " << suiteName);
			if (suite != nullptr) {
				suites.insert(suite);
			}
		} else {
			const auto & matchedSuites = this->factory->weakFindSuite(suiteName);
			if (matchedSuites.empty() == false) {
				suites.insert(matchedSuites.begin(), matchedSuites.end());
			}
		}
	}

	const app::command_line::argument_map_t & settingsMap = app::settings::Global::getInstance()->getSettingsMap();

	const auto & testArgument = settingsMap.find("Test");
	EXCEPTION_ACTION_COND((testArgument == settingsMap.cend()), throw, "Unable to find key test in command line argument map");
	const std::string & testName = testArgument->second;
	EXCEPTION_ACTION_COND((testName.empty() == true), throw, "Unable to set up runner if name of the test is an empty string. Choose a test or keep the default value that ensures that you runs all tests.");

	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerTests, "Looking for " << ((testName.compare("all") == 0) ? "all tests" : (std::string("test ") + testName)) << " in " << ((suiteName.compare("all") == 0) ? "all test suites" : (std::string("suite ") + suiteName)));

	for (const auto & suite : suites) {
		this->addTestFromSuiteToTestList(suite, testName, strictSearch);
	}
}

void tester::utility::TestRunner::addTestFromSuiteToTestList(const std::shared_ptr<tester::base::Suite> & suite, const std::string & testName, bool strictSearch) {
	if (testName.compare("all") == 0) {
		const auto & matchedTests = suite->getTests();
		if (matchedTests.empty() == false) {
			this->testList.insert(matchedTests.begin(), matchedTests.end());
		}
	} else {
		if (strictSearch == true) {
			const std::shared_ptr<tester::base::Test> & test = suite->findTest(testName);
			EXCEPTION_ACTION_COND((test == nullptr), throw, "Unable to find test " << testName << " from suite " << suite->getName());
			if (test != nullptr) {
				this->testList.insert(test);
			}
		} else {
			const auto & matchedTests = suite->weakFindTest(testName);
			EXCEPTION_ACTION_COND((matchedTests.empty() == true), throw, "Unable to find test " << testName << " from suite " << suite->getName() << " with weak comparison");
			if (matchedTests.empty() == false) {
				this->testList.insert(matchedTests.begin(), matchedTests.end());
			}
		}
	}
}

void tester::utility::TestRunner::run() {

	const app::command_line::argument_map_t & settingsMap = app::settings::Global::getInstance()->getSettingsMap();

	const auto & listArgument = settingsMap.find("List");
	EXCEPTION_ACTION_COND((listArgument == settingsMap.cend()), throw, "Unable to find key list in command line argument map");

	const std::string & listElements = listArgument->second;

	std::string listPrint;

	for (const auto & test : this->testList) {
		try {
			if ((listElements.empty() == true) || (listElements.compare("none") == 0)) {
				test->run();
				tester::shared::test_status_e status = test->getStatus();
				if (status == tester::shared::test_status_e::FAIL) {
					this->failedTests.insert(test);
				}
			} else if (listElements.compare("tests") == 0) {
				const std::string line("- " + test->getName() + " in suite " + test->getSuite()->getName() + "\n");
				listPrint = listPrint + line;
			} else if (listElements.compare("suites") == 0) {
				const std::string line("- " + test->getSuite()->getName() + "\n");
				if (listPrint.find(line) == std::string::npos) {
					listPrint = listPrint + line;
				}
			}
		} catch (const app::exception::Exception & bexc) {
			test->addExceptionThrown(bexc.getLine(), bexc.getFilename(), bexc.getCondition(), bexc.getMessage());
			this->failedTests.insert(test);
		} catch (const QUnhandledException & unhandledexc) {
			const std::string condition = std::string();
			const std::string message("Got unhandled exception");
			test->addExceptionThrown(__LINE__, __FILE__, condition, message);
			this->failedTests.insert(test);
		} catch (const std::exception & exc) {
			const std::string condition = std::string();
			test->addExceptionThrown(__LINE__, __FILE__, condition, exc.what());
			this->failedTests.insert(test);
		}
	}

	if (listPrint.empty() == false) {
		LOG_INFO(app::logger::info_level_e::ZERO, testRunnerOverall, "List of selected " << listElements << ":" << listPrint);
	}
}

void tester::utility::TestRunner::printResults() const {
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "Runner results");
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "Statistics:");
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "- test run: " << this->testList.size());
	LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "- test failed: " << this->failedTests.size());
	for (const auto & test : this->failedTests) {
		const tester::base::Test::test_error_container_t & errorMap = test->getErrorMap();
		if (errorMap.empty() == false) {
			LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "Test \"" << test->getName() << "\" has " << errorMap.size() << " errors:");
			for (const auto & e : errorMap) {
				LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "- type " << e.first << " error data " << e.second);
			}
		}

		const tester::base::Test::test_error_container_t & expectedErrors = test->getExpectedErrors();
		if (expectedErrors.empty() == false) {
			LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "Test expected errors:");
			for (const auto & e : expectedErrors) {
				LOG_INFO(app::logger::info_level_e::ZERO, testRunnerResult, "- type " << e.first << " error data " << e.second);
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
