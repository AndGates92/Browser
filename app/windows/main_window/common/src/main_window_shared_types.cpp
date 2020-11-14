/**
 * @copyright
 * @file main_window_shared_types.cpp
 * @author Andrea Gianarda
 * @date 21st December 2019
 * @brief Main Window Shared Types functions
 */

#include <iostream>

#include <QtCore/QTextStream>

#include "common/include/type_print_macros.h"
#include "windows/main_window/common/include/main_window_shared_types.h"

namespace main_window_shared_types {

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::navigation_type_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::state_postprocessing_e)

	// Overload << operator for state_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::state_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::text_action_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::page_type_e)

}

