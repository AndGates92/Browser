/**
 * @copyright
 * @file json_action.cpp
 * @author Andrea Gianarda
 * @date 09th of October 2020
 * @brief Main Window JSON action class functions
 */

// Qt libraries
#include <QtWidgets/QShortcut>

#include "utility/qt/include/qt_operator.h"
#include "common/include/global_enums.h"
#include "common/include/global_functions.h"
#include "common/include/global_qfunctions.h"
#include "utility/logger/include/macros.h"
#include "windows/main_window/common/include/shared_types.h"
#include "windows/main_window/json/include/json_action.h"
#include "widgets/commands/include/key_sequence.h"

LOGGING_CONTEXT(mainWindowJsonActionOverall, mainWindowJsonAction.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::JsonAction::JsonAction(const QString & jsonFileName) : json::JsonAction<main_window::JsonData>(jsonFileName) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowJsonActionOverall,  "Main window json action classe constructor");

	this->populateActionData();

}

main_window::JsonAction::~JsonAction() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowJsonActionOverall,  "Main window json action class destructor");
}

// TODO handle shortcuts with multiple keys
std::string main_window::JsonAction::getShortcutKey(const std::string & value) {
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
			EXCEPTION_ACTION(throw,  "Value in JSON file " << value << " is not alphanumeric and lowercase ");
		}
	}

	return keyName;
}

std::string main_window::JsonAction::getShortcutModifier(const std::string & value) {
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

void main_window::JsonAction::addItemToActionData(std::unique_ptr<main_window::JsonData> & data, const std::string & key, const std::string & item) {
	void * valuePtr = nullptr;
	main_window::state_e state = main_window::state_e::IDLE;
	int shortcutKey = (int)Qt::Key_unknown;

	if (key.compare("State") == 0) {
		state = global_qfunctions::qStringToQEnum<main_window::state_e>(QString::fromStdString(item));
		EXCEPTION_ACTION_COND(((int)state == -1), throw, "Unable to match state enumerator for state " << item);
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


