/**
 * @copyright
 * @file command_menu.cpp
 * @author Andrea Gianarda
 * @date 23th January 2020
 * @brief Command menu functions
 */

#include "global_macros.h"
#include "command_menu.h"

// Categories
Q_LOGGING_CATEGORY(commandMenuOverall, "commandMenu.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(commandMenuSettings, "commandMenu.settings", MSG_TYPE_LEVEL)

command_menu::CommandMenu::CommandMenu(QWidget * parent) : QAbstractItemView(parent) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, commandMenuOverall,  "Create command menu");
	this->setProperties();

	this->menuModel = new command_menu_model::CommandMenuModel(parent);

	this->setModel(this->menuModel);
}

command_menu::CommandMenu::~CommandMenu() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, commandMenuOverall,  "Destoy command menu");

	delete this->menuModel;
}

void command_menu::CommandMenu::setProperties() {

	// Set title
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, commandMenuSettings,  "Set title to command menu: " << command_menu::commandMenuTitle);
	this->setWindowTitle(command_menu::commandMenuTitle);

	// Edit trigger 
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, commandMenuSettings,  "Edit trigger: " << command_menu::editTrigger);
	this->setEditTriggers(command_menu::editTrigger);

	// Drag and drop mode
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, commandMenuSettings,  "Drag and drop mode: " << command_menu::dragDropMode);
	this->setDragDropMode(command_menu::dragDropMode);

	// Autoscroll
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, commandMenuSettings,  "Enable autoscroll: " << command_menu::autoScrollProp);
	this->setAutoScroll(command_menu::autoScrollProp);
}

void command_menu::CommandMenu::setModel(command_menu_model::CommandMenuModel * model) {
	// Call setModel from the base class
	QAbstractItemView::setModel(model);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
QRect command_menu::CommandMenu::visualRect(QModelIndex & index) const {

	return QRect();
}

void command_menu::CommandMenu::scrollTo(const QModelIndex & index, QAbstractItemView::ScrollHint hint) {

}

QModelIndex command_menu::CommandMenu::indexAt(const QPoint &point) const {

	return QModelIndex();
}

QModelIndex command_menu::CommandMenu::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers) {

	return QModelIndex();
}

int command_menu::CommandMenu::horizontalOffset() const {

	return 0;
}

int command_menu::CommandMenu::verticalOffset() const {

	return 0;
}

bool command_menu::CommandMenu::isIndexHidden(const QModelIndex &index) const {

	return false;
}

void command_menu::CommandMenu::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) {

}

QRegion command_menu::CommandMenu::visualRegionForSelection(const QItemSelection &selection) const {

	return QRegion();
}

QRect command_menu::CommandMenu::visualRect(const QModelIndex & index) const {

	return QRect();
}
#pragma GCC diagnostic pop
