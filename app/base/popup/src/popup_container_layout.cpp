/**
 * @copyright
 * @file popup_container_layout.cpp
 * @author Andrea Gianarda
 * @date 14th of August 2020
 * @brief Popup container layout menu functions
 */

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtWidgets/QWidget>

#include "popup_container_layout.h"
#include "logging_macros.h"

// Categories
Q_LOGGING_CATEGORY(popupContainerLayoutOverall, "popupContainerLayout.overall", MSG_TYPE_LEVEL)

popup_container_layout::PopupContainerLayout::PopupContainerLayout(QWidget * parent) : QStackedLayout(parent) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, popupContainerLayoutOverall,  "Popup container layout constructor");

}

popup_container_layout::PopupContainerLayout::~PopupContainerLayout() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, popupContainerLayoutOverall,  "Popup container layout destructor");
}

QSize popup_container_layout::PopupContainerLayout::sizeHint() const {

	QWidget * widget = this->currentWidget();

	QSize hint(0,0);
	if (widget != Q_NULLPTR) {
		hint = widget->sizeHint();
	}

	return hint;
}
