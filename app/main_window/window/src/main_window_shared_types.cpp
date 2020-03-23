/**
 * @copyright
 * @file main_window_shared_types.cpp
 * @author Andrea Gianarda
 * @date 21st December 2019
 * @brief Main Window Shared Types functions
 */

#include <iostream>

#include <qt5/QtCore/QTextStream>

#include "type_print_macros.h"
#include "main_window_shared_types.h"

namespace main_window_shared_types {

	// Overload << operator for offset_type_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::offset_type_e)

	// Overload << operator for state_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::state_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::text_action_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(main_window_shared_types::tab_type_e)

}

