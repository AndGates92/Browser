/**
 * @copyright
 * @file global_classes.cpp
 * @author Andrea Gianarda
 * @date 31st of Mqrch 2020
 * @brief Global class definition
 */

#include "global_classes.h"

bool global_classes::StringCompare::operator() (const std::string & rhs, const std::string & lhs) const {
		return (rhs.compare(lhs) < 0);
}
