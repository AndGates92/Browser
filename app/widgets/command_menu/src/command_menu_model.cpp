/**
 * @copyright
 * @file command_menu_model.cpp
 * @author Andrea Gianarda
 * @date 24th January 2020
 * @brief Command menu model functions
 */

#include "utility/logger/include/macros.h"
#include "widgets/command_menu/include/command_menu_model.h"

// Categories
LOGGING_CONTEXT(commandMenuModelOverall, commandMenuModel.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuModelSettings, commandMenuModel.settings, TYPE_LEVEL, INFO_VERBOSITY)

command_menu_model::CommandMenuModel::CommandMenuModel(QObject * parent) : QAbstractItemModel(parent) {

	LOG_INFO(logger::info_level_e::ZERO, commandMenuModelOverall,  "Create command menu model");
}

command_menu_model::CommandMenuModel::~CommandMenuModel() {
	LOG_INFO(logger::info_level_e::ZERO, commandMenuModelOverall,  "Destoy command menu model");

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
