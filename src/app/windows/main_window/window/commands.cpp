/**
 * @copyright
 * @file commands.cpp
 * @author Andrea Gianarda
 * @date 13th December 2020
 * @brief Main window commands functions
 */

#include "app/utility/cpp/cpp_operator.h"
#include "app/windows/main_window/window/commands.h"

LOGGING_CONTEXT(mainWindowCommandsOverall, mainWindowCommands.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::window::Commands::Commands() : app::main_window::window::Commands(QString()) {

}

app::main_window::window::Commands::Commands(const QStringList jsonFiles) : app::main_window::json::Action(jsonFiles) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCommandsOverall,  "Creating main window commands with " << this->getActionJsonFilesAsString());
}

app::main_window::window::Commands::Commands(const QString jsonFile) : app::main_window::json::Action(jsonFile) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCommandsOverall,  "Creating main window commands with " << this->getActionJsonFilesAsString());
}

app::main_window::window::Commands::~Commands() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowCommandsOverall,  "Main window commands destructor");
}

void app::main_window::window::Commands::appendActionData(const QStringList & jsonFiles) {
	app::main_window::json::Action::appendActionData(jsonFiles);
}

void app::main_window::window::Commands::appendActionData(const QString & filename) {
	app::main_window::json::Action::appendActionData(filename);
}
