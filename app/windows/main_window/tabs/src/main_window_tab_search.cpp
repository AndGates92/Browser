/**
 * @copyright
 * @file main_window_tab_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main window tab search functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_tab_search.h"
#include "main_window_web_engine_view.h"
#include "main_window_tab.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowTabSearchOverall, "mainWindowTabSearch.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabSearchFind, "mainWindowTabSearch.find", MSG_TYPE_LEVEL)

main_window_tab_search::MainWindowTabSearch::MainWindowTabSearch(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> attachedTab): tab_search::TabSearch(parent, attachedTab) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabSearchOverall,  "Tab search constructor");

	this->connectSignals();
}

main_window_tab_search::MainWindowTabSearch::~MainWindowTabSearch() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabSearchOverall,  "Tab search destructor");

}

CASTED_SHARED_PTR_GETTER(main_window_tab_search::MainWindowTabSearch::getTab, main_window_tab::MainWindowTab, tab_search::TabSearch::getTab())

void main_window_tab_search::MainWindowTabSearch::connectSignals() {

	#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	std::shared_ptr<main_window_tab::MainWindowTab> currentTab = this->getTab();
	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> currentTabPage = currentTab->getPage();
	connect(currentTabPage.get(), &main_window_web_engine_page::MainWindowWebEnginePage::findTextFinished, this, &main_window_tab_search::MainWindowTabSearch::postProcessSearch, Qt::UniqueConnection);
	#endif // QT_VERSION

}

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
void main_window_tab_search::MainWindowTabSearch::postProcessSearch(const QWebEngineFindTextResult & result) {
	const int & activeMatch = result.activeMatch();
	const int & numberOfMatches = result.numberOfMatches();

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowTabSearchFind,  "Match " << activeMatch << " out of " << numberOfMatches);
}
#endif // QT_VERSION
