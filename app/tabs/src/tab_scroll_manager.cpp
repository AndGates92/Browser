/**
 * @copyright
 * @file tab_scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Tab Scroll Manager functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "function_macros.h"
#include "tab_scroll_manager.h"

// Categories
Q_LOGGING_CATEGORY(tabScrollManagerOverall, "tabScrollManager.overall", MSG_TYPE_LEVEL)

tab_scroll_manager::TabScrollManager::TabScrollManager(QWidget * parent): QWidget(parent), scrollPosition(QPointF(0.0, 0.0)), contentsSize(QSizeF(0.0, 0.0)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager constructor");
}

tab_scroll_manager::TabScrollManager::~TabScrollManager() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, tabScrollManagerOverall,  "TabScrollManager destructor");
}

CONST_SETTER_GETTER(tab_scroll_manager::TabScrollManager::updateContentsSize, tab_scroll_manager::TabScrollManager::getContentsSize, QSizeF &, this->contentsSize)

CONST_SETTER_GETTER(tab_scroll_manager::TabScrollManager::updateScrollPosition, tab_scroll_manager::TabScrollManager::getScrollPosition, QPointF &, this->scrollPosition)
