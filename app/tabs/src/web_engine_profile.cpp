/**
 * @copyright
 * @file web_engine_profile.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine profile functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "web_engine_profile.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(webEngineProfileOverall, "webEngineProfile.overall", MSG_TYPE_LEVEL)

web_engine_profile::WebEngineProfile * web_engine_profile::WebEngineProfile::defaultProfile() {
	try {

		web_engine_profile::WebEngineProfile * profile = dynamic_cast<web_engine_profile::WebEngineProfile *>(QWebEngineProfile::defaultProfile());
		return profile;

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;

}

web_engine_profile::WebEngineProfile::WebEngineProfile(const QString & storageName, QObject * parent): QWebEngineProfile(storageName, parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineProfileOverall,  "Web engine profile constructor");

}

web_engine_profile::WebEngineProfile::WebEngineProfile(QObject * parent): QWebEngineProfile(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineProfileOverall,  "Web engine profile constructor");

}

web_engine_profile::WebEngineProfile::~WebEngineProfile() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineProfileOverall,  "Web engine profile destructor");

}
