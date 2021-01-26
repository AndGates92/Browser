/**
 * @copyright
 * @file menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Menu bar functions
 */

#include <iostream>

#include "app/base/menu/menu_bar.h"
#include "app/shared/enums.h"
#include "app/utility/logger/macros.h"

LOGGING_CONTEXT(menuBarOverall, menuBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::menu::MenuBar::MenuBar(QWidget * parent) : QMenuBar(parent) {
	LOG_INFO(app::logger::info_level_e::ZERO, menuBarOverall, "Menu bar constructor");

}

app::base::menu::MenuBar::~MenuBar() {
	LOG_INFO(app::logger::info_level_e::ZERO, menuBarOverall, "Menu bar desstructor");

}
