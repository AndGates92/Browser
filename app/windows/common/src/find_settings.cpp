/**
 * @copyright
 * @file find_settings.cpp
 * @author Andrea Gianarda
 * @date 3rd of August 2020
 * @brief Find Settings functions
 */

#include <string>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include "logging_macros.h"
#include "find_settings.h"
#include "function_macros.h"

// Categories
Q_LOGGING_CATEGORY(findSettingsOverall, "findSettings.overall", MSG_TYPE_LEVEL)

find_settings::FindSettings::FindSettings(const QString & initText, const global_enums::offset_type_e & initDirection, const bool & initCaseSensitive, const bool & initMatchFullWord) : printable_object::PrintableObject(), text(initText), direction(initDirection), caseSensitive(initCaseSensitive), matchFullWord(initMatchFullWord) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findSettingsOverall,  "Creating find button window");

}

find_settings::FindSettings::FindSettings(const find_settings::FindSettings & rhs) : text(rhs.text), direction(rhs.direction), caseSensitive(rhs.caseSensitive), matchFullWord(rhs.matchFullWord) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findSettingsOverall,  "Copy constructor find settings");

}

find_settings::FindSettings & find_settings::FindSettings::operator=(const find_settings::FindSettings & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findSettingsOverall,  "Copy assignment operator for find settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->direction != rhs.direction) {
		this->direction = rhs.direction;
	}

	if (this->caseSensitive != rhs.caseSensitive) {
		this->caseSensitive = rhs.caseSensitive;
	}

	if (this->matchFullWord != rhs.matchFullWord) {
		this->matchFullWord = rhs.matchFullWord;
	}

	if (this->text != rhs.text) {
		this->text = rhs.text;
	}

	return *this;
}

find_settings::FindSettings::FindSettings(find_settings::FindSettings && rhs) : text(std::exchange(rhs.text, QString())), direction(std::exchange(rhs.direction, global_enums::offset_type_e::IDLE)), caseSensitive(std::exchange(rhs.caseSensitive, false)), matchFullWord(std::exchange(rhs.matchFullWord, false)) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findSettingsOverall,  "Move constructor find settings");
}

find_settings::FindSettings & find_settings::FindSettings::operator=(find_settings::FindSettings && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findSettingsOverall,  "Move assignment operator for find settings");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->direction = std::exchange(rhs.direction, global_enums::offset_type_e::IDLE);
		this->caseSensitive = std::exchange(rhs.caseSensitive, false);
		this->matchFullWord = std::exchange(rhs.matchFullWord, false);
		this->text = std::exchange(rhs.text, QString());
	}

	return *this;
}

find_settings::FindSettings::~FindSettings() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, findSettingsOverall,  "Destructor of FindSettings class");
}

const std::string find_settings::FindSettings::print() const {
	std::string settings;

	settings = settings + " text: " + this->text.toStdString();
	settings = settings + " case sensitive: " + std::to_string((int)this->caseSensitive);
	settings = settings + " match full word: " + std::to_string((int)this->matchFullWord);
	settings = settings + " direction: " + this->direction;

	return settings;
}

CONST_REF_SETTER(find_settings::FindSettings::setDirection, global_enums::offset_type_e, this->direction)
BASE_GETTER(find_settings::FindSettings::getDirection, global_enums::offset_type_e, this->direction)
CONST_REF_SETTER(find_settings::FindSettings::setCaseSensitive, bool, this->caseSensitive)
BASE_GETTER(find_settings::FindSettings::getCaseSensitive, bool, this->caseSensitive)
CONST_REF_SETTER(find_settings::FindSettings::setMatchFullWord, bool, this->matchFullWord)
BASE_GETTER(find_settings::FindSettings::getMatchFullWord, bool, this->matchFullWord)
CONST_REF_SETTER_GETTER(find_settings::FindSettings::setText, find_settings::FindSettings::getText, QString, this->text)
