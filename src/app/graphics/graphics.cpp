/**
 * @copyright
 * @file graphics.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Graphics functions
 */

#include <memory>

// Qt libraries
#include <QtWidgets/QApplication>

#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/windows/main_window/window/wrapper.h"
#include "app/graphics/graphics.h"
#include "app/utility/logger/logger.h"

// Categories
LOGGING_CONTEXT(graphicsOverall, graphics.overall, TYPE_LEVEL, INFO_VERBOSITY)

void graphics::init_graphics(int & argc, char** argv) {
	QApplication app(argc, argv);

	LOG_INFO(app::logger::info_level_e::ZERO, graphicsOverall,  "Create Application");

	std::unique_ptr<app::main_window::window::Wrapper> window = std::make_unique<app::main_window::window::Wrapper>(Q_NULLPTR, Qt::Window);
	window->show();

	app.exec();
}
