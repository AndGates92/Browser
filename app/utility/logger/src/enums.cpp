/**
 * @copyright
 * @file enums.cpp
 * @author Andrea Gianarda
 * @date 02nd November 2020
 * @brief Logger enumeration functions
 */

#include <iostream>

#include "enums.h"

namespace logger {

	OVERLOAD_OPERATORS_CUSTOM_TYPE(logger::info_level_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(logger::msg_type_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(logger::state_e)

}
