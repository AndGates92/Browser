/**
 * @copyright
 * @file stl_helper.cpp
 * @author Andrea Gianarda
 * @date 06th of October 2020
 * @brief STL Helper
 */

#include "utility/stl/include/stl_helper.h"

const std::string app::utility::findAndReplaceString(std::string text, const std::string & searchString, const std::string & replacingString) {

	if (searchString.empty() == false) {
		std::size_t position = 0;
		while ((position != std::string::npos) && (position < text.size())) {
			position = text.find(searchString, position);
			if (position != std::string::npos) {
				if (replacingString.empty() == true) {
					text.erase(position, searchString.size());
				} else {
					text.replace(position, searchString.size(), replacingString);
				}
				position++;
			}
		}
	}

	return text;
}


