/**
 * @copyright
 * @file test_factory.cpp
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Test factory functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "test_factory.h"
#include "command_suite.h"

Q_LOGGING_CATEGORY(testFactoryOverall, "testFactory.overall", MSG_TYPE_LEVEL)

test_factory::TestFactory::TestFactory(int & argc, char** argv, const base_factory::BaseFactory::suite_container_t & testSuites) : base_factory::BaseFactory(argc, argv, testSuites) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testFactoryOverall,  "Test factory constructor");

}

test_factory::TestFactory::~TestFactory() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, testFactoryOverall,  "Test factory destructor");

}

void test_factory::TestFactory::populate() {
	command_suite::CommandSuite::create<command_suite::CommandSuite>(this->shared_from_this());
}
