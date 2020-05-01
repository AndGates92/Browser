/**
 * @copyright
 * @file tab_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Tab search functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "tab_search.h"

// Categories
Q_LOGGING_CATEGORY(tabSearchOverall, "tabSearch.overall", MSG_TYPE_LEVEL)

tab_search::TabSearch::TabSearch(QWidget * attachedTab, QObject * parent): QObject(parent), tab(attachedTab), text(QString::null), flags(QWebEnginePage::FindFlag(0)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search constructor");
}

tab_search::TabSearch::~TabSearch() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabSearchOverall,  "Tab search destructor");

}
