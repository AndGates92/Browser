/**
 * @copyright
 * @file menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar functions
 */

#include <iostream>

#include "app/shared/enums.h"
#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/windows/main_window/menu/file_menu.h"
#include "app/windows/main_window/menu/edit_menu.h"
#include "app/windows/main_window/menu/menu_bar.h"

LOGGING_CONTEXT(mainWindowMenuBarOverall, menuBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::menu::MenuBar::MenuBar(QWidget * parent) : app::base::menu::MenuBar(parent), fileMenu(Q_NULLPTR), editMenu(Q_NULLPTR) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar constructor");
}

void app::main_window::menu::MenuBar::createMenus() {
	this->fileMenu = std::make_unique<app::main_window::menu::FileMenu>(this, this->weak_from_this(), "File", app::key_sequence::KeySequence(Qt::Key_F));
	this->editMenu = std::make_unique<app::main_window::menu::EditMenu>(this, this->weak_from_this(), "Edit", app::key_sequence::KeySequence(Qt::Key_E));
}

app::main_window::menu::MenuBar::~MenuBar() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar destructor");
}

CONST_GETTER(app::main_window::menu::MenuBar::getFileMenu, std::unique_ptr<app::main_window::menu::FileMenu> &, this->fileMenu)
CONST_GETTER(app::main_window::menu::MenuBar::getEditMenu, std::unique_ptr<app::main_window::menu::EditMenu> &, this->editMenu)
