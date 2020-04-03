/**
 * @copyright
 * @file web_engine_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine search functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "web_engine_search.h"

// Categories
Q_LOGGING_CATEGORY(webEngineSearchOverall, "webEngineSearch.overall", MSG_TYPE_LEVEL)

web_engine_search::WebEngineSearch::WebEngineSearch(QWidget * attachedTab, QObject * parent): QObject(parent), tab(attachedTab) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineSearchOverall,  "Web engine search constructor");
	this->text = QString::null;
	this->flags = QWebEnginePage::FindFlag(0);
}

web_engine_search::WebEngineSearch::~WebEngineSearch() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, webEngineSearchOverall,  "Web engine search destructor");

}
