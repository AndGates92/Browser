/**
 * @copyright
 * @file data.cpp
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief JSON Data functions
 */

#include "app/shared/constants.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/shared/exception.h"
#include "app/shared/constructor_macros.h"
#include "app/base/json/data.h"

// Categories
LOGGING_CONTEXT(jsonDataOverall, jsonData.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::json::Data::Data(const app::base::json::Data::parameter_t & jsonParameters) : app::printable_object::PrintableObject(), parameters(jsonParameters) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonDataOverall,  "JSON Data constructor. Data " << *this);

}

app::base::json::Data::Data(const app::base::json::Data & rhs): parameters(rhs.parameters) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonDataOverall,  "Copy constructor JSON data");

}

app::base::json::Data & app::base::json::Data::operator=(const app::base::json::Data & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonDataOverall,  "Copy assignment operator for JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->parameters != rhs.parameters) {
		this->parameters = rhs.parameters;
	}

	return *this;

}

app::base::json::Data::Data(app::base::json::Data && rhs): parameters(std::exchange(rhs.parameters, app::base::json::Data::parameter_t())) {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonDataOverall,  "Move constructor JSON data");
}

app::base::json::Data & app::base::json::Data::operator=(app::base::json::Data && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonDataOverall,  "Move assignment operator for JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->parameters = std::exchange(rhs.parameters, app::base::json::Data::parameter_t());
	}

	return *this;
}

app::base::json::Data::~Data() {

	LOG_INFO(app::logger::info_level_e::ZERO, jsonDataOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string app::base::json::Data::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + "JSON Parameters:\n";
	for (const auto & p : this->parameters) {
		structInfo = structInfo + "- " + p + "\n";
	}

	return structInfo;
}

CONST_GETTER(app::base::json::Data::getParameters, app::base::json::Data::parameter_t &, this->parameters)

void app::base::json::Data::addParameter(const std::string & name) {
	this->parameters.insert(name);
}

bool app::base::json::Data::operator==(const app::base::json::Data & rhs) {
	bool isSame = true;
	isSame &= (this->parameters == rhs.parameters);

	return isSame;
}

bool app::base::json::Data::operator!=(const app::base::json::Data & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}
