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
Q_LOGGING_CATEGORY(editMenuOverall, "editNemu.overall", MSG_TYPE_LEVEL)

edit_menu::EditMenu::EditMenu(QWidget * window, QMenuBar * menuBar, const char* menuName, const QKeySequence & key) : menu::Menu(window,menuBar,menuName,key) {

	this->createActions();
	this->createMenu();

}

void edit_menu::EditMenu::createActions() {

	this->undoAction = new QAction(tr("Undo"), this);
	this->undoAction->setStatusTip(tr("Undo previous action"));
	connect(this->undoAction, &QAction::triggered, this, &EditMenu::undoSlot);

}

void edit_menu::EditMenu::createMenu() {
	this->winMenu->addAction(undoAction);
}

void edit_menu::EditMenu::undoSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, editMenuOverall,  "undo slot");
}
