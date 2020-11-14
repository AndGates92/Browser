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

test_factory::TestFactory::TestFactory(int & argc, char** argv, const base_factory::BaseFactory::suite_container_t & testSuites) : base_factory::BaseFactory(argc, argv, testSuites) {

	LOG_INFO(logger::info_level_e::ZERO, testFactoryOverall,  "Test factory constructor");

}

test_factory::TestFactory::~TestFactory() {

	LOG_INFO(logger::info_level_e::ZERO, testFactoryOverall,  "Test factory destructor");

}

void test_factory::TestFactory::populate() {
	command_suite::CommandSuite::create<command_suite::CommandSuite>(this->shared_from_this());
}
