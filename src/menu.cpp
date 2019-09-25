/**
 * @copyright
 * @file menu.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Top Menu functions
 */

// Qt libraries
#include "global_macros.h"
#include "global_types.h"

#include "menu.h"

// Categories
Q_LOGGING_CATEGORY(menuOverall, "menu.overall", MSG_TYPE_LEVEL)

menu::Menu::Menu(QWidget * window, QMenuBar * menuBar) : window(window), menuBar(menuBar) {

}

