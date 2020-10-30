/**
 * @copyright
 * @file config.cpp
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Logger config functions
 */

#include <string>

#include "macros.h"
#include "global_enums.h"
#include "global_macros.h"

#include "config.h"

/**
 * @brief log filename
 *
 */
#if !defined(LOGFILE)
	#define LOGFILE browser.log
#endif

// Categories
LOGGING_CONTEXT(loggerConfigOverall, loggerConfig.overall, TYPE_LEVEL, INFO_VERBOSITY)

logger::msg_type_e logger::Config::defaultType = logger::msg_type_e::TYPE_LEVEL;
logger::info_level_e logger::Config::defaultVerbosity = logger::info_level_e::INFO_VERBOSITY;
std::string logger::Config::defaultContextName = "default";
std::string logger::Config::defaultOutputFile = STRINGIFY(LOGFILE);

logger::Config::Config() {

	LOG_INFO(logger::info_level_e::ZERO, loggerConfigOverall,  "Creating logger configuration class with default type " << logger::Config::defaultType << " and default verbosity " << logger::Config::defaultVerbosity);
}

logger::Config::~Config() {
	LOG_INFO(logger::info_level_e::ZERO, loggerConfigOverall,  "Destructor of logger configuration class");
}

const logger::msg_type_e & logger::Config::getDefaultType() {
	return defaultType;
}

const logger::info_level_e & logger::Config::getDefaultVerbosity() {
	return defaultVerbosity;
}

const std::string & logger::Config::getDefaultContextName() {
	return defaultContextName;
}

const std::string & logger::Config::getDefaultOutputFile() {
	return defaultOutputFile;
}
