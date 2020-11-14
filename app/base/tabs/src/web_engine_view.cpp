/**
 * @copyright
 * @file web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/logger/include/macros.h"
#include "common/include/function_macros.h"
#include "base/tabs/include/web_engine_view.h"

// Categories
LOGGING_CONTEXT(webEngineViewOverall, webEngineView.overall, TYPE_LEVEL, INFO_VERBOSITY)

web_engine_view::WebEngineView::WebEngineView(QWidget * parent): QWebEngineView(parent) {
	LOG_INFO(logger::info_level_e::ZERO, webEngineViewOverall,  "Web engine view constructor");

	// Use deleteLater to schedule a destruction event in the event loop
	std::shared_ptr<web_engine_page::WebEnginePage> newPage = std::shared_ptr<web_engine_page::WebEnginePage>(new web_engine_page::WebEnginePage(parent, web_engine_profile::WebEngineProfile::defaultProfile()), [] (web_engine_page::WebEnginePage * p) {
		p->deleteLater();
	});
	this->updatePage(newPage);
}

web_engine_view::WebEngineView::~WebEngineView() {
	LOG_INFO(logger::info_level_e::ZERO, webEngineViewOverall,  "Web engine view destructor");
}

void web_engine_view::WebEngineView::updatePage(const std::shared_ptr<web_engine_page::WebEnginePage> & newPage) {
	this->currentPage = newPage;
	this->setPage(this->currentPage.get());
}

BASE_GETTER(web_engine_view::WebEngineView::page, std::shared_ptr<web_engine_page::WebEnginePage>, this->currentPage)
