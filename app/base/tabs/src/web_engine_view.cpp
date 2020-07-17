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
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, webEngineViewOverall,  "Web engine view constructor");

	// Use deleteLater to schedule a destruction event in the event loop
	std::shared_ptr<web_engine_page::WebEnginePage> newPage = std::shared_ptr<web_engine_page::WebEnginePage>(new web_engine_page::WebEnginePage(parent, web_engine_profile::WebEngineProfile::defaultProfile()), [] (web_engine_page::WebEnginePage * p) {
		p->deleteLater();
	});
	this->updatePage(newPage);
}

web_engine_view::WebEngineView::~WebEngineView() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, webEngineViewOverall,  "Web engine view destructor");
}

void web_engine_view::WebEngineView::updatePage(const std::shared_ptr<web_engine_page::WebEnginePage> newPage) {
	this->currentPage = newPage;
	this->setPage(this->currentPage.get());
}

BASE_GETTER(web_engine_view::WebEngineView::page, std::shared_ptr<web_engine_page::WebEnginePage>, this->currentPage)
