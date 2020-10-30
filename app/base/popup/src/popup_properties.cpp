/**
 * @copyright
 * @file popup_properties.cpp
 * @author Andrea Gianarda
 * @date 21st of June 2020
 * @brief Popup properties functions
*/

// Qt libraries
#include <QtGui/QPainter>
#include <QtWidgets/QStyle>
#include <QtWidgets/QStyleOption>

#include "popup_properties.h"
#include "macros.h"
#include "global_enums.h"

// Categories
LOGGING_CONTEXT(popupPropertiesOverall, popupProperties.overall, TYPE_LEVEL, INFO_VERBOSITY)

popup_properties::PopupProperties::PopupProperties(const bool & center, const int & sidePadding) : centered(center), padding(sidePadding) {

	LOG_INFO(logger::info_level_e::ZERO, popupPropertiesOverall,  "Popup properties constructor");

}

popup_properties::PopupProperties::PopupProperties(const popup_properties::PopupProperties & rhs): centered(rhs.centered), padding(rhs.padding) {

	LOG_INFO(logger::info_level_e::ZERO, popupPropertiesOverall,  "Copy constructor of popup properties");

}

popup_properties::PopupProperties & popup_properties::PopupProperties::operator=(const popup_properties::PopupProperties & rhs) {

	LOG_INFO(logger::info_level_e::ZERO, popupPropertiesOverall,  "Copy assignment operator of popup properties");

	// If rhs points to the same address as this, then return this
	if (&rhs == this) {
		return *this;
	}

	if (this->centered == rhs.centered) {
		this->centered = rhs.centered;
	}
	if (this->padding == rhs.padding) {
		this->padding = rhs.padding;
	}

	return *this;
}

popup_properties::PopupProperties::PopupProperties(popup_properties::PopupProperties && rhs): centered(std::exchange(rhs.centered, false)), padding(std::exchange(rhs.padding, 0)) {

	LOG_INFO(logger::info_level_e::ZERO, popupPropertiesOverall,  "Move constructor of popup properties");
}

popup_properties::PopupProperties & popup_properties::PopupProperties::operator=(popup_properties::PopupProperties && rhs) {

	LOG_INFO(logger::info_level_e::ZERO, popupPropertiesOverall,  "Move assignment operator of popup properties");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->centered = std::exchange(rhs.centered, false);
		this->padding = std::exchange(rhs.padding, 0);
	}

	return *this;
}

popup_properties::PopupProperties::~PopupProperties() {
	LOG_INFO(logger::info_level_e::ZERO, popupPropertiesOverall,  "Popup properties destructor");
}

bool popup_properties::PopupProperties::isCentered() const {
	return this->centered;
}

int popup_properties::PopupProperties::getPadding() const {
	return this->padding;
}

void popup_properties::PopupProperties::setPadding(const int & sidePadding) {
	this->padding = sidePadding;
}

void popup_properties::PopupProperties::setCentered(const bool & center) {
	this->centered = center;
}

