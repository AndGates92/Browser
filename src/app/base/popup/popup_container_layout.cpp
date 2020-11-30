/**
 * @copyright
 * @file popup_container_layout.cpp
 * @author Andrea Gianarda
 * @date 14th of August 2020
 * @brief Popup container layout menu functions
 */

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/base/popup/popup_container_layout.h"
#include "app/utility/logger/macros.h"

// Categories
LOGGING_CONTEXT(popupContainerLayoutOverall, popupContainerLayout.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::base::popup::PopupContainerLayout::PopupContainerLayout(QWidget * parent) : QStackedLayout(parent) {

	LOG_INFO(app::logger::info_level_e::ZERO, popupContainerLayoutOverall,  "Popup container layout constructor");

}

app::base::popup::PopupContainerLayout::~PopupContainerLayout() {
	LOG_INFO(app::logger::info_level_e::ZERO, popupContainerLayoutOverall,  "Popup container layout destructor");
}

QSize app::base::popup::PopupContainerLayout::sizeHint() const {

	QWidget * widget = this->currentWidget();

	QSize hint(0,0);
	if (widget != Q_NULLPTR) {
		hint = widget->sizeHint();
	}

	return hint;
}
