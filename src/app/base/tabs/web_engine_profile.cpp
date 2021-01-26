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
#include "app/base/tabs/web_engine_profile.h"
#include "app/shared/exception.h"

// Categories
LOGGING_CONTEXT(webEngineProfileOverall, webEngineProfile.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::WebEngineProfile * app::base::tab::WebEngineProfile::defaultProfile() {

	try {
		static app::base::tab::WebEngineProfile * profile = dynamic_cast<app::base::tab::WebEngineProfile *>(QWebEngineProfile::defaultProfile());
		return profile;
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;

}

app::base::tab::WebEngineProfile::WebEngineProfile(const QString & storageName, QObject * parent): QWebEngineProfile(storageName, parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, webEngineProfileOverall, "Web engine profile constructor");

}

app::base::tab::WebEngineProfile::~WebEngineProfile() {
	LOG_INFO(app::logger::info_level_e::ZERO, webEngineProfileOverall, "Web engine profile destructor");

}
