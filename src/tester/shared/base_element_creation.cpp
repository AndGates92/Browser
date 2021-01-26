/**
 * @copyright
 * @file base_element_creation.cpp
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Base element creation functions
 */

#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"

#include "tester/shared/base_element_creation.h"

LOGGING_CONTEXT(baseElementCreationOverall, baseElementCreation.overall, TYPE_LEVEL, INFO_VERBOSITY)

tester::shared::BaseElementCreation::BaseElementCreation() {

	LOG_INFO(app::logger::info_level_e::ZERO, baseElementCreationOverall, "Base element creation constructor");

}

tester::shared::BaseElementCreation::~BaseElementCreation() {

	LOG_INFO(app::logger::info_level_e::ZERO, baseElementCreationOverall, "Base element creation destructor");

}
