/**
 * @copyright
 * @file web_engine_settings.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine settings functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/web_engine_settings.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEngineSettingsOverall, mainWindowWebEngineSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::WebEngineSettings::WebEngineSettings(QWebEngineSettings * newSettings): web_engine_settings::WebEngineSettings(newSettings) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings constructor");

}

main_window::WebEngineSettings::WebEngineSettings(const main_window::WebEngineSettings & rhs) : web_engine_settings::WebEngineSettings(rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy constructor web engine settings");

}

main_window::WebEngineSettings & main_window::WebEngineSettings::operator=(const main_window::WebEngineSettings & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy assignment operator for web engine settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	this->web_engine_settings::WebEngineSettings::operator=(rhs);

	return *this;
}

main_window::WebEngineSettings::WebEngineSettings(main_window::WebEngineSettings && rhs) :  web_engine_settings::WebEngineSettings(std::move(rhs)) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move constructor web engine settings");
}

main_window::WebEngineSettings & main_window::WebEngineSettings::operator=(main_window::WebEngineSettings && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move assignment operator for web engine settings");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->web_engine_settings::WebEngineSettings::operator=(std::move(rhs));
	}

	return *this;
}

main_window::WebEngineSettings::~WebEngineSettings() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings destructor");

}
