/**
 * @copyright
 * @file menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Menu bar functions
 */

#include <iostream>
// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "menu_bar.h"
#include "global_types.h"
#include "logging_macros.h"

Q_LOGGING_CATEGORY(menuBarOverall, "menuBar.overall", MSG_TYPE_LEVEL)

menu_bar::MenuBar::MenuBar(QWidget * parent) : QMenuBar(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, menuBarOverall,  "Menu bar constructor");

}

menu_bar::MenuBar::~MenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, menuBarOverall,  "Menu bar desstructor");

}
