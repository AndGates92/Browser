/**
 * @copyright
 * @file json_data.cpp
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief JSON Data functions
 */

// Qt libraries
#include <QtCore/QtGlobal>

// Required by qInfo
#include <QtCore/QtDebug>

#include "global_constants.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"
#include "constructor_macros.h"
#include "json_data.h"

// Categories
Q_LOGGING_CATEGORY(jsonDataOverall, "jsonData.overall", MSG_TYPE_LEVEL)

json_data::JsonData::JsonData(const json_data::JsonData::parameter_t jsonParameters) : printable_object::PrintableObject(), parameters(jsonParameters) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, jsonDataOverall,  "JSON Data constructor. Data " << *this);

}

json_data::JsonData::JsonData(const json_data::JsonData & rhs): parameters(rhs.parameters) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, jsonDataOverall,  "Copy constructor JSON data");

}

json_data::JsonData & json_data::JsonData::operator=(const json_data::JsonData & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, jsonDataOverall,  "Copy assignment operator for JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->parameters != rhs.parameters) {
		this->parameters = rhs.parameters;
	}

	return *this;

}

json_data::JsonData::JsonData(json_data::JsonData && rhs): parameters(std::exchange(rhs.parameters, json_data::JsonData::parameter_t())) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, jsonDataOverall,  "Move constructor JSON data");
}

json_data::JsonData & json_data::JsonData::operator=(json_data::JsonData && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, jsonDataOverall,  "Move assignment operator for JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->parameters = std::exchange(rhs.parameters, json_data::JsonData::parameter_t());
	}

	return *this;
}

json_data::JsonData::~JsonData() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, jsonDataOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string json_data::JsonData::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + "JSON Parameters:\n";
	for (const auto & p : this->parameters) {
		structInfo = structInfo + "- " + p + "\n";
	}

	return structInfo;
}

CONST_GETTER(json_data::JsonData::getParameters, json_data::JsonData::parameter_t &, this->parameters)

void json_data::JsonData::addParameter(const std::string & name) {
	this->parameters.insert(name);
}

bool json_data::JsonData::operator==(const json_data::JsonData & rhs) {
	bool isSame = true;
	isSame &= (this->parameters == rhs.parameters);

	return isSame;
}

bool json_data::JsonData::operator!=(const json_data::JsonData & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}
