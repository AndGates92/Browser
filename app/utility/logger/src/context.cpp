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

app::logger::Context app::logger::Context::getDefaultContext() {
	app::logger::Context context(app::logger::Config::getInstance()->getDefaultContextName(), std::string(), 0, std::string(), app::logger::Config::getInstance()->getDefaultType(), app::logger::Config::getInstance()->getDefaultVerbosity(), app::settings::Global::getLogFilePath());
	return context;
}

app::logger::Context::Context(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity, const std::string ologfilename) : name(contextName), file(contextFile), line(contextLine), function(contextFunction), logFilename(ologfilename), type(contextType), infoVerbosity(contextInfoVerbosity) {

}

app::logger::Context::Context(const std::string contextName, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity, const std::string ologfilename) : name(contextName), file(std::string()), line(0), function(std::string()), logFilename(ologfilename), type(contextType), infoVerbosity(contextInfoVerbosity) {

}

app::logger::Context::~Context() {

}

CONST_SETTER_GETTER(app::logger::Context::setLogFilename, app::logger::Context::getLogFilename, std::string &, this->logFilename)
CONST_SETTER_GETTER(app::logger::Context::setName, app::logger::Context::getName, std::string &, this->name)
CONST_SETTER_GETTER(app::logger::Context::setType, app::logger::Context::getType, app::logger::msg_type_e &, this->type)
CONST_SETTER_GETTER(app::logger::Context::setInfoVerbosity, app::logger::Context::getInfoVerbosity, app::logger::info_level_e &, this->infoVerbosity)
CONST_GETTER(app::logger::Context::getFile, std::string &, this->file)
CONST_GETTER(app::logger::Context::getLine, int &, this->line)
CONST_GETTER(app::logger::Context::getFunction, std::string &, this->function)
