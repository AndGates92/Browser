/**
 * @copyright
 * @file main_window_web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"
#include "main_window_web_engine_view.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineViewOverall, "mainWindowWebEngineView.overall", MSG_TYPE_LEVEL)

main_window_web_engine_view::MainWindowWebEngineView::MainWindowWebEngineView(QWidget * parent, const main_window_shared_types::page_type_e type, const QString & src, const void * data): web_engine_view::WebEngineView(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view constructor");

	main_window_web_engine_page::MainWindowWebEnginePage * page = new main_window_web_engine_page::MainWindowWebEnginePage(parent, type, src, main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile(), data);
	this->setPage(page);

	this->connectSignals();
}

main_window_web_engine_view::MainWindowWebEngineView::~MainWindowWebEngineView() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view destructor");

}

CASTED_PTR_GETTER(main_window_web_engine_view::MainWindowWebEngineView::page, main_window_web_engine_page::MainWindowWebEnginePage, web_engine_view::WebEngineView::page())

void main_window_web_engine_view::MainWindowWebEngineView::connectSignals() {
	connect(this, &main_window_web_engine_view::MainWindowWebEngineView::urlChanged, this, &main_window_web_engine_view::MainWindowWebEngineView::updatePageSource, Qt::UniqueConnection);
}

void main_window_web_engine_view::MainWindowWebEngineView::updatePageSource(const QUrl & url) {

	main_window_web_engine_page::MainWindowWebEnginePage * enginePage = this->page();

	const main_window_shared_types::page_type_e type = enginePage->getType();

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if ((type == main_window_shared_types::page_type_e::WEB_CONTENT) && (url.isValid())) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		enginePage->setSource(urlStr);
	}
}
