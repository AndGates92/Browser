/**
 * @copyright
 * @file file_menu.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief File Menu functions
 */

// Qt libraries
#include <QtCore/QObject>

#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/windows/main_window/menu/file_menu.h"

// Categories
LOGGING_CONTEXT(fileMenuOverall, fileMenu.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(fileMenuOpenAction, fileMenu.openAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(fileMenuOpenTabAction, fileMenu.openTabAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(fileMenuSaveAction, fileMenu.saveAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(fileMenuPrintAction, fileMenu.printAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(fileMenuExitAction, fileMenu.exitAction, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::menu::FileMenu::FileMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const app::key_sequence::KeySequence & key) : app::base::menu::Menu(parent,menuBar,menuName,key), openWindow(Q_NULLPTR) {

	LOG_INFO(app::logger::info_level_e::ZERO, fileMenuOverall,  "Creating file menu");
	this->createActions();
	this->createMenu();

}

app::main_window::menu::FileMenu::~FileMenu() {

	LOG_INFO(app::logger::info_level_e::ZERO, fileMenuOverall,  "file menu destructor");

}

void app::main_window::menu::FileMenu::createActions() {

	this->openAction = std::make_unique<QAction>(tr("Open"), this);
	this->openAction->setStatusTip(tr("Open URL"));
	connect(this->openAction.get(), &QAction::triggered, this, &app::main_window::menu::FileMenu::open);

	this->openTabAction = std::make_unique<QAction>(tr("OpenTab"), this);
	this->openTabAction->setStatusTip(tr("Open Tab"));

	this->saveAction = std::make_unique<QAction>(tr("Save"), this);
	this->saveAction->setStatusTip(tr("Save"));
	connect(this->saveAction.get(), &QAction::triggered, this, &app::main_window::menu::FileMenu::save);

	this->printAction = std::make_unique<QAction>(tr("Print"), this);
	this->printAction->setStatusTip(tr("Print"));
	connect(this->printAction.get(), &QAction::triggered, this, &app::main_window::menu::FileMenu::print);

	this->exitAction = std::make_unique<QAction>(tr("Exit"), this);
	this->exitAction->setStatusTip(tr("Exit"));

}

void app::main_window::menu::FileMenu::createMenu() {
	this->winMenu->addAction(openAction.get());
	this->winMenu->addAction(openTabAction.get());
	this->winMenu->addAction(saveAction.get());
	this->winMenu->addAction(printAction.get());
	this->winMenu->addAction(exitAction.get());
}

void app::main_window::menu::FileMenu::open() {
	LOG_INFO(app::logger::info_level_e::ZERO, fileMenuOpenAction,  "Open slot: connect signal from open window to slot seding signal to the main window");

	this->openWindow.reset(new app::open_window::Window(this->parentWidget(), Qt::Window));
	connect(this->openWindow.get(), &app::open_window::Window::fileRead, this, &app::main_window::menu::FileMenu::updateCenterWindow);
	this->openWindow->show();
	this->openWindow->setFocus();
}

void app::main_window::menu::FileMenu::save() {
	LOG_INFO(app::logger::info_level_e::ZERO, fileMenuSaveAction,  "Save slot: saving web page to disk");

}

void app::main_window::menu::FileMenu::print() {
	LOG_INFO(app::logger::info_level_e::ZERO, fileMenuPrintAction,  "Print slot: printing web page");

}

void app::main_window::menu::FileMenu::updateCenterWindow(const QString & contentSource, const void * data) const {
	LOG_INFO(app::logger::info_level_e::ZERO, fileMenuOpenAction,  "Send signal to main window to update the center window");
	emit this->updateCenterWindowSignal(contentSource, data);
}
