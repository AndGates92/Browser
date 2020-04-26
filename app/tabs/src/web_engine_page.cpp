/**
 * @copyright
 * @file web_engine_page.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine page functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "web_engine_page.h"

// Categories
Q_LOGGING_CATEGORY(webEnginePageOverall, "webEnginePage.overall", MSG_TYPE_LEVEL)

web_engine_page::WebEnginePage::WebEnginePage(web_engine_profile::WebEngineProfile * profile, QWidget * parent): QWebEnginePage(profile, parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEnginePageOverall,  "Web engine page constructor");
}

web_engine_page::WebEnginePage::WebEnginePage(QWidget * parent): QWebEnginePage(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEnginePageOverall,  "Web engine page constructor");

}

web_engine_page::WebEnginePage::~WebEnginePage() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEnginePageOverall,  "Web engine page destructor");

}
