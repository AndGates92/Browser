/**
 * @copyright
 * @file test_factory.cpp
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Test factory functions
 */

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "tester/factories/test_factory.h"
#include "tester/suites/command_suite.h"

LOGGING_CONTEXT(testFactoryOverall, testFactory.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::factory::TestFactory::TestFactory(int & argc, char** argv, const tester::base::Factory::suite_container_t & testSuites) : tester::base::Factory(argc, argv, testSuites) {

	LOG_INFO(app::logger::info_level_e::ZERO, testFactoryOverall, "Test factory constructor");

}

tester::factory::TestFactory::~TestFactory() {

	LOG_INFO(app::logger::info_level_e::ZERO, testFactoryOverall, "Test factory destructor");

}

void tester::factory::TestFactory::populate() {
	tester::suite::CommandSuite::create<tester::suite::CommandSuite>(this->shared_from_this());
}
