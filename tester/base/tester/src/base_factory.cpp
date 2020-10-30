/**
 * @copyright
 * @file base_factory.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Base factory functions
 */

#include "global_enums.h"
#include "macros.h"
#include "function_macros.h"
#include "base_factory.h"

LOGGING_CONTEXT(baseFactoryOverall, baseFactory.overall, TYPE_LEVEL, INFO_VERBOSITY)

base_factory::BaseFactory::BaseFactory(int & argc, char** argv, const base_factory::BaseFactory::suite_container_t & testSuites) : argc(argc), argv(argv), suites(testSuites) {
	LOG_INFO(logger::info_level_e::ZERO, baseFactoryOverall,  "Creating base factory with initial content " << *this);
	for (const auto & suite : this->suites) {
		suite->populate();
	}
}

base_factory::BaseFactory::~BaseFactory() {
	LOG_INFO(logger::info_level_e::ZERO, baseFactoryOverall,  "Base factory destructor");
}

int & base_factory::BaseFactory::getArgc() {
	return this->argc;
}

char ** base_factory::BaseFactory::getArgv() {
	return this->argv;
}

void base_factory::BaseFactory::addTest(const std::string & suiteName, const std::shared_ptr<base_test::BaseTest> & test) {
	std::shared_ptr<base_suite::BaseSuite> suite = this->findOrCreateSuite(suiteName);
	this->addTest(suite, test);
}

void base_factory::BaseFactory::addTest(const std::shared_ptr<base_suite::BaseSuite> & suite, const std::shared_ptr<base_test::BaseTest> & test) {
	suite->addTest(test);
}

std::shared_ptr<base_suite::BaseSuite> base_factory::BaseFactory::findOrCreateSuite(const std::string & suiteName) {
	std::shared_ptr<base_suite::BaseSuite> suite = this->findSuite(suiteName);
	if (suite == nullptr) {
		suite = this->createSuite(suiteName);
		this->addSuite(suite);
	}

	return suite;
}

std::shared_ptr<base_suite::BaseSuite> base_factory::BaseFactory::findSuite(const std::string & suiteName) const {
	auto suiteByName = [&] (const std::shared_ptr<base_suite::BaseSuite> & s) {
		return (suiteName.compare(s->getName()) == 0);
	};
	auto suiteIt = std::find_if(this->suites.cbegin(), this->suites.cend(), suiteByName);
	auto suiteFound = (suiteIt != this->suites.cend());

	std::shared_ptr<base_suite::BaseSuite> suite = nullptr;

	if (suiteFound == true) {
		suite = *suiteIt;
	}

	return suite;
}

std::shared_ptr<base_suite::BaseSuite> base_factory::BaseFactory::createSuite(const std::string & suiteName) {
	std::shared_ptr<base_suite::BaseSuite> suite(new base_suite::BaseSuite(this->shared_from_this(), suiteName));
	suite->populate();
	return suite;
}

void base_factory::BaseFactory::addSuite(const std::shared_ptr<base_suite::BaseSuite> & suite) {
	this->suites.insert(suite);
}

CONST_GETTER(base_factory::BaseFactory::getSuites, base_factory::BaseFactory::suite_container_t &, this->suites)

const std::string base_factory::BaseFactory::print() const {
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

void base_factory::BaseFactory::populate() {

}

void base_factory::BaseFactory::postProcessCreation() {
	this->populate();
}
