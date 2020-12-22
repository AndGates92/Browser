/**
 * @copyright
 * @file web_engine_profile.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine profile functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/logger/macros.h"
#include "app/shared/exception.h"
#include "app/windows/main_window/tabs/web_engine_profile.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEngineProfileOverall, mainWindowWebEngineProfile.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::WebEngineProfile * app::main_window::tab::WebEngineProfile::defaultProfile() {
	try {
		static app::main_window::tab::WebEngineProfile * profile = dynamic_cast<app::main_window::tab::WebEngineProfile *>(app::base::tab::WebEngineProfile::defaultProfile());
		return profile;
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;
}

app::main_window::tab::WebEngineProfile::WebEngineProfile(const QString & storageName, QObject * parent): app::base::tab::WebEngineProfile(storageName, parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineProfileOverall,  "Web engine profile constructor");

}

app::main_window::tab::WebEngineProfile::~WebEngineProfile() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineProfileOverall,  "Web engine profile destructor");

}
