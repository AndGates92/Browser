/**
 * @copyright
 * @file command_menu_model.cpp
 * @author Andrea Gianarda
 * @date 24th January 2020
 * @brief Command menu model functions
 */

#include "app/utility/logger/macros.h"
#include "app/widgets/command_menu/command_menu_model.h"

// Categories
LOGGING_CONTEXT(commandMenuModelOverall, commandMenuModel.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(commandMenuModelSettings, commandMenuModel.settings, TYPE_LEVEL, INFO_VERBOSITY)

app::command_menu::CommandMenuModel::CommandMenuModel(QObject * parent) : QAbstractItemModel(parent) {

	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuModelOverall, "Create command menu model");
}

app::command_menu::CommandMenuModel::~CommandMenuModel() {
	LOG_INFO(app::logger::info_level_e::ZERO, commandMenuModelOverall, "Destoy command menu model");

}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
QModelIndex app::command_menu::CommandMenuModel::index(int row, int column, const QModelIndex & parent) const {

	return QModelIndex();
}

QModelIndex app::command_menu::CommandMenuModel::parent(const QModelIndex & child) const {

	return QModelIndex();
}

int app::command_menu::CommandMenuModel::rowCount(const QModelIndex & parent) const {

	return 0;
}

int app::command_menu::CommandMenuModel::columnCount(const QModelIndex & parent) const {

	return 0;
}

QVariant app::command_menu::CommandMenuModel::data(const QModelIndex & index, int role) const {

	return QVariant();
}
#pragma GCC diagnostic pop
