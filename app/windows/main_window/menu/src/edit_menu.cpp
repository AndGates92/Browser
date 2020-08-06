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

#include "edit_menu.h"

// Categories
Q_LOGGING_CATEGORY(editMenuOverall, "editMenu.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuUndoAction, "editMenu.undoAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuRedoAction, "editMenu.redoAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuCutAction, "editMenu.cutAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuCopyAction, "editMenu.copyAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuPasteAction, "editMenu.pasteAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuSelectAllAction, "editMenu.selectAllAction", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuFindAction, "editMenu.findAction", MSG_TYPE_LEVEL)

edit_menu::EditMenu::EditMenu(QWidget * parent, std::weak_ptr<QMenuBar> menuBar, const char* menuName, const key_sequence::KeySequence & key) : menu::Menu(parent,menuBar,menuName,key), findWindow(Q_NULLPTR) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuOverall,  "edit menu constructor");

	this->createActions();
	this->createMenu();

}

edit_menu::EditMenu::~EditMenu() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuOverall,  "edit menu destructor");

}

void edit_menu::EditMenu::createActions() {

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

void edit_menu::EditMenu::createMenu() {
	this->winMenu->addAction(undoAction.get());
	this->winMenu->addAction(redoAction.get());
	this->winMenu->addAction(cutAction.get());
	this->winMenu->addAction(copyAction.get());
	this->winMenu->addAction(pasteAction.get());
	this->winMenu->addAction(selectAllAction.get());
	this->winMenu->addAction(findAction.get());
}

void edit_menu::EditMenu::undo() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuUndoAction,  "undo slot");
}

void edit_menu::EditMenu::redo() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuRedoAction,  "redo slot");
}

void edit_menu::EditMenu::cut() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuCutAction,  "cut slot");
}

void edit_menu::EditMenu::copy() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuCopyAction,  "copy slot");
}

void edit_menu::EditMenu::paste() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuPasteAction,  "paste slot");
}

void edit_menu::EditMenu::selectAll() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuSelectAllAction,  "select all slot");
}

void edit_menu::EditMenu::find() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuFindAction,  "setting up find functionality: creating window and connecting signals and slots");

	this->findWindow.reset(new find_button_window::FindButtonWindow(this->parentWidget(), Qt::Window));
	connect(this->findWindow.get(), &find_button_window::FindButtonWindow::find, this, &edit_menu::EditMenu::doSearch);
	this->findWindow->show();
	this->findWindow->setFocus();
}

void edit_menu::EditMenu::doSearch(const find_settings::FindSettings settings) const {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, editMenuFindAction,  "Search settings " << settings);
	emit this->triggerSearch(settings);
}
