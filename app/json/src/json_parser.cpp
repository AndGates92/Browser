/**
 * @copyright
 * @file json_parser.cpp
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Parser
 */

#include "json_parser.h"
#include "global_macros.h"
#include "global_types.h"

Q_LOGGING_CATEGORY(jsonParserOverall, "jsonParser.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(jsonParserFile, "jsonParser.file", MSG_TYPE_LEVEL)

json_parser::JsonParser::JsonParser(QString fileName, QIODevice::OpenModeFlag openFlags) : json_wrapper::JsonWrapper::JsonWrapper(fileName,openFlags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Creating JSON Wrapper of file " << fileName);

	this->readJson();

}

json_parser::JsonParser::~JsonParser() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, jsonParserOverall,  "Destructor of JsonParser class");

}
