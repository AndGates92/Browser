/**
 * @copyright
 * @file main_window_web_engine_profile.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine profile functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "exception_macros.h"
#include "main_window_web_engine_profile.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineProfileOverall, "mainWindowWebEngineProfile.overall", MSG_TYPE_LEVEL)

main_window_web_engine_profile::MainWindowWebEngineProfile * main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile() {
	try {
		main_window_web_engine_profile::MainWindowWebEngineProfile * profile = dynamic_cast<main_window_web_engine_profile::MainWindowWebEngineProfile *>(web_engine_profile::WebEngineProfile::defaultProfile());
		return profile;
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;
}

main_window_web_engine_profile::MainWindowWebEngineProfile::MainWindowWebEngineProfile(QObject * parent, const QString & storageName): web_engine_profile::WebEngineProfile(parent, storageName) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineProfileOverall,  "Web engine profile constructor");

}

main_window_web_engine_profile::MainWindowWebEngineProfile::~MainWindowWebEngineProfile() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineProfileOverall,  "Web engine profile destructor");

}
