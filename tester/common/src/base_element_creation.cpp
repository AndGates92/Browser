/**
 * @copyright
 * @file base_element_creation.cpp
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Base element creation functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>

#include "global_enums.h"
#include "logging_macros.h"

#include "base_element_creation.h"

Q_LOGGING_CATEGORY(baseElementCreationOverall, "baseElementCreation.overall", MSG_TYPE_LEVEL)

base_element_creation::BaseElementCreation::BaseElementCreation() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseElementCreationOverall,  "Base element creation constructor");

}

base_element_creation::BaseElementCreation::~BaseElementCreation() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, baseElementCreationOverall,  "Base element creation destructor");

}
