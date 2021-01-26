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

#include "app/base/popup/popup_properties.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"

// Categories
LOGGING_CONTEXT(popupPropertiesOverall, popupProperties.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::popup::PopupProperties::PopupProperties(const bool & center, const int & sidePadding) : centered(center), padding(sidePadding) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupPropertiesOverall, "Popup properties constructor");

}

app::base::popup::PopupProperties::PopupProperties(const app::base::popup::PopupProperties & rhs): centered(rhs.centered), padding(rhs.padding) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupPropertiesOverall, "Copy constructor of popup properties");

}

app::base::popup::PopupProperties & app::base::popup::PopupProperties::operator=(const app::base::popup::PopupProperties & rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupPropertiesOverall, "Copy assignment operator of popup properties");

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

app::base::popup::PopupProperties::PopupProperties(app::base::popup::PopupProperties && rhs): centered(std::exchange(rhs.centered, false)), padding(std::exchange(rhs.padding, 0)) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupPropertiesOverall, "Move constructor of popup properties");
}

app::base::popup::PopupProperties & app::base::popup::PopupProperties::operator=(app::base::popup::PopupProperties && rhs) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupPropertiesOverall, "Move assignment operator of popup properties");

	// If rhs points to the same address as this, then return this
	if (&rhs != this) {
		this->centered = std::exchange(rhs.centered, false);
		this->padding = std::exchange(rhs.padding, 0);
	}

	return *this;
}

app::base::popup::PopupProperties::~PopupProperties() {
	LOG_INFO(app::logger::info_level_e::ZERO, popupPropertiesOverall, "Popup properties destructor");
}

bool app::base::popup::PopupProperties::isCentered() const {
	return this->centered;
}

int app::base::popup::PopupProperties::getPadding() const {
	return this->padding;
}

void app::base::popup::PopupProperties::setPadding(const int & sidePadding) {
	this->padding = sidePadding;
}

void app::base::popup::PopupProperties::setCentered(const bool & center) {
	this->centered = center;
}

