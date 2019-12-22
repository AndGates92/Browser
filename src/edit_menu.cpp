/**
 * @copyright
 * @file edit_menu.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Edit Menu functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWidgets/QAction>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtGui/QKeySequence>

#include "edit_menu.h"

// Categories
Q_LOGGING_CATEGORY(editMenuOverall, "editMenu.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(editMenuAction, "editMenu.action", MSG_TYPE_LEVEL)

edit_menu::EditMenu::EditMenu(QWidget * window, QMenuBar * menuBar, const char* menuName, const QKeySequence & key) : menu::Menu(window,menuBar,menuName,key) {

	this->createActions();
	this->createMenu();

}

void edit_menu::EditMenu::createActions() {

	this->undoAction = new QAction(tr("Undo"), this);
	this->undoAction->setStatusTip(tr("Undo previous action"));
	connect(this->undoAction, &QAction::triggered, this, &EditMenu::undo);

	this->redoAction = new QAction(tr("Redo"), this);
	this->redoAction->setStatusTip(tr("Redo action"));
	connect(this->redoAction, &QAction::triggered, this, &EditMenu::redo);

	this->cutAction = new QAction(tr("Cut"), this);
	this->cutAction->setStatusTip(tr("Cut action"));
	connect(this->cutAction, &QAction::triggered, this, &EditMenu::cut);

	this->copyAction = new QAction(tr("Copy"), this);
	this->copyAction->setStatusTip(tr("Copy action"));
	connect(this->copyAction, &QAction::triggered, this, &EditMenu::copy);

	this->pasteAction = new QAction(tr("Paste"), this);
	this->pasteAction->setStatusTip(tr("Paste action"));
	connect(this->pasteAction, &QAction::triggered, this, &EditMenu::paste);

	this->selectAllAction = new QAction(tr("Select All"), this);
	this->selectAllAction->setStatusTip(tr("Select All action"));
	connect(this->selectAllAction, &QAction::triggered, this, &EditMenu::selectAll);

	this->findAction = new QAction(tr("Find"), this);
	this->findAction->setStatusTip(tr("Find action"));
	connect(this->findAction, &QAction::triggered, this, &EditMenu::find);

}

void edit_menu::EditMenu::createMenu() {
	this->winMenu->addAction(undoAction);
	this->winMenu->addAction(redoAction);
	this->winMenu->addAction(cutAction);
	this->winMenu->addAction(copyAction);
	this->winMenu->addAction(pasteAction);
	this->winMenu->addAction(selectAllAction);
	this->winMenu->addAction(findAction);
}

void edit_menu::EditMenu::undo() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "undo slot");
}

void edit_menu::EditMenu::redo() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "redo slot");
}

void edit_menu::EditMenu::cut() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "cut slot");
}

void edit_menu::EditMenu::copy() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "copy slot");
}

void edit_menu::EditMenu::paste() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "paste slot");
}

void edit_menu::EditMenu::selectAll() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "select all slot");
}

void edit_menu::EditMenu::find() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuAction,  "find slot");
}
