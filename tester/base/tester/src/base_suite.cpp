/**
 * @copyright
 * @file base_suite.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Test suite functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "base_suite.h"
#include "base_factory.h"

Q_LOGGING_CATEGORY(baseSuiteOverall, "baseSuite.overall", MSG_TYPE_LEVEL)

bool base_suite::SuitePtrCompare::operator() (const std::shared_ptr<base_suite::BaseSuite> & rhs, const std::shared_ptr<base_suite::BaseSuite> & lhs) const {
	bool isSame = ((*rhs) == (*lhs));
	return isSame;
}

base_suite::BaseSuite::BaseSuite(const std::shared_ptr<base_factory::BaseFactory> & testFactory, const std::string & suiteName, const base_suite::BaseSuite::tests_container_t & testList) : factory(testFactory), name(suiteName), tests(testList) {

	QEXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Cannot create test suite with no name");
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseSuiteOverall,  "Creating " << *this);

}

base_suite::BaseSuite::~BaseSuite() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseSuiteOverall,  "Test suite destructor");

}

const std::shared_ptr<base_factory::BaseFactory> base_suite::BaseSuite::getFactory() const {
	QEXCEPTION_ACTION_COND((this->factory.expired() == true), throw,  "Unable to get factory bar for test " << QString::fromStdString(this->name) << " as it has already expired");
	std::shared_ptr<base_factory::BaseFactory> testFactory = this->factory.lock();
	QEXCEPTION_ACTION_COND((testFactory == nullptr), throw, "Factory is a nullptr - suite " << QString::fromStdString(this->name) << " must have a factory linked to it");

	return testFactory;
}

const std::string & base_suite::BaseSuite::getName() const {
	QEXCEPTION_ACTION_COND((this->name.empty() == true), throw, "Suite cannot have an empty name");
	return this->name;
}

void base_suite::BaseSuite::addTest(const std::shared_ptr<base_test::BaseTest> & test) {
	this->tests.insert(test);
}

CONST_GETTER(base_suite::BaseSuite::getTests, base_suite::BaseSuite::tests_container_t &, this->tests)

const std::string base_suite::BaseSuite::print() const {
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

bool base_suite::BaseSuite::operator== (const base_suite::BaseSuite & otherSuite) const {
	bool nameComparison = (this->getName().compare(otherSuite.getName()) < 0);
	bool factoryComparison = (this->getFactory() == otherSuite.getFactory());

	const base_suite::BaseSuite::tests_container_t & thisTests = this->getTests();
	const base_suite::BaseSuite::tests_container_t & otherTests = otherSuite.getTests();
	base_suite::BaseSuite::tests_container_t::size_type testNumberDifference = (thisTests.size() - otherTests.size());
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

std::shared_ptr<base_test::BaseTest> base_suite::BaseSuite::findTest(const std::string & testName) const {
	auto testByName = [&] (const std::shared_ptr<base_test::BaseTest> & t) {
		return (testName.compare(t->getName()) == 0);
	};
	auto testIt = std::find_if(this->tests.cbegin(), this->tests.cend(), testByName);
	auto testFound = (testIt != this->tests.cend());

	std::shared_ptr<base_test::BaseTest> test = nullptr;

	if (testFound == true) {
		test = *testIt;
	}

	return test;
}

void base_suite::BaseSuite::populate() {

}

void base_suite::BaseSuite::postProcessCreation() {
	this->getFactory()->addSuite(this->shared_from_this());
	this->populate();
}
