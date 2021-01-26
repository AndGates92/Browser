/**
 * @copyright
 * @file factory.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Base factory functions
 */

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "tester/base/factory.h"

LOGGING_CONTEXT(baseFactoryOverall, baseFactory.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::base::Factory::Factory(int & argc, char** argv, const tester::base::Factory::suite_container_t & testSuites) : argc(argc), argv(argv), suites(testSuites) {
	LOG_INFO(app::logger::info_level_e::ZERO, baseFactoryOverall, "Creating base factory with initial content " << *this);
	for (const auto & suite : this->suites) {
		suite->populate();
	}
}

tester::base::Factory::~Factory() {
	LOG_INFO(app::logger::info_level_e::ZERO, baseFactoryOverall, "Base factory destructor");
}

int & tester::base::Factory::getArgc() {
	return this->argc;
}

char ** tester::base::Factory::getArgv() {
	return this->argv;
}

void tester::base::Factory::addTest(const std::string & suiteName, const std::shared_ptr<tester::base::Test> & test) {
	std::shared_ptr<tester::base::Suite> suite = this->findOrCreateSuite(suiteName);
	this->addTest(suite, test);
}

void tester::base::Factory::addTest(const std::shared_ptr<tester::base::Suite> & suite, const std::shared_ptr<tester::base::Test> & test) {
	suite->addTest(test);
}

std::shared_ptr<tester::base::Suite> tester::base::Factory::findOrCreateSuite(const std::string & suiteName) {
	std::shared_ptr<tester::base::Suite> suite = this->findSuite(suiteName);
	if (suite == nullptr) {
		suite = this->createSuite(suiteName);
		this->addSuite(suite);
	}

	return suite;
}

std::shared_ptr<tester::base::Suite> tester::base::Factory::findSuite(const std::string & suiteName) const {
	auto suiteByName = [&] (const std::shared_ptr<tester::base::Suite> & s) {
		return (suiteName.compare(s->getName()) == 0);
	};
	auto suiteIt = std::find_if(this->suites.cbegin(), this->suites.cend(), suiteByName);
	auto suiteFound = (suiteIt != this->suites.cend());

	std::shared_ptr<tester::base::Suite> suite = nullptr;

	if (suiteFound == true) {
		suite = *suiteIt;
	}

	return suite;
}

std::shared_ptr<tester::base::Suite> tester::base::Factory::createSuite(const std::string & suiteName) {
	std::shared_ptr<tester::base::Suite> suite(new tester::base::Suite(this->shared_from_this(), suiteName));
	suite->populate();
	return suite;
}

void tester::base::Factory::addSuite(const std::shared_ptr<tester::base::Suite> & suite) {
	this->suites.insert(suite);
}

CONST_GETTER(tester::base::Factory::getSuites, tester::base::Factory::suite_container_t &, this->suites)

const std::string tester::base::Factory::print() const {
	std::string factoryInfo;

	if (this->suites.empty() == false) {
		factoryInfo = factoryInfo + " factory suites:\n";
		for (auto s : this->suites) {
			factoryInfo = factoryInfo + " - " + *s + "\n";
		}
	} else {
		factoryInfo = factoryInfo + " empty factory\n";
	}

	return factoryInfo;
}

void tester::base::Factory::populate() {

}

void tester::base::Factory::postProcessCreation() {
	this->populate();
}
