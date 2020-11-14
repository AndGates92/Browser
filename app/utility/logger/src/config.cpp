/**
 * @copyright
 * @file config.cpp
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Logger config functions
 */

#include <string>

#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "common/include/global_macros.h"

#include "common/include/function_macros.h"
#include "utility/logger/include/config.h"

// Categories
LOGGING_CONTEXT(loggerConfigOverall, loggerConfig.overall, TYPE_LEVEL, INFO_VERBOSITY)

logger::Config::Config() : defaultType(logger::msg_type_e::TYPE_LEVEL), defaultVerbosity(logger::info_level_e::INFO_VERBOSITY), defaultContextName("default") {

}

logger::Config::~Config() {

}

CONST_GETTER(logger::Config::getDefaultType, logger::msg_type_e &, this->defaultType)
CONST_GETTER(logger::Config::getDefaultVerbosity, logger::info_level_e &, this->defaultVerbosity)
CONST_GETTER(logger::Config::getDefaultContextName, std::string &, this->defaultContextName)
