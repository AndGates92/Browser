/**
 * @copyright
 * @file context.cpp
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Logger context functions
 */

#include <string>

#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"

#include "utility/logger/include/config.h"
#include "utility/logger/include/context.h"

logger::Context logger::Context::getDefaultContext() {
	logger::Context context(logger::Config::getInstance()->getDefaultContextName(), std::string(), 0, std::string(), logger::Config::getInstance()->getDefaultType(), logger::Config::getInstance()->getDefaultVerbosity(), settings::BrowserSettings::getLogFilePath());
	return context;
}

logger::Context::Context(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const logger::msg_type_e contextType, const logger::info_level_e contextInfoVerbosity, const std::string ologfilename) : name(contextName), file(contextFile), line(contextLine), function(contextFunction), logFilename(ologfilename), type(contextType), infoVerbosity(contextInfoVerbosity) {

}

logger::Context::Context(const std::string contextName, const logger::msg_type_e contextType, const logger::info_level_e contextInfoVerbosity, const std::string ologfilename) : name(contextName), file(std::string()), line(0), function(std::string()), logFilename(ologfilename), type(contextType), infoVerbosity(contextInfoVerbosity) {

}

logger::Context::~Context() {

}

CONST_SETTER_GETTER(logger::Context::setLogFilename, logger::Context::getLogFilename, std::string &, this->logFilename)
CONST_SETTER_GETTER(logger::Context::setName, logger::Context::getName, std::string &, this->name)
CONST_SETTER_GETTER(logger::Context::setType, logger::Context::getType, logger::msg_type_e &, this->type)
CONST_SETTER_GETTER(logger::Context::setInfoVerbosity, logger::Context::getInfoVerbosity, logger::info_level_e &, this->infoVerbosity)
CONST_GETTER(logger::Context::getFile, std::string &, this->file)
CONST_GETTER(logger::Context::getLine, int &, this->line)
CONST_GETTER(logger::Context::getFunction, std::string &, this->function)
