/**
 * @copyright
 * @file web_engine_profile.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine profile functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/exception_macros.h"
#include "windows/main_window/tabs/include/web_engine_profile.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEngineProfileOverall, mainWindowWebEngineProfile.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::WebEngineProfile * main_window::WebEngineProfile::defaultProfile() {
	try {
		main_window::WebEngineProfile * profile = dynamic_cast<main_window::WebEngineProfile *>(web_engine_profile::WebEngineProfile::defaultProfile());
		return profile;
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;
}

main_window::WebEngineProfile::WebEngineProfile(QObject * parent, const QString & storageName): web_engine_profile::WebEngineProfile(parent, storageName) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineProfileOverall,  "Web engine profile constructor");

}

main_window::WebEngineProfile::~WebEngineProfile() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowWebEngineProfileOverall,  "Web engine profile destructor");

}
