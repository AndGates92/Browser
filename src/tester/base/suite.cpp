/**
 * @copyright
 * @file suite.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Test suite functions
 */

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "tester/base/suite.h"
#include "tester/base/factory.h"

LOGGING_CONTEXT(baseSuiteOverall, baseSuite.overall, TYPE_LEVEL, INFO_VERBOSITY)

bool tester::base::SuitePtrCompare::operator() (const std::shared_ptr<tester::base::Suite> & rhs, const std::shared_ptr<tester::base::Suite> & lhs) const {
	bool isSame = ((*rhs) == (*lhs));
	return isSame;
}

tester::base::Suite::Suite(const std::shared_ptr<tester::base::Factory> & testFactory, const std::string & suiteName, const tester::base::Suite::tests_container_t & testList) : factory(testFactory), name(suiteName), tests(testList) {

	EXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Cannot create test suite with no name");
	LOG_INFO(app::logger::info_level_e::ZERO, baseSuiteOverall,  "Creating " << *this);

}

tester::base::Suite::~Suite() {

	LOG_INFO(app::logger::info_level_e::ZERO, baseSuiteOverall,  "Test suite destructor");

}

const std::shared_ptr<tester::base::Factory> tester::base::Suite::getFactory() const {
	EXCEPTION_ACTION_COND((this->factory.expired() == true), throw,  "Unable to get factory bar for test " << this->name << " as it has already expired");
	std::shared_ptr<tester::base::Factory> testFactory = this->factory.lock();
	EXCEPTION_ACTION_COND((testFactory == nullptr), throw, "Factory is a nullptr - suite " << this->name << " must have a factory linked to it");

	return testFactory;
}

const std::string & tester::base::Suite::getName() const {
	EXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Suite cannot have an empty name");
	return this->name;
}

void tester::base::Suite::addTest(const std::shared_ptr<tester::base::Test> & test) {
	const auto & insertReturnPair = this->tests.insert(test);
	EXCEPTION_ACTION_COND((insertReturnPair.second == false), throw, "Unable to insert test " << test->getName() << " to the list of tests in suite " << this->name);
}

CONST_GETTER(tester::base::Suite::getTests, tester::base::Suite::tests_container_t &, this->tests)

const std::string tester::base::Suite::print() const {
	std::string suiteInfo;

	suiteInfo = suiteInfo + " suite " + this->getName();

	if (this->tests.empty() == false) {
		suiteInfo = suiteInfo + " with tests:\n";
		for (auto t : this->tests) {
			suiteInfo = suiteInfo + " - ";
			suiteInfo = suiteInfo + *t + "\n";
		}
	} else {
		suiteInfo = suiteInfo + " with no tests\n";
	}

	return suiteInfo;
}

bool tester::base::Suite::operator== (const tester::base::Suite & otherSuite) const {
	bool nameComparison = (this->getName().compare(otherSuite.getName()) < 0);
	bool factoryComparison = (this->getFactory() == otherSuite.getFactory());

	const tester::base::Suite::tests_container_t & thisTests = this->getTests();
	const tester::base::Suite::tests_container_t & otherTests = otherSuite.getTests();
	tester::base::Suite::tests_container_t::size_type testNumberDifference = (thisTests.size() - otherTests.size());
	bool testNumberMatch = (testNumberDifference == 0);
	bool testMatch = true;

	if (otherTests.empty() == false) {
		for (auto t : otherTests) {
			testMatch &= (thisTests.find(t) != thisTests.end());
		}
	}

	bool compare = ((nameComparison == true) && (factoryComparison == true) && (testNumberMatch == true) && (testMatch == true));

	return compare;
}

std::shared_ptr<tester::base::Test> tester::base::Suite::findTest(const std::string & testName) const {
	auto testByName = [&] (const std::shared_ptr<tester::base::Test> & t) {
		return (testName.compare(t->getName()) == 0);
	};
	auto testIt = std::find_if(this->tests.cbegin(), this->tests.cend(), testByName);
	auto testFound = (testIt != this->tests.cend());

	std::shared_ptr<tester::base::Test> test = nullptr;

	if (testFound == true) {
		test = *testIt;
	}

	return test;
}

void tester::base::Suite::populate() {

}

void tester::base::Suite::postProcessCreation() {
	this->getFactory()->addSuite(this->shared_from_this());
	this->populate();
}
