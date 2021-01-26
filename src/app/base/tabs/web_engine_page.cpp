/**
 * @copyright
 * @file web_engine_page.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine page functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/base/tabs/web_engine_page.h"

// Categories
LOGGING_CONTEXT(webEnginePageOverall, webEnginePage.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::WebEnginePage::WebEnginePage(QWidget * parent, app::base::tab::WebEngineProfile * profile): QWebEnginePage(profile, parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, webEnginePageOverall, "Web engine page constructor");
}

app::base::tab::WebEnginePage::~WebEnginePage() {
	LOG_INFO(app::logger::info_level_e::ZERO, webEnginePageOverall, "Web engine page destructor");
}

CASTED_PTR_GETTER(app::base::tab::WebEnginePage::profile, app::base::tab::WebEngineProfile, QWebEnginePage::profile())
