/**
 * @copyright
 * @file web_engine_profile.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine profile functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "macros.h"
#include "web_engine_profile.h"
#include "exception_macros.h"

// Categories
LOGGING_CONTEXT(webEngineProfileOverall, webEngineProfile.overall, TYPE_LEVEL, INFO_VERBOSITY)

web_engine_profile::WebEngineProfile * web_engine_profile::WebEngineProfile::defaultProfile() {

	try {
		web_engine_profile::WebEngineProfile * profile = dynamic_cast<web_engine_profile::WebEngineProfile *>(QWebEngineProfile::defaultProfile());
		return profile;
	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;

}

web_engine_profile::WebEngineProfile::WebEngineProfile(QObject * parent, const QString & storageName): QWebEngineProfile(storageName, parent) {
	LOG_INFO(logger::info_level_e::ZERO, webEngineProfileOverall,  "Web engine profile constructor");

}

web_engine_profile::WebEngineProfile::~WebEngineProfile() {
	LOG_INFO(logger::info_level_e::ZERO, webEngineProfileOverall,  "Web engine profile destructor");

}
