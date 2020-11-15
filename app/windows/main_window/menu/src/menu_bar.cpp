/**
 * @copyright
 * @file menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar functions
 */

#include <iostream>

#include "windows/main_window/menu/include/menu_bar.h"
#include "common/include/global_enums.h"
#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"

LOGGING_CONTEXT(mainWindowMenuBarOverall, menuBar.overall, TYPE_LEVEL, INFO_VERBOSITY)

main_window::MenuBar::MenuBar(QWidget * parent) : menu::MenuBar(parent), fileMenu(Q_NULLPTR), editMenu(Q_NULLPTR) {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar constructor");
}

void main_window::MenuBar::createMenus() {
	this->fileMenu = std::make_unique<file_menu::FileMenu>(this, this->weak_from_this(), "File", key_sequence::KeySequence(Qt::Key_F));
	this->editMenu = std::make_unique<edit_menu::EditMenu>(this, this->weak_from_this(), "Edit", key_sequence::KeySequence(Qt::Key_E));
}

main_window::MenuBar::~MenuBar() {
	LOG_INFO(logger::info_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar destructor");
}

CONST_GETTER(main_window::MenuBar::getFileMenu, std::unique_ptr<file_menu::FileMenu> &, this->fileMenu)
CONST_GETTER(main_window::MenuBar::getEditMenu, std::unique_ptr<edit_menu::EditMenu> &, this->editMenu)
