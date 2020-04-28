/**
 * @copyright
 * @file main_window_menu_bar.cpp
 * @author Andrea Gianarda
 * @date 02nd of February 2020
 * @brief Main Window menu bar functions
 */

#include <iostream>
// Qt libraries
#include <qt5/QtCore/QtGlobal>

#include "main_window_menu_bar.h"
#include "global_types.h"
#include "function_macros.h"
#include "logging_macros.h"

Q_LOGGING_CATEGORY(mainWindowMenuBarOverall, "menuBar.overall", MSG_TYPE_LEVEL)

main_window_menu_bar::MainWindowMenuBar::MainWindowMenuBar(QWidget * parent) : menu_bar::MenuBar(parent), fileMenu(new file_menu::FileMenu(parent, this, "File", key_sequence::KeySequence(Qt::Key_F))), editMenu(new edit_menu::EditMenu(parent, this, "Edit", key_sequence::KeySequence(Qt::Key_E))) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar constructor");
}

main_window_menu_bar::MainWindowMenuBar::~MainWindowMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar destructor");

	// Delete menus
	if (this->fileMenu != Q_NULLPTR) {
		delete this->fileMenu;
	}

	if (this->fileMenu != Q_NULLPTR) {
		delete this->editMenu;
	}
}

PTR_GETTER(main_window_menu_bar::MainWindowMenuBar::getFileMenu, file_menu::FileMenu, this->fileMenu)
PTR_GETTER(main_window_menu_bar::MainWindowMenuBar::getEditMenu, edit_menu::EditMenu, this->editMenu)
