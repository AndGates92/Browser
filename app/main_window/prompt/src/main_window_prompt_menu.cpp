/**
 * @copyright
 * @file main_window_prompt_menu.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window prompt menu functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QHBoxLayout>

#include "main_window_prompt_menu.h"
#include "logging_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowPromptMenuOverall, "mainWindowPromptMenu.overall", MSG_TYPE_LEVEL)

main_window_prompt_menu::MainWindowPromptMenu::MainWindowPromptMenu(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowPromptMenuOverall,  "Main window prompt menu constructor");

}

main_window_prompt_menu::MainWindowPromptMenu::~MainWindowPromptMenu() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowPromptMenuOverall,  "Main window prompt menu destructor");

}
