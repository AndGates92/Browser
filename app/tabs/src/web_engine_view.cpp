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
#include "exception_macros.h"
#include "web_engine_view.h"

// Categories
Q_LOGGING_CATEGORY(webEngineViewOverall, "webEngineView.overall", MSG_TYPE_LEVEL)

web_engine_view::WebEngineView::WebEngineView(QWidget * parent): QWebEngineView(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineViewOverall,  "Web engine view constructor");

	web_engine_page::WebEnginePage * page = new web_engine_page::WebEnginePage(web_engine_profile::WebEngineProfile::defaultProfile(), parent);
	this->setPage(page);

}

web_engine_view::WebEngineView::~WebEngineView() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineViewOverall,  "Web engine view destructor");

}

web_engine_page::WebEnginePage * web_engine_view::WebEngineView::page() const {
	try {
		return dynamic_cast<web_engine_page::WebEnginePage *>(QWebEngineView::page());
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;
}
