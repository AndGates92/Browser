/**
 * @copyright
 * @file main_window_json_data.cpp
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window JSON Data functions
 */

// Qt libraries
#include <qt5/QtCore/QtGlobal>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include "main_window_json_data.h"
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

main_window_json_data::MainWindowJsonData * main_window_json_data::MainWindowJsonData::makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const key_sequence::KeySequence & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue) {
	main_window_json_data::MainWindowJsonData * newData = new main_window_json_data::MainWindowJsonData(jsonKey, nameKeyValue, stateKeyValue, shortcutKeyValue, longCmdKeyValue, helpKeyValue);
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Creating JSON data: " << newData->qprint());
	return newData;
}

main_window_json_data::MainWindowJsonData::MainWindowJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const main_window_shared_types::state_e & stateKeyValue, const key_sequence::KeySequence & shortcutKeyValue, const std::string & longCmdKeyValue, const std::string & helpKeyValue): key(jsonKey), name(nameKeyValue), state(stateKeyValue), shortcut(shortcutKeyValue), longCmd(longCmdKeyValue), help(helpKeyValue) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "JSON Data structure constructor. Data " << this->qprint());

}

main_window_json_data::MainWindowJsonData::MainWindowJsonData(const main_window_json_data::MainWindowJsonData & rhs): key(rhs.key), name(rhs.name), state(rhs.state), shortcut(rhs.shortcut), longCmd(rhs.longCmd), help(rhs.help) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Copy constructor main window JSON data");

}

main_window_json_data::MainWindowJsonData & main_window_json_data::MainWindowJsonData::operator=(const main_window_json_data::MainWindowJsonData & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Copy assignment operator for main window JSON data");

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

main_window_json_data::MainWindowJsonData::MainWindowJsonData(main_window_json_data::MainWindowJsonData && rhs): key(std::exchange(rhs.key, std::string())), name(std::exchange(rhs.name, std::string())), state(std::exchange(rhs.state, main_window_shared_types::state_e::IDLE)), shortcut(std::exchange(rhs.shortcut, key_sequence::KeySequence(QKeySequence::UnknownKey))), longCmd(std::exchange(rhs.longCmd, std::string())), help(std::exchange(rhs.help, std::string())) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Move constructor main window JSON data");
}

main_window_json_data::MainWindowJsonData & main_window_json_data::MainWindowJsonData::operator=(main_window_json_data::MainWindowJsonData && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowJsonDataOverall,  "Move assignment operator for main window JSON data");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->key = std::exchange(rhs.key, std::string());
		this->name = std::exchange(rhs.name, std::string());
		this->state = std::exchange(rhs.state, main_window_shared_types::state_e::IDLE);
		this->shortcut = std::exchange(rhs.shortcut, key_sequence::KeySequence(QKeySequence::UnknownKey));
		this->longCmd = std::exchange(rhs.longCmd, std::string());
		this->help = std::exchange(rhs.help, std::string());
	}

	return *this;
}

main_window_json_data::MainWindowJsonData::~MainWindowJsonData() {

}

const QString main_window_json_data::MainWindowJsonData::qprint() const {
	const std::string mainWindowJsonDataInfo(this->print());
	const QString qStr(QString::fromStdString(mainWindowJsonDataInfo));

	return qStr;
}

std::string main_window_json_data::MainWindowJsonData::print() const {
	std::string structInfo;

	structInfo = structInfo + "key in the JSON file: " + this->key + "\n";
	structInfo = structInfo + "name of the action: " + this->name + "\n";
	structInfo = structInfo + "state the window has to be put into: " + this->state + "\n";
	structInfo = structInfo + "shortcut for the action: " + this->shortcut.toStdString() + "\n";
	structInfo = structInfo + "long command for the action: " + this->longCmd + "\n";
	structInfo = structInfo + "help for the action: " + this->help + "\n";

	return structInfo;
}

CONST_GETTER(main_window_json_data::MainWindowJsonData::getKey, std::string, this->key)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getName, std::string, this->name)
BASE_GETTER(main_window_json_data::MainWindowJsonData::getState, main_window_shared_types::state_e, this->state)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getShortcut, key_sequence::KeySequence, this->shortcut)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getLongCmd, std::string, this->longCmd)
CONST_GETTER(main_window_json_data::MainWindowJsonData::getHelp, std::string, this->help)
