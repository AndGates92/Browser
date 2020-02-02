/**
 * @copyright
 * @file main_window_menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar functions
 */

#include <iostream>
// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "main_window_menu_bar.h"
#include "global_types.h"
#include "global_macros.h"

Q_LOGGING_CATEGORY(mainWindowMenuBarOverall, "menuBar.overall", MSG_TYPE_LEVEL)

main_window_menu_bar::MainWindowMenuBar::MainWindowMenuBar(QWidget * window) : menu_bar::MenuBar(window) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar constructor");

	this->fillMenuBar();
}

main_window_menu_bar::MainWindowMenuBar::~MainWindowMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar desstructor");

	// Delete menus
	delete this->fileMenu;
	delete this->editMenu;
}

void main_window_menu_bar::MainWindowMenuBar::fillMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Create menus");
	this->fileMenu = new file_menu::FileMenu(this->window, this, "File", Qt::Key_F);
	this->editMenu = new edit_menu::EditMenu(this->window, this, "Edit", Qt::Key_E);
}

file_menu::FileMenu * main_window_menu_bar::MainWindowMenuBar::getFileMenu() {
	return this->fileMenu;
}


edit_menu::EditMenu * main_window_menu_bar::MainWindowMenuBar::getEditMenu() {
	return this->editMenu;
}

