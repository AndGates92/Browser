/**
 * @copyright
 * @file command_line_argument.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window JSON Data functions
 */

#include "common/include/global_constants.h"
#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "common/include/exception_macros.h"
#include "settings/include/command_line_argument.h"

namespace app {

	namespace command_line {

		namespace argument {

			namespace {
				/**
				 * @brief default action parameters which are the keys of the JSON file
				 *
				 */
				static const std::vector<std::string> keyNames{"Key", "Name", "ShortCmd", "LongCmd", "DefaultValue", "NumberArguments", "Help"};
			}

		}

	}

}

// Categories
LOGGING_CONTEXT(commandLineArgumentOverall, commandLineArgument.overall, TYPE_LEVEL, INFO_VERBOSITY)

std::shared_ptr<app::command_line::Argument> app::command_line::Argument::makeArgument(const std::string & jsonKey, const std::string & nameKeyValue, const std::string & shortCmdKeyValue, const std::string & longCmdKeyValue, const std::string & defaultValueKeyValue, const int & numberOfArgumentsKeyValue, const std::string & helpKeyValue) {
	std::shared_ptr<app::command_line::Argument> newData = std::make_shared<app::command_line::Argument>(jsonKey, nameKeyValue, shortCmdKeyValue, longCmdKeyValue, defaultValueKeyValue, numberOfArgumentsKeyValue, helpKeyValue);
	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "Creating JSON data: " << *newData);
	return newData;
}

app::command_line::Argument::Argument(const std::string & jsonKey, const std::string & nameKeyValue, const std::string & shortCmdKeyValue, const std::string & longCmdKeyValue, const std::string & defaultValueKeyValue, const int & numberOfArgumentsKeyValue, const std::string & helpKeyValue) : app::base::json::Data(app::command_line::Argument::parameter_t(app::command_line::argument::keyNames.cbegin(), app::command_line::argument::keyNames.cend())), key(jsonKey), name(nameKeyValue), shortCmd(shortCmdKeyValue), longCmd(longCmdKeyValue), defaultValue(defaultValueKeyValue), numberOfArguments(numberOfArgumentsKeyValue), help(helpKeyValue) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "Main window JSON Data constructor. Data " << *this);

}

app::command_line::Argument::Argument(const app::command_line::Argument & rhs) : app::base::json::Data(rhs), key(rhs.key), name(rhs.name), shortCmd(rhs.shortCmd), longCmd(rhs.longCmd), defaultValue(rhs.defaultValue), numberOfArguments(rhs.numberOfArguments), help(rhs.help) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "Copy constructor main window JSON data");

}

app::command_line::Argument & app::command_line::Argument::operator=(const app::command_line::Argument & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "Copy assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	app::base::json::Data::operator=(rhs);

	if (this->key.compare(rhs.key) != 0) {
		this->key = rhs.key;
	}
	if (this->name.compare(rhs.name) != 0) {
		this->name = rhs.name;
	}
	if (this->shortCmd.compare(rhs.shortCmd) != 0) {
		this->shortCmd = rhs.shortCmd;
	}
	if (this->longCmd.compare(rhs.longCmd) != 0) {
		this->longCmd = rhs.longCmd;
	}
	if (this->defaultValue.compare(rhs.defaultValue) != 0) {
		this->defaultValue = rhs.defaultValue;
	}
	if (this->numberOfArguments == rhs.numberOfArguments) {
		this->numberOfArguments = rhs.numberOfArguments;
	}
	if (this->help.compare(rhs.help) != 0) {
		this->help = rhs.help;
	}

	return *this;

}

app::command_line::Argument::Argument(app::command_line::Argument && rhs) : app::base::json::Data(std::move(rhs)), key(std::exchange(rhs.key, std::string())), name(std::exchange(rhs.name, std::string())), shortCmd(std::exchange(rhs.shortCmd, std::string())), longCmd(std::exchange(rhs.longCmd, std::string())), defaultValue(std::exchange(rhs.defaultValue, std::string())), numberOfArguments(std::exchange(rhs.numberOfArguments, -1)), help(std::exchange(rhs.help, std::string())) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "Move constructor main window JSON data");
}

app::command_line::Argument & app::command_line::Argument::operator=(app::command_line::Argument && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "Move assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		app::base::json::Data::operator=(std::move(rhs));
		this->key = std::exchange(rhs.key, std::string());
		this->name = std::exchange(rhs.name, std::string());
		this->shortCmd = std::exchange(rhs.shortCmd, std::string());
		this->longCmd = std::exchange(rhs.longCmd, std::string());
		this->defaultValue = std::exchange(rhs.defaultValue, std::string());
		this->numberOfArguments = std::exchange(rhs.numberOfArguments, -1);
		this->help = std::exchange(rhs.help, std::string());
	}

	return *this;
}

app::command_line::Argument::~Argument() {

	LOG_INFO(app::logger::info_level_e::ZERO, commandLineArgumentOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string app::command_line::Argument::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + app::base::json::Data::print();
	structInfo = structInfo + "- key in the JSON file: " + this->key + "\n";
	structInfo = structInfo + "- name of the action: " + this->name + "\n";
	structInfo = structInfo + "- short command of the action: " + this->shortCmd + "\n";
	structInfo = structInfo + "- long command of the action: " + this->longCmd + "\n";
	structInfo = structInfo + "- default argument of the action: " + this->defaultValue + "\n";
	structInfo = structInfo + "- number of arguments of the action: " + std::to_string(this->numberOfArguments) + "\n";
	structInfo = structInfo + "- help for the action: " + this->help + "\n";

	return structInfo;
}

CONST_GETTER(app::command_line::Argument::getKey, std::string &, this->key)
CONST_GETTER(app::command_line::Argument::getName, std::string &, this->name)
CONST_GETTER(app::command_line::Argument::getShortCmd, std::string &, this->shortCmd)
CONST_GETTER(app::command_line::Argument::getLongCmd, std::string &, this->longCmd)
CONST_GETTER(app::command_line::Argument::getDefaultValue, std::string &, this->defaultValue)
CONST_GETTER(app::command_line::Argument::getNumberOfArguments, int &, this->numberOfArguments)
CONST_GETTER(app::command_line::Argument::getHelp, std::string &, this->help)

void app::command_line::Argument::setValueFromMemberName(const std::string & name, const void * value) {
	EXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().end()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void app::command_line::Argument::addParameter(const std::string & name)");

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->key = *strPtr;
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->name = *strPtr;
	} else if (name.compare("ShortCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->shortCmd = *strPtr;
	} else if (name.compare("LongCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->longCmd = *strPtr;
	} else if (name.compare("DefaultValue") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->defaultValue = *strPtr;
	} else if (name.compare("NumberArguments") == 0) {
		const int * const intPtr(static_cast<const int *>(value));
		this->numberOfArguments = *intPtr;
	} else if (name.compare("Help") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->help = *strPtr;
	} else {
		EXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}
}

const void * app::command_line::Argument::getValueFromMemberName(const std::string & name) const {
	EXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void app::command_line::Argument::addParameter(const std::string & name)");

	const void * value = nullptr;

	if (name.compare("Key") == 0) {
		value = &(this->key);
	} else if (name.compare("Name") == 0) {
		value = &(this->name);
	} else if (name.compare("ShortCmd") == 0) {
		value = &(this->shortCmd);
	} else if (name.compare("LongCmd") == 0) {
		value = &(this->longCmd);
	} else if (name.compare("DefaultValue") == 0) {
		value = &(this->defaultValue);
	} else if (name.compare("NumberArguments") == 0) {
		value = &(this->numberOfArguments);
	} else if (name.compare("Help") == 0) {
		value = &(this->help);
	} else {
		EXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}

	return value;
}

bool app::command_line::Argument::isSameFieldValue(const std::string & name, const void * value) const {
	EXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void app::command_line::Argument::addParameter(const std::string & name)");

	bool isSame = false;

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->key.compare(*strPtr) == 0);
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->name.compare(*strPtr) == 0);
	} else if (name.compare("ShortCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->shortCmd.compare(*strPtr) == 0);
	} else if (name.compare("LongCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->longCmd.compare(*strPtr) == 0);
	} else if (name.compare("DefaultValue") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->defaultValue.compare(*strPtr) == 0);
	} else if (name.compare("NumberArguments") == 0) {
		const int * const intPtr(static_cast<const int *>(value));
		isSame = (this->numberOfArguments == *intPtr);
	} else if (name.compare("Help") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->help.compare(*strPtr) == 0);
	} else {
		EXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}

	return isSame;
}

bool app::command_line::Argument::operator==(const app::command_line::Argument & rhs) {
	bool isSame = true;
	isSame &= app::base::json::Data::operator==(rhs);
	isSame &= (this->key.compare(rhs.key) == 0);
	isSame &= (this->name.compare(rhs.name) == 0);
	isSame &= (this->shortCmd.compare(rhs.shortCmd) == 0);
	isSame &= (this->longCmd.compare(rhs.longCmd) == 0);
	isSame &= (this->defaultValue.compare(rhs.defaultValue) == 0);
	isSame &= (this->numberOfArguments == rhs.numberOfArguments);
	isSame &= (this->help.compare(rhs.help) == 0);

	return isSame;
}

bool app::command_line::Argument::operator!=(const app::command_line::Argument & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}
