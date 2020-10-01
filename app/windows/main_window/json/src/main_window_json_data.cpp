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

std::shared_ptr<main_window_json_data::MainWindowJsonData> main_window_json_data::MainWindowJsonData::makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue) {
	std::shared_ptr<main_window_json_data::MainWindowJsonData> newData = std::make_shared<main_window_json_data::MainWindowJsonData>(jsonKey, nameKeyValue, stateKeyValue, shortcutKeyValue, longCmdKeyValue, helpKeyValue);
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Creating JSON data: " << *newData);
	return newData;
}

main_window_json_data::MainWindowJsonData::MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const int & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue) : json_data::JsonData(main_window_json_data::MainWindowJsonData::parameter_t(main_window_json_data::keyNames.cbegin(), main_window_json_data::keyNames.cend())), key(jsonKey), name(nameKeyValue), state(stateKeyValue), shortcut(shortcutKeyValue), longCmd(longCmdKeyValue), help(helpKeyValue) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Main window JSON Data constructor. Data " << *this);

}

main_window_json_data::MainWindowJsonData::MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs) : json_data::JsonData(rhs), key(rhs.key), name(rhs.name), state(rhs.state), shortcut(rhs.shortcut), longCmd(rhs.longCmd), help(rhs.help) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Copy constructor main window JSON data");

}

main_window_json_data::MainWindowJsonData & main_window_json_data::MainWindowJsonData::operator=(const main_window_json_data::MainWindowJsonData & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Copy assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	json_data::JsonData::operator=(rhs);

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

main_window_json_data::MainWindowJsonData::MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs) : json_data::JsonData(rhs), key(std::exchange(rhs.key, std::string())), name(std::exchange(rhs.name, std::string())), state(std::exchange(rhs.state, main_window_shared_types::state_e::IDLE)), shortcut(std::exchange(rhs.shortcut, (int)Qt::Key_unknown)), longCmd(std::exchange(rhs.longCmd, std::string())), help(std::exchange(rhs.help, std::string())) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Move constructor main window JSON data");
}

main_window_json_data::MainWindowJsonData & main_window_json_data::MainWindowJsonData::operator=(main_window_json_data::MainWindowJsonData && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Move assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		json_data::JsonData::operator=(rhs);
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

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "JSON Data structure destructor. Data " << *this);

}

const std::string main_window_json_data::MainWindowJsonData::print() const {
	std::string structInfo;

	structInfo = "\n";
	structInfo = structInfo + json_data::JsonData::print();
	structInfo = structInfo + "Data:\n";
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

CONST_GETTER(main_window_json_data::MainWindowJsonData::getKey, std::string &, this->key)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getName, std::string &, this->name)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getState, main_window_shared_types::state_e &, this->state)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getShortcut, int &, this->shortcut)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getLongCmd, std::string &, this->longCmd)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getHelp, std::string &, this->help)

void main_window_json_data::MainWindowJsonData::setValueFromMemberName(const std::string & name, const void * value) {
	QEXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().end()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void main_window_json_data::MainWindowJsonData::addParameter(const std::string & name)");

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
	QEXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void main_window_json_data::MainWindowJsonData::addParameter(const std::string & name)");

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
	QEXCEPTION_ACTION_COND((this->getParameters().find(name) == this->getParameters().cend()), throw, "Parameter " << name << " has not been found among the action parameters. In order to add it, please call void main_window_json_data::MainWindowJsonData::addParameter(const std::string & name)");

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

bool main_window_json_data::MainWindowJsonData::operator==(const main_window_json_data::MainWindowJsonData & rhs) {
	bool isSame = true;
	isSame &= this->json_data::JsonData::operator==(rhs);
	isSame &= (this->key.compare(rhs.key) == 0);
	isSame &= (this->name.compare(rhs.name) == 0);
	isSame &= (this->state == rhs.state);
	isSame &= (this->shortcut == rhs.shortcut);
	isSame &= (this->longCmd.compare(rhs.longCmd) == 0);
	isSame &= (this->help.compare(rhs.help) == 0);

	return isSame;
}

bool main_window_json_data::MainWindowJsonData::operator!=(const main_window_json_data::MainWindowJsonData & rhs) {
	bool isSame = (*this == rhs);
	return !isSame;
}
