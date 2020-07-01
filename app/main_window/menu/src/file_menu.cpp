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

#include "logging_macros.h"
#include "global_types.h"
#include "file_menu.h"

// Categories
Q_LOGGING_CATEGORY(fileMenuOverall, "fileMenu.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuOpenAction, "fileMenu.openAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuOpenTabAction, "fileMenu.openTabAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuSaveAction, "fileMenu.saveAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuPrintAction, "fileMenu.printAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(fileMenuExitAction, "fileMenu.exitAction", MSG_TYPE_LEVEL)

file_menu::FileMenu::FileMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key) : menu::Menu(parent,menuBar,menuName,key) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOverall,  "Creating file menu");
	this->createActions();
	this->createMenu();

}

file_menu::FileMenu::~FileMenu() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOverall,  "file menu destructor");

}

void file_menu::FileMenu::createActions() {

	this->openAction = std::make_unique<QAction>(tr("Open"), this);
	this->openAction->setStatusTip(tr("Open URL"));
	connect(this->openAction.get(), &QAction::triggered, this, &file_menu::FileMenu::open);

	this->openTabAction = std::make_unique<QAction>(tr("OpenTab"), this);
	this->openTabAction->setStatusTip(tr("Open Tab"));

	this->saveAction = std::make_unique<QAction>(tr("Save"), this);
	this->saveAction->setStatusTip(tr("Save"));
	connect(this->saveAction.get(), &QAction::triggered, this, &file_menu::FileMenu::save);

	this->printAction = std::make_unique<QAction>(tr("Print"), this);
	this->printAction->setStatusTip(tr("Print"));
	connect(this->printAction.get(), &QAction::triggered, this, &file_menu::FileMenu::print);

	this->exitAction = std::make_unique<QAction>(tr("Exit"), this);
	this->exitAction->setStatusTip(tr("Exit"));

}

void file_menu::FileMenu::createMenu() {
	this->winMenu->addAction(openAction.get());
	this->winMenu->addAction(openTabAction.get());
	this->winMenu->addAction(saveAction.get());
	this->winMenu->addAction(printAction.get());
	this->winMenu->addAction(exitAction.get());
}

void file_menu::FileMenu::open() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOpenAction,  "Open slot: connect signal from open window to slot seding signal to the main window");

	this->openWindow = std::make_unique<open_button_window::OpenButtonWindow>(this->parentWidget(), Qt::Window);
	connect(this->openWindow.get(), &open_button_window::OpenButtonWindow::fileRead, this, &file_menu::FileMenu::updateCenterWindow);
	this->openWindow->show();
	this->openWindow->setFocus();
}

void file_menu::FileMenu::save() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuSaveAction,  "Save slot: saving web page to disk");

}

void file_menu::FileMenu::print() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuPrintAction,  "Print slot: printing web page");

}

void file_menu::FileMenu::updateCenterWindow(const QString & contentSource, const void * data) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, fileMenuOpenAction,  "Send signal to main window to update the center window");
	emit this->updateCenterWindowSignal(contentSource, data);
}
