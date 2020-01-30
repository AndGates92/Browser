/**
 * @copyright
 * @file main_window_core.cpp
 * @author Andrea Gianarda
 * @date 30th January 2020
 * @brief Main Window core functions
 */

#include <iostream>
// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>

#include "main_window_core.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowCoreOverall, "mainWindowCore.overall", MSG_TYPE_LEVEL)

main_window_core::MainWindowCore::MainWindowCore() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core constructor");

}

main_window_core::MainWindowCore::~MainWindowCore() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCoreOverall,  "Main window core destructor");

	// Delete menus
	delete this->fileMenu;
	delete this->editMenu;
	delete this->cmdMenu;

	// Label
	delete this->userInputText;
	delete this->websiteText;
	delete this->infoText;

	// Main components
	delete this->tabs;

	// Main widget
	delete this->mainWidget;
}
