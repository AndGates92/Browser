/**
 * @copyright
 * @file popup_container_layout.cpp
 * @author Andrea Gianarda
 * @date 14th of August 2020
 * @brief Popup container layout menu functions
 */

// Qt libraries
#include <QtWidgets/QWidget>

#include "base/popup/include/popup_container_layout.h"
#include "utility/logger/include/macros.h"

// Categories
LOGGING_CONTEXT(popupContainerLayoutOverall, popupContainerLayout.overall, TYPE_LEVEL, INFO_VERBOSITY)

popup_container_layout::PopupContainerLayout::PopupContainerLayout(QWidget * parent) : QStackedLayout(parent) {

	LOG_INFO(logger::info_level_e::ZERO, popupContainerLayoutOverall,  "Popup container layout constructor");

}

popup_container_layout::PopupContainerLayout::~PopupContainerLayout() {
	LOG_INFO(logger::info_level_e::ZERO, popupContainerLayoutOverall,  "Popup container layout destructor");
}

QSize popup_container_layout::PopupContainerLayout::sizeHint() const {

	QWidget * widget = this->currentWidget();

	QSize hint(0,0);
	if (widget != Q_NULLPTR) {
		hint = widget->sizeHint();
	}

	return hint;
}
