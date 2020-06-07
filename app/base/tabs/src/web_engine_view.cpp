/**
 * @copyright
 * @file web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "web_engine_view.h"

// Categories
Q_LOGGING_CATEGORY(webEngineViewOverall, "webEngineView.overall", MSG_TYPE_LEVEL)

web_engine_view::WebEngineView::WebEngineView(QWidget * parent): QWebEngineView(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineViewOverall,  "Web engine view constructor");

	web_engine_page::WebEnginePage * viewPage = new web_engine_page::WebEnginePage(parent, web_engine_profile::WebEngineProfile::defaultProfile());
	this->setPage(viewPage);
}

web_engine_view::WebEngineView::~WebEngineView() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineViewOverall,  "Web engine view destructor");
}

CASTED_PTR_GETTER(web_engine_view::WebEngineView::page, web_engine_page::WebEnginePage, QWebEngineView::page())
