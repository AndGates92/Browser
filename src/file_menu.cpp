/**
 * @copyright
 * @file file_menu.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief File Menu functions
 */

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "open_button_window.h"
#include "file_menu.h"


// Categories
Q_LOGGING_CATEGORY(fileMenuOverall, "fileMenu.overall", MSG_TYPE_LEVEL)

file_menu::FileMenu::FileMenu(QWidget * window, QMenuBar * menuBar) : menu::Menu(window,menuBar,"File") {

	this->createActions();
	this->createMenu();

}

void file_menu::FileMenu::createActions() {

	this->openAction = new QAction(tr("Open"), this);
	this->openAction->setStatusTip(tr("Open URL"));
	connect(this->openAction, &QAction::triggered, this, &file_menu::FileMenu::openSlot);

}

void file_menu::FileMenu::createMenu() {

	menu::Menu::createMenu();

//	this->winMenu = this->menuBar->addMenu(tr("File"));
	this->winMenu->addAction(openAction);

}

void file_menu::FileMenu::openSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOverall,  "open slot");

	open_button_window::OpenButtonWindow OpenWindow(this->window, Qt::Dialog);
	OpenWindow.exec();
}
