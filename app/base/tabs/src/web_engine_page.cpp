/**
 * @copyright
 * @file web_engine_page.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine page functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "base/tabs/include/web_engine_page.h"

// Categories
LOGGING_CONTEXT(webEnginePageOverall, webEnginePage.overall, TYPE_LEVEL, INFO_VERBOSITY)

web_engine_page::WebEnginePage::WebEnginePage(QWidget * parent, web_engine_profile::WebEngineProfile * profile): QWebEnginePage(profile, parent) {
	LOG_INFO(logger::info_level_e::ZERO, webEnginePageOverall,  "Web engine page constructor");
}

web_engine_page::WebEnginePage::~WebEnginePage() {
	LOG_INFO(logger::info_level_e::ZERO, webEnginePageOverall,  "Web engine page destructor");
}

CASTED_PTR_GETTER(web_engine_page::WebEnginePage::profile, web_engine_profile::WebEngineProfile, QWebEnginePage::profile())
