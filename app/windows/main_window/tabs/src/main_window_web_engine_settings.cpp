/**
 * @copyright
 * @file main_window_web_engine_settings.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine settings functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_web_engine_settings.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineSettingsOverall, "mainWindowWebEngineSettings.overall", MSG_TYPE_LEVEL)

main_window_web_engine_settings::MainWindowWebEngineSettings::MainWindowWebEngineSettings(QWebEngineSettings * newSettings): web_engine_settings::WebEngineSettings(newSettings) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings constructor");

}

main_window_web_engine_settings::MainWindowWebEngineSettings::MainWindowWebEngineSettings(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs) : web_engine_settings::WebEngineSettings(rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy constructor web engine settings");

}

main_window_web_engine_settings::MainWindowWebEngineSettings & main_window_web_engine_settings::MainWindowWebEngineSettings::operator=(const main_window_web_engine_settings::MainWindowWebEngineSettings & rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Copy assignment operator for web engine settings");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}
	
	this->web_engine_settings::WebEngineSettings::operator=(rhs);

	return *this;
}

main_window_web_engine_settings::MainWindowWebEngineSettings::MainWindowWebEngineSettings(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs) :  web_engine_settings::WebEngineSettings(rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move constructor web engine settings");
}

main_window_web_engine_settings::MainWindowWebEngineSettings & main_window_web_engine_settings::MainWindowWebEngineSettings::operator=(main_window_web_engine_settings::MainWindowWebEngineSettings && rhs) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Move assignment operator for web engine settings");

	// If rhs doesn't point to the same address as this, then execute move
	if (&rhs != this) {
		this->web_engine_settings::WebEngineSettings::operator=(rhs);
	}

	return *this;
}

main_window_web_engine_settings::MainWindowWebEngineSettings::~MainWindowWebEngineSettings() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineSettingsOverall,  "Web engine settings destructor");

}
