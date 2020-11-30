/**
 * @copyright
 * @file enums.cpp
 * @author Andrea Gianarda
 * @date 02nd November 2020
 * @brief Logger enumeration functions
 */

#include <iostream>

#include "app/utility/logger/enums.h"

namespace app {

	namespace logger {

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::logger::info_level_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::logger::msg_type_e)

		OVERLOAD_OPERATORS_CUSTOM_TYPE(app::logger::state_e)

	}

}
