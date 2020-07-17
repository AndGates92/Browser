/**
 * @copyright
 * @file global_enums.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Global Types functions
 */

#include <iostream>

#include <qt5/QtCore/QTextStream>

#include "type_print_macros.h"
#include "global_enums.h"

namespace global_enums {

	OVERLOAD_OPERATORS_CUSTOM_TYPE(global_enums::qinfo_level_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(global_enums::sign_e)

	// Overload << operator for offset_type_e
	OVERLOAD_OPERATORS_CUSTOM_TYPE(global_enums::offset_type_e)

}
