/**
 * @copyright
 * @file web_engine_settings.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine settings functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/logger/macros.h"
#include "app/base/tabs/web_engine_settings.h"

// Categories
LOGGING_CONTEXT(webEngineSettingsOverall, webEngineSettings.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::WebEngineSettings::WebEngineSettings(QWebEngineSettings * newSettings): settings(newSettings) {
	LOG_INFO(app::logger::info_level_e::ZERO, webEngineSettingsOverall,  "Web engine settings constructor");

	// Hide scrollbars
	this->settings->setAttribute(QWebEngineSettings::ShowScrollBars, false);

}

app::base::tab::WebEngineSettings::WebEngineSettings(const app::base::tab::WebEngineSettings & rhs) : settings(rhs.settings) {

	LOG_INFO(app::logger::info_level_e::ZERO, webEngineSettingsOverall,  "Copy constructor web engine settings");

}

app::base::tab::WebEngineSettings & app::base::tab::WebEngineSettings::operator=(const app::base::tab::WebEngineSettings & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, webEngineSettingsOverall,  "Copy assignment operator for web engine settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	if (this->settings != rhs.settings) {
		this->settings = rhs.settings;
	}

	return *this;
}

app::base::tab::WebEngineSettings::WebEngineSettings(app::base::tab::WebEngineSettings && rhs) : settings(std::exchange(rhs.settings, Q_NULLPTR)) {

	LOG_INFO(app::logger::info_level_e::ZERO, webEngineSettingsOverall,  "Move constructor web engine settings");
}

app::base::tab::WebEngineSettings & app::base::tab::WebEngineSettings::operator=(app::base::tab::WebEngineSettings && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, webEngineSettingsOverall,  "Move assignment operator for web engine settings");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->settings = std::exchange(rhs.settings, Q_NULLPTR);
	}

	return *this;
}

app::base::tab::WebEngineSettings::~WebEngineSettings() {
	LOG_INFO(app::logger::info_level_e::ZERO, webEngineSettingsOverall,  "Web engine settings destructor");

}
