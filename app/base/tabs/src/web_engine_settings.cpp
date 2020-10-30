/**
 * @copyright
 * @file web_engine_settings.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine settings functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "macros.h"
#include "web_engine_settings.h"

// Categories
LOGGING_CONTEXT(webEngineSettingsOverall, webEngineSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

web_engine_settings::WebEngineSettings::WebEngineSettings(QWebEngineSettings * newSettings): settings(newSettings) {
	LOG_INFO(logger::info_level_e::ZERO, webEngineSettingsOverall,  "Web engine settings constructor");

	// Hide scrollbars
	this->settings->setAttribute(QWebEngineSettings::ShowScrollBars, false);

}

web_engine_settings::WebEngineSettings::WebEngineSettings(const web_engine_settings::WebEngineSettings & rhs) : settings(rhs.settings) {

	LOG_INFO(logger::info_level_e::ZERO, webEngineSettingsOverall,  "Copy constructor web engine settings");

}

web_engine_settings::WebEngineSettings & web_engine_settings::WebEngineSettings::operator=(const web_engine_settings::WebEngineSettings & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, webEngineSettingsOverall,  "Copy assignment operator for web engine settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	if (this->settings != rhs.settings) {
		this->settings = rhs.settings;
	}

	return *this;
}

web_engine_settings::WebEngineSettings::WebEngineSettings(web_engine_settings::WebEngineSettings && rhs) : settings(std::exchange(rhs.settings, Q_NULLPTR)) {

	LOG_INFO(logger::info_level_e::ZERO, webEngineSettingsOverall,  "Move constructor web engine settings");
}

web_engine_settings::WebEngineSettings & web_engine_settings::WebEngineSettings::operator=(web_engine_settings::WebEngineSettings && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, webEngineSettingsOverall,  "Move assignment operator for web engine settings");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->settings = std::exchange(rhs.settings, Q_NULLPTR);
	}

	return *this;
}

web_engine_settings::WebEngineSettings::~WebEngineSettings() {
	LOG_INFO(logger::info_level_e::ZERO, webEngineSettingsOverall,  "Web engine settings destructor");

}
