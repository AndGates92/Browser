/**
 * @copyright
 * @file main_window_tab_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main window tab search functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "macros.h"
#include "main_window_tab_search.h"
#include "main_window_web_engine_view.h"
#include "main_window_tab.h"
#include "exception_macros.h"

// Categories
LOGGING_CONTEXT(mainWindowTabSearchOverall, mainWindowTabSearch.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowTabSearchFind, mainWindowTabSearch.find, TYPE_LEVEL, INFO_VERBOSITY)

main_window_tab_search::MainWindowTabSearch::MainWindowTabSearch(QWidget * parent, std::weak_ptr<main_window_tab::MainWindowTab> attachedTab): tab_search::TabSearch(parent, attachedTab) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchOverall,  "Main window tab search constructor");

	this->connectSignals();
}

main_window_tab_search::MainWindowTabSearch::~MainWindowTabSearch() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchOverall,  "Main window tab search destructor");

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

	const QString text = this->settings.getText();
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchFind,  "Searching text " << text << " in the current tab - Match " << activeMatch << " out of " << numberOfMatches);

	const main_window_tab_search::search_data_s & data { activeMatch, numberOfMatches };
	emit searchResultChanged(data);
}
#endif // QT_VERSION

void main_window_tab_search::MainWindowTabSearch::setCallback() {

	this->callback = [=] (bool found) {
		LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchFind,  "Searching text in the current tab - Found: " << found);
		emit this->findTextFinished(found);
	};

}
