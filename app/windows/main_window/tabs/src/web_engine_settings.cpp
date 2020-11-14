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

app::main_window::tab::WebEngineSettings::WebEngineSettings(QWebEngineSettings * newSettings): app::base::tab::WebEngineSettings(newSettings) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings constructor");

}

app::main_window::tab::WebEngineSettings::WebEngineSettings(const app::main_window::tab::WebEngineSettings & rhs) : app::base::tab::WebEngineSettings(rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy constructor web engine settings");

}

app::main_window::tab::WebEngineSettings & app::main_window::tab::WebEngineSettings::operator=(const app::main_window::tab::WebEngineSettings & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy assignment operator for web engine settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	app::base::tab::WebEngineSettings::operator=(rhs);

	return *this;
}

app::main_window::tab::WebEngineSettings::WebEngineSettings(app::main_window::tab::WebEngineSettings && rhs) :  app::base::tab::WebEngineSettings(std::move(rhs)) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move constructor web engine settings");
}

app::main_window::tab::WebEngineSettings & app::main_window::tab::WebEngineSettings::operator=(app::main_window::tab::WebEngineSettings && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move assignment operator for web engine settings");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		app::base::tab::WebEngineSettings::operator=(std::move(rhs));
	}

	return *this;
}

app::main_window::tab::WebEngineSettings::~WebEngineSettings() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings destructor");

}
