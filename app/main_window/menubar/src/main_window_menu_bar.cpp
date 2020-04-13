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

main_window_menu_bar::MainWindowMenuBar::MainWindowMenuBar(QWidget * window) : menu_bar::MenuBar(window), fileMenu(new file_menu::FileMenu(this->parentWidget(), this, "File", Qt::Key_F)), editMenu(new edit_menu::EditMenu(this->parentWidget(), this, "Edit", Qt::Key_E)) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar constructor");

}

main_window_menu_bar::MainWindowMenuBar::~MainWindowMenuBar() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowMenuBarOverall,  "Main window menu bar destructor");

	// Delete menus
	delete this->fileMenu;
	delete this->editMenu;
}

PTR_GETTER(main_window_menu_bar::MainWindowMenuBar::getFileMenu, file_menu::FileMenu, this->fileMenu)
PTR_GETTER(main_window_menu_bar::MainWindowMenuBar::getEditMenu, edit_menu::EditMenu, this->editMenu)
