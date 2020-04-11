/**
 * @copyright
 * @file tab_shared_types.cpp
 * @author Andrea Gianarda
 * @date 11th of April 2020
 * @brief Tab Shared Types functions
 */

#include <iostream>

#include <qt5/QtCore/QTextStream>

#include "type_print_macros.h"
#include "tab_shared_types.h"

namespace tab_shared_types {

	// Overload << operator for offset_type_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(tab_shared_types::load_status_e)

}

