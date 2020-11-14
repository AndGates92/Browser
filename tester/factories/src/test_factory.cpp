/**
 * @copyright
 * @file test_factory.cpp
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Test factory functions
 */

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "factories/include/test_factory.h"
#include "suites/include/command_suite.h"

LOGGING_CONTEXT(testFactoryOverall, testFactory.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::factory::TestFactory::TestFactory(int & argc, char** argv, const tester::base::Factory::suite_container_t & testSuites) : tester::base::Factory(argc, argv, testSuites) {

	LOG_INFO(app::logger::info_level_e::ZERO, testFactoryOverall,  "Test factory constructor");

}

tester::factory::TestFactory::~TestFactory() {

	LOG_INFO(app::logger::info_level_e::ZERO, testFactoryOverall,  "Test factory destructor");

}

void tester::factory::TestFactory::populate() {
	tester::suite::CommandSuite::create<tester::suite::CommandSuite>(this->shared_from_this());
}
