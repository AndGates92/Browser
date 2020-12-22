/**
 * @copyright
 * @file data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window JSON Data functions
 */

#include "app/utility/logger/macros.h"
#include "app/utility/qt/qt_operator.h"
#include "app/shared/constants.h"
#include "app/shared/setters_getters.h"
#include "app/shared/exception.h"
#include "app/windows/main_window/json/data.h"

// Categories
LOGGING_CONTEXT(mainWindowDataOverall, mainWindowData.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace json {

			namespace data {

				namespace {
					/**
					 * @brief default action parameters which are the keys of the JSON file
					 *
					 */
					static const std::vector<std::string> keyNames{"Key", "Name", "State", "Shortcut", "LongCmd", "Help"};
				}

			}

		}

	}

}


std::shared_ptr<app::main_window::json::Data> app::main_window::json::Data::makeData(const std::string & jsonKey, const std::string & nameKeyValue, const app::main_window::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue) {
	std::shared_ptr<app::main_window::json::Data> newData = std::make_shared<app::main_window::json::Data>(jsonKey, nameKeyValue, stateKeyValue, shortcutKeyValue, longCmdKeyValue, helpKeyValue);
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "Creating JSON data: " << *newData);
	return newData;
}

app::main_window::json::Data::Data(const std::string & jsonKey, const std::string & nameKeyValue, const app::main_window::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue) : app::base::json::Data(app::main_window::json::Data::parameter_t(app::main_window::json::data::keyNames.cbegin(), app::main_window::json::data::keyNames.cend())), key(jsonKey), name(nameKeyValue), state(stateKeyValue), shortcut(shortcutKeyValue), longCmd(longCmdKeyValue), help(helpKeyValue) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "Main window JSON Data constructor. Data " << *this);

}

app::main_window::json::Data::Data(const app::main_window::json::Data & rhs) : app::base::json::Data(rhs), key(rhs.key), name(rhs.name), state(rhs.state), shortcut(rhs.shortcut), longCmd(rhs.longCmd), help(rhs.help) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "Copy constructor main window JSON data");

}

app::main_window::json::Data & app::main_window::json::Data::operator=(const app::main_window::json::Data & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "Copy assignment operator for main window JSON data");

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
	if (this->state != rhs.state) {
		this->state = rhs.state;
	}
	if (this->shortcut != rhs.shortcut) {
		this->shortcut = rhs.shortcut;
	}
	if (this->longCmd.compare(rhs.longCmd) != 0) {
		this->longCmd = rhs.longCmd;
	}
	if (this->help.compare(rhs.help) != 0) {
		this->help = rhs.help;
	}

	return *this;

}

app::main_window::json::Data::Data(app::main_window::json::Data && rhs) : app::base::json::Data(std::move(rhs)), key(std::exchange(rhs.key, std::string())), name(std::exchange(rhs.name, std::string())), state(std::exchange(rhs.state, app::main_window::state_e::IDLE)), shortcut(std::exchange(rhs.shortcut, (int)Qt::Key_unknown)), longCmd(std::exchange(rhs.longCmd, std::string())), help(std::exchange(rhs.help, std::string())) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "Move constructor main window JSON data");
}

app::main_window::json::Data & app::main_window::json::Data::operator=(app::main_window::json::Data && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "Move assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		app::base::json::Data::operator=(std::move(rhs));
		this->key = std::exchange(rhs.key, std::string());
		this->name = std::exchange(rhs.name, std::string());
		this->state = std::exchange(rhs.state, app::main_window::state_e::IDLE);
		this->shortcut = std::exchange(rhs.shortcut, (int)Qt::Key_unknown);
		this->longCmd = std::exchange(rhs.longCmd, std::string());
		this->help = std::exchange(rhs.help, std::string());
	}

	return *this;
}

app::main_window::json::Data::~Data() {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowDataOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string app::main_window::json::Data::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + app::base::json::Data::print();
	structInfo = structInfo + "Data:\n";
	structInfo = structInfo + "- key in the JSON file: " + this->key + "\n";
	structInfo = structInfo + "- name of the action: " + this->name + "\n";
	structInfo = structInfo + "- state the window has to be put into: " + this->state + "\n";
	// In order to get the key of the shortcut, bitwise and with the negation of the modifier mask
	Qt::Key key = (Qt::Key)(this->shortcut & ~app::shared::qmodifierMask);
	// In order to get the modifier of the shortcut, bitwise and with the modifier mask
	Qt::KeyboardModifiers modifier = (Qt::KeyboardModifiers)(this->shortcut & app::shared::qmodifierMask);
	structInfo = structInfo + "- shortcut key for the action: modifier " + app::shared::qEnumToQString(modifier, true).toStdString() + " key " + app::shared::qEnumToQString(key, true).toStdString() + "\n";
	structInfo = structInfo + "- long command for the action: " + this->longCmd + "\n";
	structInfo = structInfo + "- help for the action: " + this->help + "\n";

	return structInfo;
}

CONST_GETTER(app::main_window::json::Data::getKey, std::string &, this->key)
CONST_GETTER(app::main_window::json::Data::getName, std::string &, this->name)
CONST_GETTER(app::main_window::json::Data::getState, app::main_window::state_e &, this->state)
CONST_GETTER(app::main_window::json::Data::getShortcut, int &, this->shortcut)
CONST_GETTER(app::main_window::json::Data::getLongCmd, std::string &, this->longCmd)
CONST_GETTER(app::main_window::json::Data::getHelp, std::string &, this->help)

void app::main_window::json::Data::setValueFromMemberName(const std::string & name, const void * value) {
	EXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().end()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void app::main_window::json::Data::addParameter(const std::string & name)");

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->key = *strPtr;
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->name = *strPtr;
	} else if (name.compare("State") == 0) {
		const app::main_window::state_e * const statePtr(static_cast<const app::main_window::state_e *>(value));
		this->state = *statePtr;
	} else if (name.compare("Shortcut") == 0) {
		const int * const shortcutKeyPtr(static_cast<const int *>(value));
		this->shortcut = *shortcutKeyPtr;
	} else if (name.compare("LongCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->longCmd = *strPtr;
	} else if (name.compare("Help") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->help = *strPtr;
	} else {
		EXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}
}

const void * app::main_window::json::Data::getValueFromMemberName(const std::string & name) const {
	EXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void app::main_window::json::Data::addParameter(const std::string & name)");

	const void * value = nullptr;

	if (name.compare("Key") == 0) {
		value = &(this->key);
	} else if (name.compare("Name") == 0) {
		value = &(this->name);
	} else if (name.compare("State") == 0) {
		value = &(this->state);
	} else if (name.compare("Shortcut") == 0) {
		value = &(this->shortcut);
	} else if (name.compare("LongCmd") == 0) {
		value = &(this->longCmd);
	} else if (name.compare("Help") == 0) {
		value = &(this->help);
	} else {
		EXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}

	return value;
}

bool app::main_window::json::Data::isSameFieldValue(const std::string & name, const void * value) const {
	EXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void app::main_window::json::Data::addParameter(const std::string & name)");

	bool isSame = false;

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->key.compare(*strPtr) == 0);
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->name.compare(*strPtr) == 0);
	} else if (name.compare("State") == 0) {
		const app::main_window::state_e * const statePtr(static_cast<const app::main_window::state_e *>(value));
		isSame = (this->state == *statePtr);
	} else if (name.compare("Shortcut") == 0) {
		const int * const shortcutKeyPtr(static_cast<const int *>(value));
		isSame = (this->shortcut == *shortcutKeyPtr);
	} else if (name.compare("LongCmd") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->longCmd.compare(*strPtr) == 0);
	} else if (name.compare("Help") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->help.compare(*strPtr) == 0);
	} else {
		EXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}

	return isSame;
}

bool app::main_window::json::Data::operator==(const app::main_window::json::Data & rhs) {
	bool isSame = true;
	isSame &= app::base::json::Data::operator==(rhs);
	isSame &= (this->key.compare(rhs.key) == 0);
	isSame &= (this->name.compare(rhs.name) == 0);
	isSame &= (this->state == rhs.state);
	isSame &= (this->shortcut == rhs.shortcut);
	isSame &= (this->longCmd.compare(rhs.longCmd) == 0);
	isSame &= (this->help.compare(rhs.help) == 0);

	return isSame;
}

bool app::main_window::json::Data::operator!=(const app::main_window::json::Data & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}
