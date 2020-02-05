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
Q_LOGGING_CATEGORY(fileMenuOpenTabAction, "fileMenu.openTabAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuSaveAction, "fileMenu.saveAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuPrintAction, "fileMenu.printAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuExitAction, "fileMenu.exitAction", MSG_TYPE_LEVEL)

file_menu::FileMenu::FileMenu(QWidget * window, QMenuBar * menuBar, const char* menuName, const QKeySequence & key) : menu::Menu(window,menuBar,menuName,key) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOverall,  "Creating file menu");
	this->createActions();
	this->createMenu();

}

file_menu::FileMenu::~FileMenu() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOverall,  "file menu destructor");

	delete this->openTabAction;
	delete this->saveAction;
	delete this->printAction;
	delete this->exitAction;

}

void file_menu::FileMenu::createActions() {

	this->openAction = new QAction(tr("Open"), this);
	this->openAction->setStatusTip(tr("Open URL"));
	connect(this->openAction, &QAction::triggered, this, &file_menu::FileMenu::open);

	this->openTabAction = new QAction(tr("OpenTab"), this);
	this->openTabAction->setStatusTip(tr("Open Tab"));

	this->saveAction = new QAction(tr("Save"), this);
	this->saveAction->setStatusTip(tr("Save"));
	connect(this->saveAction, &QAction::triggered, this, &file_menu::FileMenu::save);

	this->printAction = new QAction(tr("Print"), this);
	this->printAction->setStatusTip(tr("Print"));
	connect(this->printAction, &QAction::triggered, this, &file_menu::FileMenu::print);

	this->exitAction = new QAction(tr("Exit"), this);
	this->exitAction->setStatusTip(tr("Exit"));

}

void file_menu::FileMenu::createMenu() {
	this->winMenu->addAction(openAction);
	this->winMenu->addAction(openTabAction);
	this->winMenu->addAction(saveAction);
	this->winMenu->addAction(printAction);
	this->winMenu->addAction(exitAction);
}

void file_menu::FileMenu::open() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOpenAction,  "Open slot: connect signal from open window to slot seding signal to the main window");

	this->openWindow = new open_button_window::OpenButtonWindow(this->window, Qt::Dialog);
	connect(this->openWindow, &open_button_window::OpenButtonWindow::fileRead, this, &file_menu::FileMenu::updateCenterWindow);
	this->openWindow->exec();
}

void file_menu::FileMenu::save() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuSaveAction,  "Save slot: saving web page to disk");

}

void file_menu::FileMenu::print() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuPrintAction,  "Print slot: printing web page");

}

void file_menu::FileMenu::updateCenterWindow(const QString & title, const QString & content) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOpenAction,  "Send signal to main window to update the center window");
	emit this->updateCenterWindowSignal(title, content);
}
