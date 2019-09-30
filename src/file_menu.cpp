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
#include "file_menu.h"

// Categories
Q_LOGGING_CATEGORY(fileMenuOverall, "fileMenu.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuOpenAction, "fileMenu.openAction", MSG_TYPE_LEVEL)

file_menu::FileMenu::FileMenu(QWidget * window, QMenuBar * menuBar, const char* menuName, const QKeySequence & key) : menu::Menu(window,menuBar,menuName,key) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOverall,  "Creating file menu");
	this->createActions();
	this->createMenu();

}

void file_menu::FileMenu::createActions() {

	this->openAction = new QAction(tr("Open"), this);
	this->openAction->setStatusTip(tr("Open URL"));
	connect(this->openAction, &QAction::triggered, this, &file_menu::FileMenu::openSlot);

}

void file_menu::FileMenu::createMenu() {
	this->winMenu->addAction(openAction);
}

void file_menu::FileMenu::openSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOpenAction,  "Open slot: connect signal from open window to slot seding signal to the main window");

	this->openWindow = new open_button_window::OpenButtonWindow(this->window, Qt::Dialog);
	connect(this->openWindow, &open_button_window::OpenButtonWindow::fileRead, this, &file_menu::FileMenu::updateCenterWindowSlot);
	this->openWindow->exec();
}

void file_menu::FileMenu::updateCenterWindowSlot(QString & content) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOpenAction,  "Send signal to main window to update the center window");
	emit this->updateCenterWindow(content);
}
