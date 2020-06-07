/**
 * @copyright
 * @file popup_properties.cpp
 * @author Andrea Gianarda
 * @date 21st of June 2020
 * @brief Popup properties functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QPainter>

#include <qt5/QtWidgets/QStyle>
#include <qt5/QtWidgets/QStyleOption>

#include "popup_properties.h"
#include "logging_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(popupPropertiesOverall, "popupProperties.overall", MSG_TYPE_LEVEL)

popup_properties::PopupProperties::PopupProperties(const bool & center, const int & sidePadding) : centered(center), padding(sidePadding) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, popupPropertiesOverall,  "Popup properties constructor");

}

popup_properties::PopupProperties::PopupProperties(const popup_properties::PopupProperties & rhs): centered(rhs.centered), padding(rhs.padding) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, popupPropertiesOverall,  "Copy constructor of popup properties");

}

popup_properties::PopupProperties & popup_properties::PopupProperties::operator=(const popup_properties::PopupProperties & rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, popupPropertiesOverall,  "Copy assignment operator of popup properties");

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

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, popupPropertiesOverall,  "Move constructor of popup properties");
}

popup_properties::PopupProperties & popup_properties::PopupProperties::operator=(popup_properties::PopupProperties && rhs) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, popupPropertiesOverall,  "Move assignment operator of popup properties");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->centered = std::exchange(rhs.centered, false);
		this->padding = std::exchange(rhs.padding, 0);
	}

	return *this;
}

popup_properties::PopupProperties::~PopupProperties() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, popupPropertiesOverall,  "Popup properties destructor");
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

