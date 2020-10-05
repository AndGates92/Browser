/**
 * @copyright
 * @file main_window_json_action.cpp
 * @author Andrea Gianarda
 * @date 09th of October 2020
 * @brief Main Window JSON action class functions
 */

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtWidgets/QShortcut>

#include "qt_operator.h"
#include "global_enums.h"
#include "global_functions.h"
#include "global_qfunctions.h"
#include "logging_macros.h"
#include "main_window_shared_types.h"
#include "main_window_json_action.h"
#include "key_sequence.h"

Q_LOGGING_CATEGORY(mainWindowJsonActionOverall, "mainWindowJsonAction.overall", MSG_TYPE_LEVEL)

main_window_json_action::MainWindowJsonAction::MainWindowJsonAction(const QString & jsonFileName) : json_action::JsonAction<main_window_json_data::MainWindowJsonData>(jsonFileName) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonActionOverall,  "Main window json action classe constructor");

	this->populateActionData();

}

main_window_json_action::MainWindowJsonAction::~MainWindowJsonAction() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowJsonActionOverall,  "Main window json action class destructor");
}

// TODO handle shortcuts with multiple keys
std::string main_window_json_action::MainWindowJsonAction::getShortcutKey(const std::string & value) {
	const std::string delim(",");
	std::string keyName = std::string();
	std::vector<std::string> subStrs = global_functions::splitStringByDelimiter(value, delim);
	auto alphaNum = [&] (unsigned char c) {
		return (std::isalnum(c) != 0);
	};
	auto slashChar = [&] (unsigned char c) {
		return ((std::isgraph(c) != 0) && (c == '/'));
	};

	for (std::string iter : subStrs) {
		bool isAlphaNum = (std::find_if(iter.cbegin(), iter.cend(), alphaNum) != iter.cend());
		bool isSlash = (std::find_if(iter.cbegin(), iter.cend(), slashChar) != iter.cend());
		if (isAlphaNum == true) {
			// Initialize upperKey with as many spaces as the number of characters in iter in order for std::transform to access already allocated space
			std::string upperKey(iter.size(), ' ');
			std::transform(iter.begin(), iter.end(), upperKey.begin(),
				[] (unsigned char c) {
					return std::toupper(c);
				}
			);
			keyName.append("Key_");
			keyName.append(upperKey);
		} else if (isSlash == true) {
			// If string contains only 1 backslash
			keyName.append("Key_Slash");
		} else {
			QEXCEPTION_ACTION(throw,  "Value in JSON file " << value << " is not alphanumeric and lowercase ");
		}
	}

	return keyName;
}

std::string main_window_json_action::MainWindowJsonAction::getShortcutModifier(const std::string & value) {
	const std::string delim(",");
	std::string modifierName("Qt::");
	std::vector<std::string> subStrs = global_functions::splitStringByDelimiter(value, delim);
	auto alphaNumUpper = [&] (unsigned char c) {
		return ((std::isalnum(c) != 0) && (std::isupper(c) != 0));
	};
	for (std::string iter : subStrs) {
		bool isAlphaNumUpperCase = (std::find_if(iter.cbegin(), iter.cend(), alphaNumUpper) != iter.cend());
		if (isAlphaNumUpperCase == true) {
			modifierName.append("ShiftModifier");
		} else {
			modifierName.append("NoModifier");
		}
	}

	return modifierName;
}

void main_window_json_action::MainWindowJsonAction::addItemToActionData(std::unique_ptr<main_window_json_data::MainWindowJsonData> & data, const std::string & key, const std::string & item) {
	void * valuePtr = nullptr;
	main_window_shared_types::state_e state = main_window_shared_types::state_e::IDLE;
	int shortcutKey = (int)Qt::Key_unknown;

	if (key.compare("State") == 0) {
		state = global_qfunctions::qStringToQEnum<main_window_shared_types::state_e>(QString::fromStdString(item));
		QEXCEPTION_ACTION_COND(((int)state == -1), throw, "Unable to match state enumerator for state " << QString::fromStdString(item));
		valuePtr = &state;
	} else if (key.compare("Shortcut") == 0) {
		// Get key
		std::string keyStr(this->getShortcutKey(item));
		Qt::Key key = global_qfunctions::qStringToQEnum<Qt::Key>(QString::fromStdString(keyStr));
		// Get modifier
		std::string modifierStr(this->getShortcutModifier(item));
		Qt::KeyboardModifiers modifier = global_qfunctions::qStringToQEnum<Qt::KeyboardModifiers>(QString::fromStdString(modifierStr));
		shortcutKey = ((int)key) | ((int)modifier);
		valuePtr = &shortcutKey;
	} else {
		valuePtr = &const_cast<std::string &>(item);
	}

	data->setValueFromMemberName(key, valuePtr);
}


