/**
 * @copyright
 * @file web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/base/tabs/web_engine_page.h"
#include "app/base/tabs/web_engine_view.h"

// Categories
LOGGING_CONTEXT(webEngineViewOverall, webEngineView.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::tab::WebEngineView::WebEngineView(QWidget * parent): QWebEngineView(parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, webEngineViewOverall,  "Web engine view constructor");

	// Use deleteLater to schedule a destruction event in the event loop
	std::shared_ptr<app::base::tab::WebEnginePage> newPage = std::shared_ptr<app::base::tab::WebEnginePage>(new app::base::tab::WebEnginePage(parent, app::base::tab::WebEngineProfile::defaultProfile()), [] (app::base::tab::WebEnginePage * p) {
		p->deleteLater();
	});
	this->updatePage(newPage);
}

app::base::tab::WebEngineView::~WebEngineView() {
	LOG_INFO(app::logger::info_level_e::ZERO, webEngineViewOverall,  "Web engine view destructor");
}

void app::base::tab::WebEngineView::updatePage(const std::shared_ptr<app::base::tab::WebEnginePage> & newPage) {
	this->currentPage = newPage;
	this->setPage(this->currentPage.get());
}

BASE_GETTER(app::base::tab::WebEngineView::page, std::shared_ptr<app::base::tab::WebEnginePage>, this->currentPage)
