/**
 * @copyright
 * @file search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Main window tab search functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/windows/main_window/tabs/search.h"
#include "app/windows/main_window/tabs/web_engine_view.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/shared/exception.h"

// Categories
LOGGING_CONTEXT(mainWindowTabSearchOverall, mainWindowTabSearch.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowTabSearchFind, mainWindowTabSearch.find, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::Search::Search(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> attachedTab): app::base::tab::Search(parent, attachedTab) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabSearchOverall,  "Main window tab search constructor");

	this->connectSignals();
}

app::main_window::tab::Search::~Search() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabSearchOverall,  "Main window tab search destructor");

}

CASTED_SHARED_PTR_GETTER(app::main_window::tab::Search::getTab, app::main_window::tab::Tab, app::base::tab::Search::getTab())

void app::main_window::tab::Search::connectSignals() {

	#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
	std::shared_ptr<app::main_window::tab::Tab> currentTab = this->getTab();
	std::shared_ptr<app::main_window::tab::WebEnginePage> currentTabPage = currentTab->getPage();
	connect(currentTabPage.get(), &app::main_window::tab::WebEnginePage::findTextFinished, this, &app::main_window::tab::Search::postProcessSearch, Qt::UniqueConnection);
	#endif // QT_VERSION

}

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
void app::main_window::tab::Search::postProcessSearch(const QWebEngineFindTextResult & result) {
	const int & activeMatch = result.activeMatch();
	const int & numberOfMatches = result.numberOfMatches();

	const QString text = this->settings.getText();
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabSearchFind,  "Searching text " << text << " in the current tab - Match " << activeMatch << " out of " << numberOfMatches);

	const app::main_window::tab::search_data_s & data { activeMatch, numberOfMatches };
	emit searchResultChanged(data);
}
#endif // QT_VERSION

void app::main_window::tab::Search::setCallback() {

	this->callback = [=] (bool found) {
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabSearchFind,  "Searching text in the current tab - Found: " << found);
		emit this->findTextFinished(found);
	};

}
