/**
 * @copyright
 * @file shared_types.cpp
 * @author Andrea Gianarda
 * @date 21st December 2019
 * @brief Main Window Shared Types functions
 */

#include <iostream>

#include <QtCore/QTextStream>

#include "common/include/type_print_macros.h"
#include "windows/main_window/common/include/shared_types.h"

namespace app {

	namespace main_window {

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::main_window::navigation_type_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::main_window::state_postprocessing_e)

		// Overload << operator for state_e
		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::main_window::state_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::main_window::text_action_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::main_window::page_type_e)

	}
}

