/**
 * @copyright
 * @file main_window_menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar functions
 */

#include <iostream>
// Qt libraries
#include <QtCore/QtGlobal>

#include "main_window_menu_bar.h"
#include "global_enums.h"
#include "function_macros.h"
#include "logging_macros.h"

Q_LOGGING_CATEGORY(mainWindowMenuBarOverall, "menuBar.overall", MSG_TYPE_LEVEL)

main_window_menu_bar::MainWindowMenuBar::MainWindowMenuBar(QWidget * parent) : menu_bar::MenuBar(parent), fileMenu(Q_NULLPTR), editMenu(Q_NULLPTR) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar constructor");
}

void main_window_menu_bar::MainWindowMenuBar::createMenus() {
	this->fileMenu = std::make_unique<file_menu::FileMenu>(this, this->weak_from_this(), "File", key_sequence::KeySequence(Qt::Key_F));
	this->editMenu = std::make_unique<edit_menu::EditMenu>(this, this->weak_from_this(), "Edit", key_sequence::KeySequence(Qt::Key_E));
}

main_window_menu_bar::MainWindowMenuBar::~MainWindowMenuBar() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar destructor");
}

CONST_GETTER(main_window_menu_bar::MainWindowMenuBar::getFileMenu, std::unique_ptr<file_menu::FileMenu> &, this->fileMenu)
CONST_GETTER(main_window_menu_bar::MainWindowMenuBar::getEditMenu, std::unique_ptr<edit_menu::EditMenu> &, this->editMenu)
