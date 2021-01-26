/**
 * @copyright
 * @file edit_menu.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Edit Menu functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMenuBar>

#include "app/utility/logger/macros.h"
#include "app/windows/main_window/menu/edit_menu.h"
#include "app/windows/secondary_windows/find_window/window.h"

// Categories
LOGGING_CONTEXT(editMenuOverall, editMenu.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuUndoAction, editMenu.undoAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuRedoAction, editMenu.redoAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuCutAction, editMenu.cutAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuCopyAction, editMenu.copyAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuPasteAction, editMenu.pasteAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuSelectAllAction, editMenu.selectAllAction, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(editMenuFindAction, editMenu.findAction, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::menu::EditMenu::EditMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const app::commands::KeySequence & key) : app::base::menu::Menu(parent,menuBar,menuName,key), findWindow(Q_NULLPTR) {

	LOG_INFO(app::logger::info_level_e::ZERO, editMenuOverall, "edit menu constructor");

	this->createActions();
	this->createMenu();

}

app::main_window::menu::EditMenu::~EditMenu() {

	LOG_INFO(app::logger::info_level_e::ZERO, editMenuOverall, "edit menu destructor");

}

void app::main_window::menu::EditMenu::createActions() {

	this->undoAction = std::make_unique<QAction>(tr("Undo"), this);
	this->undoAction->setStatusTip(tr("Undo previous action"));
	connect(this->undoAction.get(), &QAction::triggered, this, &EditMenu::undo);

	this->redoAction = std::make_unique<QAction>(tr("Redo"), this);
	this->redoAction->setStatusTip(tr("Redo action"));
	connect(this->redoAction.get(), &QAction::triggered, this, &EditMenu::redo);

	this->cutAction = std::make_unique<QAction>(tr("Cut"), this);
	this->cutAction->setStatusTip(tr("Cut action"));
	connect(this->cutAction.get(), &QAction::triggered, this, &EditMenu::cut);

	this->copyAction = std::make_unique<QAction>(tr("Copy"), this);
	this->copyAction->setStatusTip(tr("Copy action"));
	connect(this->copyAction.get(), &QAction::triggered, this, &EditMenu::copy);

	this->pasteAction = std::make_unique<QAction>(tr("Paste"), this);
	this->pasteAction->setStatusTip(tr("Paste action"));
	connect(this->pasteAction.get(), &QAction::triggered, this, &EditMenu::paste);

	this->selectAllAction = std::make_unique<QAction>(tr("Select All"), this);
	this->selectAllAction->setStatusTip(tr("Select All action"));
	connect(this->selectAllAction.get(), &QAction::triggered, this, &EditMenu::selectAll);

	this->findAction = std::make_unique<QAction>(tr("Find"), this);
	this->findAction->setStatusTip(tr("Find action"));
	connect(this->findAction.get(), &QAction::triggered, this, &EditMenu::find);

}

void app::main_window::menu::EditMenu::createMenu() {
	this->winMenu->addAction(undoAction.get());
	this->winMenu->addAction(redoAction.get());
	this->winMenu->addAction(cutAction.get());
	this->winMenu->addAction(copyAction.get());
	this->winMenu->addAction(pasteAction.get());
	this->winMenu->addAction(selectAllAction.get());
	this->winMenu->addAction(findAction.get());
}

void app::main_window::menu::EditMenu::undo() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuUndoAction, "undo slot");
}

void app::main_window::menu::EditMenu::redo() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuRedoAction, "redo slot");
}

void app::main_window::menu::EditMenu::cut() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuCutAction, "cut slot");
}

void app::main_window::menu::EditMenu::copy() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuCopyAction, "copy slot");
}

void app::main_window::menu::EditMenu::paste() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuPasteAction, "paste slot");
}

void app::main_window::menu::EditMenu::selectAll() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuSelectAllAction, "select all slot");
}

void app::main_window::menu::EditMenu::find() {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuFindAction, "setting up find functionality: creating window and connecting signals and slots");

	this->findWindow.reset(new app::find_window::Window(this->parentWidget(), Qt::Window));
	connect(this->findWindow.get(), &app::find_window::Window::find, this, &app::main_window::menu::EditMenu::doSearch);
	this->findWindow->show();
	this->findWindow->setFocus();
}

void app::main_window::menu::EditMenu::doSearch(const app::windows::shared::FindSettings settings) const {
	LOG_INFO(app::logger::info_level_e::ZERO, editMenuFindAction, "Search settings " << settings);
	emit this->triggerSearch(settings);
}
