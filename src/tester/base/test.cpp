/**
 * @copyright
 * @file test.cpp
 * @author Andrea Gianarda
 * @date 24th August 2020
 * @brief Base test functions
 */

// Qt libraries
#include <QtWidgets/QApplication>

#include <locale>
#include <thread>

#include "app/windows/main_window/window/main_window.h"
#include "app/windows/main_window/window/ctrl_wrapper.h"
#include "app/windows/main_window/window/core.h"
#include "app/shared/setters_getters.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "tester/shared/error_data.h"
#include "tester/base/test.h"
#include "tester/base/factory.h"
#include "tester/base/suite.h"
#include "tester/top/main_window_wrapper.h"

LOGGING_CONTEXT(baseTestOverall, baseTest.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(baseTestTest, baseTest.test, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(baseTestError, baseTest.error, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(baseTestApp, baseTest.app, TYPE_LEVEL, INFO_VERBOSITY)

bool tester::base::TestPtrCompare::operator() (const std::shared_ptr<tester::base::Test> & rhs, const std::shared_ptr<tester::base::Test> & lhs) const {
	bool isSame = ((*rhs) == (*lhs));
	return isSame;
}

tester::base::Test::Test(const std::shared_ptr<tester::base::Suite> & testSuite, const std::string & testName) : windowWrapper(nullptr), suite(testSuite), name(testName), errorMap(tester::base::Test::test_error_container_t()), expectedErrors(tester::base::Test::test_error_container_t()), state(tester::shared::test_state_e::INSTATIATED), status(tester::shared::test_status_e::NOT_RUN) {

	this->checkCreation();

	LOG_INFO(app::logger::info_level_e::ZERO, baseTestOverall,  "Creating test " << this->name << " in suite " << this->getSuite()->getName());
}

tester::base::Test::Test(const std::shared_ptr<tester::base::Factory> & factory, const std::string & suiteName, const std::string & testName) : windowWrapper(nullptr), name(testName), errorMap(tester::base::Test::test_error_container_t()), expectedErrors(tester::base::Test::test_error_container_t()), state(tester::shared::test_state_e::INSTATIATED), status(tester::shared::test_status_e::NOT_RUN) {

	std::shared_ptr<tester::base::Suite> suiteSharedPtr = factory->findOrCreateSuite(suiteName);
	if (suiteSharedPtr != nullptr) {
		this->suite = suiteSharedPtr->weak_from_this();
	}

	this->checkCreation();

	LOG_INFO(app::logger::info_level_e::ZERO, baseTestOverall,  "Creating test " << this->name << " in suite " << suiteSharedPtr->getName());
}

tester::base::Test::~Test() {
	LOG_INFO(app::logger::info_level_e::ZERO, baseTestOverall,  "Test " << this->name << " destructor");
}

bool tester::base::Test::operator== (const tester::base::Test & otherTest) const {
	bool nameComparison = (this->getName().compare(otherTest.getName()) < 0);
	bool suiteComparison = (this->getSuite() == otherTest.getSuite());
	bool factoryComparison = (this->getFactory() == otherTest.getFactory());

	bool compare = ((nameComparison == true) && (suiteComparison == true) && (factoryComparison == true));

	return compare;
}

void tester::base::Test::checkCreation() const {
	// Check creation
	EXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Cannot create test with no name");
	EXCEPTION_ACTION_COND((this->suite.expired() == true), throw, "Cannot create test " << this->name << " belonging to no suite");
	EXCEPTION_ACTION_COND((this->getSuite() == nullptr), throw, "Cannot create test " << this->name << " as it belongs to a null suite");
}

void tester::base::Test::postProcessCreation() {
	this->getSuite()->addTest(this->shared_from_this());
	this->state = tester::shared::test_state_e::CREATED;
}

bool tester::base::Test::setup() {
	LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest,  "Setting up test " << this->name);
	this->status = tester::shared::test_status_e::NOT_RUN;
	// Wait for window to become visible
	while ((this->windowWrapper == nullptr) || (this->getWindow()->isVisible() == false)) {
		std::this_thread::yield();
	}

	// Process events after making the tab visible
	QApplication::processEvents(QEventLoop::AllEvents);

	WAIT_FOR_CONDITION((QApplication::activeWindow() != nullptr), tester::shared::error_type_e::WINDOW, "Pointer to active window is  not expected to be null", 1000);

	return (this->errorMap.size() == 0);
}

void tester::base::Test::wrapup() {

	if (this->getWindow()->isVisible() == true) {
		const std::unique_ptr<app::main_window::window::CtrlWrapper> & windowCtrl =  this->windowWrapper->getWindowCtrl();
		const std::shared_ptr<app::main_window::window::Core> & windowCore = this->windowWrapper->getWindowCore();

		// Send escape to close any menu or popup that may be opened
		tester::base::Test::sendKeyClickToFocus(Qt::Key_Escape);
		QApplication::processEvents(QEventLoop::AllEvents);

		const int tabCount = windowCore->getTabCount();

		// Close all tabs one by one by sending as many close tab command as opened tabs
		for (int idx = 0; idx < tabCount; idx++) {
			const std::string closeTabCommand(":close-tab");
			LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest, "Type " << closeTabCommand);
			QTest::keyClicks(windowCtrl.get(), QString::fromStdString(closeTabCommand));
			QApplication::processEvents(QEventLoop::AllEvents);
			QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);
			QApplication::processEvents(QEventLoop::AllEvents);
		}

		WAIT_FOR_CONDITION((windowCore->getTabCount() == 0), tester::shared::error_type_e::TABS, "Failed to closed " + std::to_string(tabCount) + " tab(s). There are still " + std::to_string(windowCore->getTabCount()) + " opened.", 5000);

		const std::string quitCommand(":quit");
		LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest, "Type " << quitCommand);

		QTest::keyClicks(windowCtrl.get(), QString::fromStdString(quitCommand));
		QApplication::processEvents(QEventLoop::AllEvents);
		QTest::keyClick(windowCtrl.get(), Qt::Key_Enter);
		QApplication::processEvents(QEventLoop::AllEvents);
		WAIT_FOR_CONDITION((this->getWindow()->isHidden() == true), tester::shared::error_type_e::WINDOW, "Window is still active even though command " + quitCommand + " was executed.", 5000);

	}

	if (this->errorMatch() == true) {
		this->status = tester::shared::test_status_e::PASS;
	} else {
		this->status = tester::shared::test_status_e::FAIL;
	}

	LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest,  "Wrapping up test " << this->name << " status " << this->status);

}

void tester::base::Test::test() {

	LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest,  "Start test " << this->getName());
	this->setState(tester::shared::test_state_e::SETTING_UP);
	bool setupSuccessful = this->setup();
	this->setState(tester::shared::test_state_e::RUNNING);
	if (setupSuccessful == true) {
		this->testBody();
	}
	this->setState(tester::shared::test_state_e::WRAPPING_UP);
	this->wrapup();
	this->setState(tester::shared::test_state_e::FINISHED);
	LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest,  "End test " << this->getName());

}

bool tester::base::Test::errorMatch() const {
	tester::base::Test::test_error_container_t::size_type errorNumberDifference = (this->errorMap.size() - this->expectedErrors.size());
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

const std::string & tester::base::Test::getName() const {
	EXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Test cannot have an empty name");
	return this->name;
}

CONST_SETTER(tester::base::Test::setName, std::string &, this->name)

const std::shared_ptr<tester::base::Factory> & tester::base::Test::getFactory() const {
	const std::shared_ptr<tester::base::Suite> testSuite = this->getSuite();
	const std::shared_ptr<tester::base::Factory> & testFactory = testSuite->getFactory();
	EXCEPTION_ACTION_COND((testFactory == nullptr), throw, "Factory is a nullptr - test " << this->name << " must have a factory linked to it");

	return testFactory;
}

const std::shared_ptr<tester::base::Suite> tester::base::Test::getSuite() const {
	EXCEPTION_ACTION_COND((this->suite.expired() == true), throw,  "Unable to get test suite bar for test " << this->name << " as it has already expired");
	const std::shared_ptr<tester::base::Suite> testSuite = this->suite.lock();
	EXCEPTION_ACTION_COND((testSuite == nullptr), throw, "Test suite is a nullptr - test " << this->name << " must belong to suite");

	return testSuite;
}

const std::unique_ptr<app::main_window::window::MainWindow> & tester::base::Test::getWindow() const {

	EXCEPTION_ACTION_COND((this->windowWrapper == nullptr), throw, "Window wrapper is a nullptr - test " << this->name << " must have a non null pointer to a window wrapper");
	const std::unique_ptr<app::main_window::window::MainWindow> & window = this->windowWrapper->getWindow();
	EXCEPTION_ACTION_COND((window == nullptr), throw, "Window is a nullptr - test " << this->name << " must have a non null pointer to a window");
	return window;
}

CONST_GETTER(tester::base::Test::getErrorMap, tester::base::Test::test_error_container_t &, this->errorMap)
CONST_GETTER(tester::base::Test::getExpectedErrors, tester::base::Test::test_error_container_t &, this->expectedErrors)
CONST_SETTER_GETTER(tester::base::Test::setState, tester::base::Test::getState, tester::shared::test_state_e &, this->state)
CONST_GETTER(tester::base::Test::getStatus, tester::shared::test_status_e &, this->status)

void tester::base::Test::addExpectedError(const tester::base::Test::test_error_container_t & errors) {
	for (auto it = errors.cbegin(); it != errors.cend(); it++) {
		this->addExpectedError(it->first, it->second);
	}
}

void tester::base::Test::addExpectedError(const tester::shared::error_type_e & type, const tester::shared::ErrorData & data) {
	bool errorFound = this->searchError(this->expectedErrors, type, data, false);
	if (errorFound == false) {
		this->addError(this->expectedErrors, type, data);
	}
}

void tester::base::Test::addAssertionFailure(const int & line, const std::string & filename, const std::string & condition, const tester::shared::error_type_e & type, const std::string & errorMessage) {
	const tester::shared::ErrorData data(this->weak_from_this(), filename, line, condition, errorMessage);
	LOG_INFO(app::logger::info_level_e::ZERO, baseTestTest,  "ASSERTION FAILED: " << data);
	this->addError(this->errorMap, type, data);
}

void tester::base::Test::addExceptionThrown(const int & line, const std::string & filename, const std::string & condition, const std::string & errorMessage) {
	const tester::shared::error_type_e type = tester::shared::error_type_e::EXCEPTION;
	this->addAssertionFailure(line, filename, condition, type, errorMessage);

	if (this->getWindow()->isVisible() == true) {
		QApplication::processEvents(QEventLoop::AllEvents);
		if ((this->state != tester::shared::test_state_e::SETTING_UP) || (this->state != tester::shared::test_state_e::RUNNING)) {
			this->wrapup();
		} else {
			this->getWindow()->close();
		}
	}
}

bool tester::base::Test::waitForCondition(const std::function<bool(void)> & conditionFunction, const std::chrono::milliseconds & timeout) const {
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	bool result = false;
	while (((result = conditionFunction()) == false) && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime) < timeout)) {
		QApplication::processEvents(QEventLoop::AllEvents);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return result;
}

void tester::base::Test::addError(test_error_container_t & errors, const tester::shared::error_type_e & type, const tester::shared::ErrorData & data) {
	errors.insert(std::pair<tester::shared::error_type_e, tester::shared::ErrorData>(type, data));
}

bool tester::base::Test::searchError(const tester::base::Test::test_error_container_t & container, const tester::shared::error_type_e & type, const tester::shared::ErrorData & data, const bool & fullMatch) const {
	auto keyValues = container.equal_range(type);

	bool foundKey = (keyValues.first != keyValues.second);
	bool foundValue = false;

	// If no element is found, equal_range returns a pair where both elements are the same, i.e. a range of 0
	if (foundKey == true) {
		auto sameValue = [&] (const std::pair<tester::shared::error_type_e, tester::shared::ErrorData> & e) {
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

void tester::base::Test::run() {

	// Check that everything is ok before kicking off the test
	EXCEPTION_ACTION_COND(((this->getSuite() == nullptr) || (this->suite.expired() == true)), throw, "Cannot run test " << this->name << " belonging to no suite");
	EXCEPTION_ACTION_COND((this->getSuite()->findTest(this->getName()) == nullptr), throw, "Unable to find test " << this->name << " in suite " << this->getSuite()->getName());
	const tester::shared::test_state_e expectedState = tester::shared::test_state_e::CREATED;
	EXCEPTION_ACTION_COND((this->getState() != expectedState), throw, "Test " << this->name << " is expected to be in state " << expectedState << " whereas it is in state " << this->getState());

	LOG_INFO(app::logger::info_level_e::ZERO, baseTestOverall,  "Running test " << this->name << " in suite " << this->getSuite()->getName());

	const std::shared_ptr<tester::base::Factory> & factory = this->getFactory();

	QApplication * app = static_cast<QApplication *>(QApplication::instance());
	if (app == nullptr) {
		app = new QApplication(factory->getArgc(), factory->getArgv());
	}

	this->windowWrapper = std::make_unique<tester::main_window_wrapper::MainWindowWrapper>(Q_NULLPTR, Qt::Window);
	this->windowWrapper->show();

	WAIT_FOR_CONDITION((this->getWindow()->isHidden() == false), tester::shared::error_type_e::WINDOW, "Window is not active at the start of test " + this->getName(), 5000);

	this->test();

	if (this->state != tester::shared::test_state_e::FINISHED) {
		this->status = tester::shared::test_status_e::FAIL;
	}
}

const std::string tester::base::Test::print() const {
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

void tester::base::Test::sendKeyClickToFocus(const Qt::Key key) {
	QWidget * focusWidget = QApplication::focusWidget();
	QTest::keyClick(focusWidget, key);
	QApplication::processEvents(QEventLoop::AllEvents);
}

void tester::base::Test::sendKeyClicksToFocus(const std::string & text) {
	QWidget * focusWidget = QApplication::focusWidget();
	QTest::keyClicks(focusWidget, QString::fromStdString(text));
	QApplication::processEvents(QEventLoop::AllEvents);
}

void tester::base::Test::sendKeyEventToFocus(const QTest::KeyAction & keyAction, const char character) {
	QWidget * focusWidget = QApplication::focusWidget();
	Qt::KeyboardModifiers modifier = Qt::NoModifier;
	if (isupper(character) != 0) {
		modifier |= Qt::ShiftModifier;
	}
	QTest::keyEvent(keyAction, focusWidget, character, modifier);
	QApplication::processEvents(QEventLoop::AllEvents);
}

void tester::base::Test::sendKeyEventsToFocus(const QTest::KeyAction & keyAction, const std::string & text) {
	// Send text characters one by one
	for (const auto & character : text) {
		tester::base::Test::sendKeyEventToFocus(keyAction, character);
	}
}
