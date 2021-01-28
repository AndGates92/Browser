/**
 * @copyright
 * @file action.cpp
 * @author Andrea Gianarda
 * @date 09th of October 2020
 * @brief Main Window JSON action class functions
 */

// Qt libraries
#include <QtWidgets/QShortcut>

#include "app/shared/enums.h"
#include "app/shared/qt_functions.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/cpp/stl_helper.h"
#include "app/utility/qt/qt_operator.h"
#include "app/utility/logger/macros.h"
#include "app/windows/main_window/shared/shared_types.h"
#include "app/windows/main_window/json/action.h"

LOGGING_CONTEXT(mainWindowActionOverall, mainWindowAction.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::json::Action::Action() : app::main_window::json::Action::Action(std::string()) {

}

app::main_window::json::Action::Action(const std::list<std::string> jsonFiles) : app::base::json::Action<app::main_window::json::Data>() {
	if (jsonFiles.empty() == false) {
		this->appendActionData(jsonFiles);
	}
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowActionOverall, "Main window json action classe constructor with " << this->getActionJsonFilesAsString());
}

app::main_window::json::Action::Action(const std::string jsonFileName) : app::base::json::Action<app::main_window::json::Data>() {
	if (jsonFileName.empty() == false) {
		this->appendActionData(jsonFileName);
	}
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowActionOverall, "Main window json action classe constructor with " << this->getActionJsonFilesAsString());


}

app::main_window::json::Action::~Action() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowActionOverall, "Main window json action class destructor");
}

// TODO handle shortcuts with multiple keys
std::string app::main_window::json::Action::getShortcutKey(const std::string & value) {
	const std::string delim(",");
	std::string keyName = std::string();
	auto subStrs = app::utility::splitStringByDelimiter<std::vector>(value, delim);
	auto alphaNum = [&] (unsigned char c) {
		return (std::isalnum(c) != 0);
	};
	auto slashChar = [&] (unsigned char c) {
		return ((std::isgraph(c) != 0) && (c == '/'));
	};
	auto colonChar = [&] (unsigned char c) {
		return ((std::isgraph(c) != 0) && (c == ':'));
	};

	for (std::string iter : subStrs) {
		bool isAlphaNum = (std::find_if(iter.cbegin(), iter.cend(), alphaNum) != iter.cend());
		bool isSlash = (std::find_if(iter.cbegin(), iter.cend(), slashChar) != iter.cend());
		bool isColon = (std::find_if(iter.cbegin(), iter.cend(), colonChar) != iter.cend());
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
		} else if (isColon == true) {
			keyName.append("Key_Colon");
		} else {
			EXCEPTION_ACTION(throw, "Value in JSON file " << value << " is not alphanumeric and lowercase ");
		}
	}

	return keyName;
}

std::string app::main_window::json::Action::getShortcutModifier(const std::string & value) {
	const std::string delim(",");
	std::string modifierName("Qt::");
	auto subStrs = app::utility::splitStringByDelimiter<std::vector>(value, delim);
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

void app::main_window::json::Action::addItemToActionData(std::unique_ptr<app::main_window::json::Data> & data, const std::string & key, const std::string & item) {
	void * valuePtr = nullptr;
	app::main_window::state_e state = app::main_window::state_e::IDLE;
	int shortcutKey = (int)Qt::Key_unknown;

	if (key.compare("State") == 0) {
		state = app::shared::qStringToQEnum<app::main_window::state_e>(QString::fromStdString(item));
		EXCEPTION_ACTION_COND(((int)state == -1), throw, "Unable to match state enumerator for state " << item);
		valuePtr = &state;
	} else if (key.compare("Shortcut") == 0) {
		// Get key
		std::string keyStr(this->getShortcutKey(item));
		Qt::Key key = app::shared::qStringToQEnum<Qt::Key>(QString::fromStdString(keyStr));
		// Get modifier
		std::string modifierStr(this->getShortcutModifier(item));
		Qt::KeyboardModifiers modifier = app::shared::qStringToQEnum<Qt::KeyboardModifiers>(QString::fromStdString(modifierStr));
		shortcutKey = ((int)key) | ((int)modifier);
		valuePtr = &shortcutKey;
	} else {
		valuePtr = &const_cast<std::string &>(item);
	}

	data->setValueFromMemberName(key, valuePtr);
}


