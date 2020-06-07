/**
 * @copyright
 * @file global_types.cpp
 * @author Andrea Gianarda
 * @date 07th of June 2020
 * @brief Global Types functions
 */

#include <iostream>

#include <qt5/QtCore/QTextStream>

#include "type_print_macros.h"
#include "global_types.h"

namespace global_types {

	OVERLOAD_OPERATORS_CUSTOM_TYPE(global_types::qinfo_level_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(global_types::sign_e)

}
