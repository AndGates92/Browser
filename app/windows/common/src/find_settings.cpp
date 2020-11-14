/**
 * @copyright
 * @file find_settings.cpp
 * @author Andrea Gianarda
 * @date 3rd of August 2020
 * @brief Find Settings functions
 */

#include <string>

#include "utility/logger/include/macros.h"
#include "windows/common/include/find_settings.h"
#include "common/include/function_macros.h"

// Categories
LOGGING_CONTEXT(findSettingsOverall, findSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::windows::shared::FindSettings::FindSettings(const QString & initText, const app::shared::offset_type_e & initDirection, const bool & initCaseSensitive, const bool & initMatchFullWord) : app::printable_object::PrintableObject(), text(initText), direction(initDirection), caseSensitive(initCaseSensitive), matchFullWord(initMatchFullWord) {

	LOG_INFO(app::logger::info_level_e::ZERO, findSettingsOverall,  "Creating find button window");

}

app::windows::shared::FindSettings::FindSettings(const app::windows::shared::FindSettings & rhs) : text(rhs.text), direction(rhs.direction), caseSensitive(rhs.caseSensitive), matchFullWord(rhs.matchFullWord) {

	LOG_INFO(app::logger::info_level_e::ZERO, findSettingsOverall,  "Copy constructor find settings");

}

app::windows::shared::FindSettings & app::windows::shared::FindSettings::operator=(const app::windows::shared::FindSettings & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, findSettingsOverall,  "Copy assignment operator for find settings");

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

app::windows::shared::FindSettings::FindSettings(app::windows::shared::FindSettings && rhs) : text(std::exchange(rhs.text, QString())), direction(std::exchange(rhs.direction, app::shared::offset_type_e::IDLE)), caseSensitive(std::exchange(rhs.caseSensitive, false)), matchFullWord(std::exchange(rhs.matchFullWord, false)) {

	LOG_INFO(app::logger::info_level_e::ZERO, findSettingsOverall,  "Move constructor find settings");
}

app::windows::shared::FindSettings & app::windows::shared::FindSettings::operator=(app::windows::shared::FindSettings && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, findSettingsOverall,  "Move assignment operator for find settings");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->direction = std::exchange(rhs.direction, app::shared::offset_type_e::IDLE);
		this->caseSensitive = std::exchange(rhs.caseSensitive, false);
		this->matchFullWord = std::exchange(rhs.matchFullWord, false);
		this->text = std::exchange(rhs.text, QString());
	}

	return *this;
}

app::windows::shared::FindSettings::~FindSettings() {
	LOG_INFO(app::logger::info_level_e::ZERO, findSettingsOverall,  "Destructor of FindSettings class");
}

const std::string app::windows::shared::FindSettings::print() const {
	std::string settings;

	settings = settings + " text: " + this->text.toStdString();
	settings = settings + " case sensitive: " + std::to_string((int)this->caseSensitive);
	settings = settings + " match full word: " + std::to_string((int)this->matchFullWord);
	settings = settings + " direction: " + this->direction;

	return settings;
}

CONST_SETTER_GETTER(app::windows::shared::FindSettings::setDirection, app::windows::shared::FindSettings::getDirection, app::shared::offset_type_e &, this->direction)
CONST_SETTER_GETTER(app::windows::shared::FindSettings::setCaseSensitive, app::windows::shared::FindSettings::getCaseSensitive, bool &, this->caseSensitive)
CONST_SETTER_GETTER(app::windows::shared::FindSettings::setMatchFullWord, app::windows::shared::FindSettings::getMatchFullWord, bool &, this->matchFullWord)
CONST_SETTER_GETTER(app::windows::shared::FindSettings::setText, app::windows::shared::FindSettings::getText, QString &, this->text)
