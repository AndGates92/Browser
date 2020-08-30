/**
 * @copyright
 * @file base_test.cpp
 * @author Andrea Gianarda
 * @date 24th August 2020
 * @brief Base test functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include <thread>

#include "global_enums.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "base_test.h"
#include "base_factory.h"
#include "base_suite.h"

Q_LOGGING_CATEGORY(baseTestOverall, "baseTest.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(baseTestTest, "baseTest.test", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(baseTestApp, "baseTest.app", MSG_TYPE_LEVEL)

bool base_test::TestPtrCompare::operator() (const std::shared_ptr<base_test::BaseTest> & rhs, const std::shared_ptr<base_test::BaseTest> & lhs) const {
	bool isSame = ((*rhs) == (*lhs));
	return isSame;
}

base_test::BaseTest::BaseTest(const std::shared_ptr<base_suite::BaseSuite> & testSuite, const std::string & testName) : window(nullptr), suite(testSuite), name(testName), errorMap(base_test::BaseTest::test_error_container_t()), expectedErrors(base_test::BaseTest::test_error_container_t()), state(test_enums::test_state_e::INSTATIATED), status(test_enums::test_status_e::NOT_RUN) {

	this->checkCreation();

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestOverall,  "Creating test " << QString::fromStdString(this->name) << " in suite " << QString::fromStdString(this->getSuite()->getName()));
}

base_test::BaseTest::BaseTest(const std::shared_ptr<base_factory::BaseFactory> & factory, const std::string & suiteName, const std::string & testName) : window(nullptr), name(testName), errorMap(base_test::BaseTest::test_error_container_t()), expectedErrors(base_test::BaseTest::test_error_container_t()), state(test_enums::test_state_e::INSTATIATED), status(test_enums::test_status_e::NOT_RUN) {

	std::shared_ptr<base_suite::BaseSuite> suiteSharedPtr = factory->findOrCreateSuite(suiteName);
	if (suiteSharedPtr != nullptr) {
		this->suite = suiteSharedPtr->weak_from_this();
	}

	this->checkCreation();

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestOverall,  "Creating test " << QString::fromStdString(this->name) << " in suite " << QString::fromStdString(suiteSharedPtr->getName()));
}

base_test::BaseTest::~BaseTest() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestOverall,  "Test " << QString::fromStdString(this->name) << " destructor");
}

bool base_test::BaseTest::operator== (const base_test::BaseTest & otherTest) const {
	bool nameComparison = (this->getName().compare(otherTest.getName()) < 0);
	bool suiteComparison = (this->getSuite() == otherTest.getSuite());
	bool factoryComparison = (this->getFactory() == otherTest.getFactory());

	bool compare = ((nameComparison == true) && (suiteComparison == true) && (factoryComparison == true));

	return compare;
}

void base_test::BaseTest::checkCreation() const {
	// Check creation
	QEXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Cannot create test with no name");
	QEXCEPTION_ACTION_COND((this->suite.expired() == true), throw, "Cannot create test " << QString::fromStdString(this->name) << " belonging to no suite");
	QEXCEPTION_ACTION_COND((this->getSuite() == nullptr), throw, "Cannot create test " << QString::fromStdString(this->name) << " as it belongs to a null suite");
}

void base_test::BaseTest::postProcessCreation() {
	this->getSuite()->addTest(this->shared_from_this());
	this->state = test_enums::test_state_e::CREATED;
}

void base_test::BaseTest::setup() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestTest,  "Setting up test " << QString::fromStdString(this->name));
	this->status = test_enums::test_status_e::NOT_RUN;
	// Wait for window to become visible
	while ((this->window == nullptr) || (this->window->getWindow()->isVisible() == false)) {
		std::this_thread::yield();
	}
}

void base_test::BaseTest::wrapup() {

	if (this->errorMatch() == true) {
		this->status = test_enums::test_status_e::PASS;
	} else {
		this->status = test_enums::test_status_e::FAIL;
	}

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestTest,  "Wrapping up test " << QString::fromStdString(this->name) << " status " << this->status);

}

void base_test::BaseTest::test() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestTest,  "Start test " << QString::fromStdString(this->getName()));
	this->setState(test_enums::test_state_e::SETTING_UP);
	this->setup();
	this->setState(test_enums::test_state_e::RUNNING);
	this->testBody();
	this->setState(test_enums::test_state_e::WRAPPING_UP);
	this->wrapup();
	this->setState(test_enums::test_state_e::FINISHED);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestTest,  "End test " << QString::fromStdString(this->getName()));

}

bool base_test::BaseTest::errorMatch() const {
	base_test::BaseTest::test_error_container_t::size_type errorNumberDifference = (this->errorMap.size() - this->expectedErrors.size());
	bool errorNumberMatch = (errorNumberDifference == 0);
	bool errorMapMatch = true;

	if (this->errorMap.empty() == false) {
		for (auto e : this->errorMap) {
			errorMapMatch &= this->searchError(this->expectedErrors, e.first, e.second, false);
		}
	}

	bool match = ((errorNumberMatch == true) && (errorMapMatch == true));

	return match;
}

const std::string & base_test::BaseTest::getName() const {
	QEXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Test cannot have an empty name");
	return this->name;
}

const std::shared_ptr<base_factory::BaseFactory> & base_test::BaseTest::getFactory() const {
	const std::shared_ptr<base_suite::BaseSuite> testSuite = this->getSuite();
	const std::shared_ptr<base_factory::BaseFactory> & testFactory = testSuite->getFactory();
	QEXCEPTION_ACTION_COND((testFactory == nullptr), throw, "Factory is a nullptr - test " << QString::fromStdString(this->name) << " must have a factory linked to it");

	return testFactory;
}

const std::shared_ptr<base_suite::BaseSuite> base_test::BaseTest::getSuite() const {
	QEXCEPTION_ACTION_COND((this->suite.expired() == true), throw,  "Unable to get test suite bar for test " << QString::fromStdString(this->name) << " as it has already expired");
	std::shared_ptr<base_suite::BaseSuite> testSuite = this->suite.lock();
	QEXCEPTION_ACTION_COND((testSuite == nullptr), throw, "Test suite is a nullptr - test " << QString::fromStdString(this->name) << " must belong to suite");

	return testSuite;
}

const std::unique_ptr<main_window_wrapper::MainWindowWrapper> & base_test::BaseTest::getWindow() const {

	QEXCEPTION_ACTION_COND((this->window == nullptr), throw, "Window is a nullptr - test " << QString::fromStdString(this->name) << " must ve a non null pointer to a window");
	return this->window;
}

CONST_GETTER(base_test::BaseTest::getErrorMap, base_test::BaseTest::test_error_container_t &, this->errorMap)
CONST_GETTER(base_test::BaseTest::getExpectedErrors, base_test::BaseTest::test_error_container_t &, this->expectedErrors)
BASE_SETTER_GETTER(base_test::BaseTest::setState, base_test::BaseTest::getState, test_enums::test_state_e, this->state)
BASE_GETTER(base_test::BaseTest::getStatus, test_enums::test_status_e, this->status)

void base_test::BaseTest::addExpectedError(const base_test::BaseTest::test_error_container_t & errors) {
	for (auto it = errors.cbegin(); it != errors.cend(); it++) {
		this->addExpectedError(it->first, it->second);
	}
}

void base_test::BaseTest::addExpectedError(const test_enums::error_type_e & type, const error_data::ErrorData & data) {
	bool errorFound = this->searchError(this->expectedErrors, type, data, false);
	if (errorFound == false) {
		this->addError(this->expectedErrors, type, data);
	}
}

void base_test::BaseTest::addAssertionFailure(const int & line, const std::string & filename, const std::string & condition, const test_enums::error_type_e & type, const std::string & errorMessage) {
	const error_data::ErrorData data(this->weak_from_this(), filename, line, condition, errorMessage);
	this->addError(this->errorMap, type, data);
}

void base_test::BaseTest::addError(test_error_container_t & errors, const test_enums::error_type_e & type, const error_data::ErrorData & data) {
	errors.insert(std::pair<test_enums::error_type_e, error_data::ErrorData>(type, data));
}

bool base_test::BaseTest::searchError(const base_test::BaseTest::test_error_container_t & container, const test_enums::error_type_e & type, const error_data::ErrorData & data, const bool & fullMatch) const {
	auto keyValues = container.equal_range(type);

	bool foundKey = (keyValues.first != keyValues.second);
	bool foundValue = false;

	// If no element is found, equal_range returns a pair where both elements are the same, i.e. a range of 0
	if (foundKey == true) {
		auto sameValue = [&] (const std::pair<test_enums::error_type_e, error_data::ErrorData> & e) {
			bool typeMatch = (e.first == type);
			bool dataMatch = false;
			if (fullMatch == true) {
				dataMatch = (e.second == data);
			} else {
				dataMatch = (e.second.partialEqual(data) == true);
			}
			return ((typeMatch == true) && (dataMatch == true));
		};
		foundValue = (std::find_if(keyValues.first, keyValues.second, sameValue) != keyValues.second);
	}

	bool found = ((foundKey == true) && (foundValue == true));

	return found;
}

void base_test::BaseTest::run() {

	// Check that everything is ok before kicking off the test
	QEXCEPTION_ACTION_COND(((this->getSuite() == nullptr) || (this->suite.expired() == true)), throw, "Cannot run test " << QString::fromStdString(this->name) << " belonging to no suite");
	QEXCEPTION_ACTION_COND((this->getSuite()->findTest(this->getName()) == nullptr), throw, "Unable to find test " << QString::fromStdString(this->name) << " in suite " << QString::fromStdString(this->getSuite()->getName()));
	const test_enums::test_state_e expectedState = test_enums::test_state_e::CREATED;
	QEXCEPTION_ACTION_COND((this->getState() != expectedState), throw, "Test " << QString::fromStdString(this->name) << " is expected to be in state " << expectedState << " whereas it is in state " << this->getState());

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseTestOverall,  "Running test " << QString::fromStdString(this->name) << " in suite " << QString::fromStdString(this->getSuite()->getName()));

	const std::shared_ptr<base_factory::BaseFactory> & factory = this->getFactory();
	QApplication app(factory->getArgc(), factory->getArgv());

	this->window = std::make_unique<main_window_wrapper::MainWindowWrapper>(Q_NULLPTR, Qt::Window);
	this->window->show();

	this->test();

	if (this->state != test_enums::test_state_e::FINISHED) {
		this->status = test_enums::test_status_e::FAIL;
	}
}

const std::string base_test::BaseTest::print() const {
	std::string testInfo;

	testInfo = testInfo + " name: " + this->name;
	testInfo = testInfo + " state: " + this->state;
	testInfo = testInfo + " status: " + this->status + "\n";

	if (this->expectedErrors.empty() == false) {
		testInfo = testInfo + " expected errors:\n";
		for (auto e : this->expectedErrors) {
			testInfo = testInfo + " - type: " + e.first + " data: " + e.second + "\n";
		}
	}

	if (this->errorMap.empty() == false) {
		testInfo = testInfo + " current errors:\n";
		for (auto e : this->errorMap) {
			testInfo = testInfo + " - type: " + e.first + " data: " + e.second + "\n";
		}
	}

	return testInfo;
}

