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
#include "exception_macros.h"
#include "main_window_web_engine_view.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineViewOverall, "mainWindowWebEngineView.overall", MSG_TYPE_LEVEL)

main_window_web_engine_view::MainWindowWebEngineView::MainWindowWebEngineView(const main_window_shared_types::tab_type_e type, const void * data, const void * tabContent, QWidget * parent): web_engine_view::WebEngineView(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view constructor");

	main_window_web_engine_page::MainWindowWebEnginePage * page = new main_window_web_engine_page::MainWindowWebEnginePage(type, data, tabContent, main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile(), parent);
	this->setPage(page);

}

main_window_web_engine_view::MainWindowWebEngineView::~MainWindowWebEngineView() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view destructor");

}

main_window_web_engine_page::MainWindowWebEnginePage * main_window_web_engine_view::MainWindowWebEngineView::page() const {
	try {
		main_window_web_engine_page::MainWindowWebEnginePage * p = dynamic_cast<main_window_web_engine_page::MainWindowWebEnginePage *>(web_engine_view::WebEngineView::page());
		return p;
	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

	return Q_NULLPTR;
}
