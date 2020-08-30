/**
 * @copyright
 * @file sanity_suite.cpp
 * @author Andrea Gianarda
 * @date 27th August 2020
 * @brief Sanity suite functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include "logging_macros.h"
#include "sanity_suite.h"
#include "launch_app.h"

Q_LOGGING_CATEGORY(sanitySuiteOverall, "sanitySuite.overall", MSG_TYPE_LEVEL)

sanity_suite::SanitySuite::SanitySuite(const std::shared_ptr<base_factory::BaseFactory> testFactory, const base_suite::BaseSuite::tests_container_t & testList) : base_suite::BaseSuite(testFactory, "Sanity suite", testList) {

}

sanity_suite::SanitySuite::~SanitySuite() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, sanitySuiteOverall,  "Sanity suite destructor");

}

void sanity_suite::SanitySuite::populate() {
	launch_app::LaunchApp::create<launch_app::LaunchApp>(this->shared_from_this());
}
