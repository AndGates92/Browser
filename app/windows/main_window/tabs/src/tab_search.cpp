/**
 * @copyright
 * @file tab_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main window tab search functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "utility/stl/include/cpp_operator.h"
#include "utility/logger/include/macros.h"
#include "windows/main_window/tabs/include/tab_search.h"
#include "windows/main_window/tabs/include/web_engine_view.h"
#include "windows/main_window/tabs/include/tab.h"
#include "common/include/exception_macros.h"

// Categories
LOGGING_CONTEXT(mainWindowTabSearchOverall, mainWindowTabSearch.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowTabSearchFind, mainWindowTabSearch.find, TYPE_LEVEL, INFO_VERBOSITY)

main_window::TabSearch::TabSearch(QWidget * parent, std::weak_ptr<main_window::Tab> attachedTab): tab_search::TabSearch(parent, attachedTab) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchOverall,  "Main window tab search constructor");

	this->connectSignals();
}

main_window::TabSearch::~TabSearch() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchOverall,  "Main window tab search destructor");

}

CASTED_SHARED_PTR_GETTER(main_window::TabSearch::getTab, main_window::Tab, tab_search::TabSearch::getTab())

void main_window::TabSearch::connectSignals() {

	#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	std::shared_ptr<main_window::Tab> currentTab = this->getTab();
	std::shared_ptr<main_window::WebEnginePage> currentTabPage = currentTab->getPage();
	connect(currentTabPage.get(), &main_window::WebEnginePage::findTextFinished, this, &main_window::TabSearch::postProcessSearch, Qt::UniqueConnection);
	#endif // QT_VERSION

}

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
void main_window::TabSearch::postProcessSearch(const QWebEngineFindTextResult & result) {
	const int & activeMatch = result.activeMatch();
	const int & numberOfMatches = result.numberOfMatches();

	const QString text = this->settings.getText();
	LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchFind,  "Searching text " << text << " in the current tab - Match " << activeMatch << " out of " << numberOfMatches);

	const main_window::search_data_s & data { activeMatch, numberOfMatches };
	emit searchResultChanged(data);
}
#endif // QT_VERSION

void main_window::TabSearch::setCallback() {

	this->callback = [=] (bool found) {
		LOG_INFO(logger::info_level_e::ZERO, mainWindowTabSearchFind,  "Searching text in the current tab - Found: " << found);
		emit this->findTextFinished(found);
	};

}
