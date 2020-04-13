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

main_window_web_engine_view::MainWindowWebEngineView::MainWindowWebEngineView(const main_window_shared_types::page_type_e type, const QString & src, const void * data, QWidget * parent): web_engine_view::WebEngineView(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view constructor");

	main_window_web_engine_page::MainWindowWebEnginePage * page = new main_window_web_engine_page::MainWindowWebEnginePage(type, src, main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile(), data, parent);
	this->setPage(page);

}

main_window_web_engine_view::MainWindowWebEngineView::~MainWindowWebEngineView() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view destructor");

}

CASTED_PTR_GETTER(main_window_web_engine_view::MainWindowWebEngineView::page, main_window_web_engine_page::MainWindowWebEnginePage, web_engine_view::WebEngineView::page())
