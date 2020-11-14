/**
 * @copyright
 * @file base_element_creation.cpp
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Base element creation functions
 */

#include "common/include/global_enums.h"
#include "utility/logger/include/macros.h"

#include "common/include/base_element_creation.h"

LOGGING_CONTEXT(baseElementCreationOverall, baseElementCreation.overall, TYPE_LEVEL, INFO_VERBOSITY)

base_element_creation::BaseElementCreation::BaseElementCreation() {

	LOG_INFO(logger::info_level_e::ZERO, baseElementCreationOverall,  "Base element creation constructor");

}

base_element_creation::BaseElementCreation::~BaseElementCreation() {

	LOG_INFO(logger::info_level_e::ZERO, baseElementCreationOverall,  "Base element creation destructor");

}
