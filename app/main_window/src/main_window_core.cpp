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

main_window_core::MainWindowCore::MainWindowCore() : mainWidget(Q_NULLPTR), tabs(Q_NULLPTR), fileMenu(Q_NULLPTR), editMenu(Q_NULLPTR), cmdMenu(Q_NULLPTR), userInputText(Q_NULLPTR), websiteText(Q_NULLPTR), infoText(Q_NULLPTR), mainWindowState(main_window_shared_types::state_e::IDLE), moveValueType(main_window_shared_types::move_value_e::IDLE), userText(QString::null) {

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

QString main_window_core::MainWindowCore::createTabInfo() {

	int tabCount = this->tabs->count();

	QString tabInfo(QString::null);
	if (tabCount == 0) {
		tabInfo.append("No tabs");
	} else {
		tabInfo.append("tab ");
		tabInfo.append(QString("%1").arg(this->tabs->currentIndex() + 1));
		tabInfo.append(" out of ");
		tabInfo.append(QString("%1").arg(tabCount));
	}

	return tabInfo;
}
