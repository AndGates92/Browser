/**
 * @copyright
 * @file main_window_json_data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window JSON Data functions
 */

// Qt libraries
#include <QtCore/QtGlobal>

// Required by qInfo
#include <QtCore/QtDebug>

#include "qt_operator.h"
#include "main_window_json_data.h"
#include "global_constants.h"
#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowJsonDataOverall, "mainWindowJsonData.overall", MSG_TYPE_LEVEL)

namespace main_window_json_data {
	bool operator==(const main_window_json_data::MainWindowJsonData & lhs, const main_window_json_data::MainWindowJsonData & rhs) {
		bool isSame = true;
		isSame &= (lhs.key.compare(rhs.key) == 0);
		isSame &= (lhs.name.compare(rhs.name) == 0);
		isSame &= (lhs.state == rhs.state);
		isSame &= (lhs.shortcut == rhs.shortcut);
		isSame &= (lhs.longCmd.compare(rhs.longCmd) == 0);
		isSame &= (lhs.help.compare(rhs.help) == 0);

		return isSame;
	}

	bool operator!=(const main_window_json_data::MainWindowJsonData & lhs, const main_window_json_data::MainWindowJsonData & rhs) {
		bool isSame = (lhs == rhs);
		return !isSame;
	}

}

std::shared_ptr<main_window_json_data::MainWindowJsonData> main_window_json_data::MainWindowJsonData::makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue) {
	std::shared_ptr<main_window_json_data::MainWindowJsonData> newData = std::make_shared<main_window_json_data::MainWindowJsonData>(jsonKey, nameKeyValue, stateKeyValue, shortcutKeyValue, longCmdKeyValue, helpKeyValue);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Creating JSON data: " << *newData);
	return newData;
}

main_window_json_data::MainWindowJsonData::MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue): printable_object::PrintableObject(), key(jsonKey), name(nameKeyValue), state(stateKeyValue), shortcut(shortcutKeyValue), longCmd(longCmdKeyValue), help(helpKeyValue) {

	this->actionParameters.insert(main_window_json_data::defaultActionParameters.cbegin(), main_window_json_data::defaultActionParameters.cend());

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "JSON Data structure constructor. Data " << *this);

}

main_window_json_data::MainWindowJsonData::MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs): key(rhs.key), name(rhs.name), state(rhs.state), shortcut(rhs.shortcut), longCmd(rhs.longCmd), help(rhs.help) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Copy constructor main window JSON data");

}

main_window_json_data::MainWindowJsonData & main_window_json_data::MainWindowJsonData::operator=(const main_window_json_data::MainWindowJsonData & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Copy assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

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

main_window_json_data::MainWindowJsonData::MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs): key(std::exchange(rhs.key, std::string())), name(std::exchange(rhs.name, std::string())), state(std::exchange(rhs.state, main_window_shared_types::state_e::IDLE)), shortcut(std::exchange(rhs.shortcut, (int)Qt::Key_unknown)), longCmd(std::exchange(rhs.longCmd, std::string())), help(std::exchange(rhs.help, std::string())) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Move constructor main window JSON data");
}

main_window_json_data::MainWindowJsonData & main_window_json_data::MainWindowJsonData::operator=(main_window_json_data::MainWindowJsonData && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Move assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->key = std::exchange(rhs.key, std::string());
		this->name = std::exchange(rhs.name, std::string());
		this->state = std::exchange(rhs.state, main_window_shared_types::state_e::IDLE);
		this->shortcut = std::exchange(rhs.shortcut, (int)Qt::Key_unknown);
		this->longCmd = std::exchange(rhs.longCmd, std::string());
		this->help = std::exchange(rhs.help, std::string());
	}

	return *this;
}

main_window_json_data::MainWindowJsonData::~MainWindowJsonData() {

}

const std::string main_window_json_data::MainWindowJsonData::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + "- key in the JSON file: " + this->key + "\n";
	structInfo = structInfo + "- name of the action: " + this->name + "\n";
	structInfo = structInfo + "- state the window has to be put into: " + this->state + "\n";
	// In order to get the key of the shortcut, bitwise and with the negation of the modifier mask
	Qt::Key key = (Qt::Key)(this->shortcut & ~global_constants::qmodifierMask);
	// In order to get the modifier of the shortcut, bitwise and with the modifier mask
	Qt::KeyboardModifiers modifier = (Qt::KeyboardModifiers)(this->shortcut & global_constants::qmodifierMask);
	structInfo = structInfo + "- shortcut key for the action: modifier " + global_qfunctions::qEnumToQString(modifier, true).toStdString() + " key " + global_qfunctions::qEnumToQString(key, true).toStdString() + "\n";
	structInfo = structInfo + "- long command for the action: " + this->longCmd + "\n";
	structInfo = structInfo + "- help for the action: " + this->help + "\n";

	return structInfo;
}

CONST_GETTER(main_window_json_data::MainWindowJsonData::getKey, std::string, this->key)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getName, std::string, this->name)
BASE_GETTER(main_window_json_data::MainWindowJsonData::getState, main_window_shared_types::state_e, this->state)
BASE_GETTER(main_window_json_data::MainWindowJsonData::getShortcut, int, this->shortcut)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getLongCmd, std::string, this->longCmd)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getHelp, std::string, this->help)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getActionParameters, auto, this->actionParameters)

void main_window_json_data::MainWindowJsonData::addActionParameters(const std::string & name) {
	this->actionParameters.insert(name);
}

void main_window_json_data::MainWindowJsonData::setValueFromMemberName(const std::string & name, const void * value) {
	QEXCEPTION_ACTION_COND((this->actionParameters.find(name) == this->actionParameters.end()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void main_window_json_data::MainWindowJsonData::addActionParameters(const std::string & name)");

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->key = *strPtr;
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		this->name = *strPtr;
	} else if (name.compare("State") == 0) {
		const main_window_shared_types::state_e * const statePtr(static_cast<const main_window_shared_types::state_e *>(value));
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
		QEXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}
}

const void * main_window_json_data::MainWindowJsonData::getValueFromMemberName(const std::string & name) const {
	QEXCEPTION_ACTION_COND((this->actionParameters.find(name) == this->actionParameters.cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void main_window_json_data::MainWindowJsonData::addActionParameters(const std::string & name)");

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
		QEXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}

	return value;
}

bool main_window_json_data::MainWindowJsonData::isSameFieldValue(const std::string & name, const void * value) const {
	QEXCEPTION_ACTION_COND((this->actionParameters.find(name) == this->actionParameters.cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void main_window_json_data::MainWindowJsonData::addActionParameters(const std::string & name)");

	bool isSame = false;

	if (name.compare("Key") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->key.compare(*strPtr) == 0);
	} else if (name.compare("Name") == 0) {
		const std::string * const strPtr(static_cast<const std::string *>(value));
		isSame = (this->name.compare(*strPtr) == 0);
	} else if (name.compare("State") == 0) {
		const main_window_shared_types::state_e * const statePtr(static_cast<const main_window_shared_types::state_e *>(value));
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
		QEXCEPTION_ACTION(throw, "Cannot find class member associated with parameter " << name << ".");
	}

	return isSame;
}
