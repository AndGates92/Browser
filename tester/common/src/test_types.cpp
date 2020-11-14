/**
 * @copyright
 * @file test_enums.cpp
 * @author Andrea Gianarda
 * @date 14th of September 2020
 * @brief Tester Types functions
 */

#include <iostream>

#include <QtCore/QTextStream>

#include "common/include/type_print_macros.h"
#include "common/include/test_enums.h"

namespace test_enums {

	OVERLOAD_OPERATORS_CUSTOM_TYPE(test_enums::error_type_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(test_enums::test_state_e)

	OVERLOAD_OPERATORS_CUSTOM_TYPE(test_enums::test_status_e)

}
