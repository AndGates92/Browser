/**
 * @copyright
 * @file command_menu_model.cpp
 * @author Andrea Gianarda
 * @date 24th January 2020
 * @brief Command menu model functions
 */

#include "logging_macros.h"
#include "command_menu_model.h"

// Categories
Q_LOGGING_CATEGORY(commandMenuModelOverall, "commandMenuModel.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(commandMenuModelSettings, "commandMenuModel.settings", MSG_TYPE_LEVEL)

command_menu_model::CommandMenuModel::CommandMenuModel(QObject * parent) : QAbstractItemModel(parent) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandMenuModelOverall,  "Create command menu model");
}

command_menu_model::CommandMenuModel::~CommandMenuModel() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, commandMenuModelOverall,  "Destoy command menu model");

}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
QModelIndex command_menu_model::CommandMenuModel::index(int row, int column, const QModelIndex & parent) const {

	return QModelIndex();
}

QModelIndex command_menu_model::CommandMenuModel::parent(const QModelIndex & child) const {

	return QModelIndex();
}

int command_menu_model::CommandMenuModel::rowCount(const QModelIndex & parent) const {

	return 0;
}

int command_menu_model::CommandMenuModel::columnCount(const QModelIndex & parent) const {

	return 0;
}

QVariant command_menu_model::CommandMenuModel::data(const QModelIndex & index, int role) const {

	return QVariant();
}
#pragma GCC diagnostic pop
