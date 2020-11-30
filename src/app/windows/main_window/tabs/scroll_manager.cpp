/**
 * @copyright
 * @file scroll_manager.cpp
 * @author Andrea Gianarda
 * @date 07th of May 2020
 * @brief Main Window Tab Scroll Manager functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>

#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/windows/main_window/tabs/scroll_manager.h"

// Categories
LOGGING_CONTEXT(mainWindowTabScrollManagerOverall, mainWindowTabScrollManager.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::ScrollManager::ScrollManager(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> browserTab, const std::shared_ptr<app::base::tab::TabBar> & tabBar): app::base::tab::ScrollManager(parent, browserTab, tabBar) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabScrollManagerOverall,  "ScrollManager constructor");

}

app::main_window::tab::ScrollManager::~ScrollManager() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowTabScrollManagerOverall,  "ScrollManager destructor");

}

CASTED_SHARED_PTR_GETTER(app::main_window::tab::ScrollManager::getTab, app::main_window::tab::Tab, app::base::tab::ScrollManager::getTab())
