/**
 * @copyright
 * @file overlayed_widget.cpp
 * @author Andrea Gianarda
 * @date 19th of June 2020
 * @brief Overlayed widget functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QPainter>

#include <qt5/QtWidgets/QStyle>
#include <qt5/QtWidgets/QStyleOption>

#include "overlayed_widget.h"
#include "logging_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(overlayedWidgetOverall, "overlayedWidget.overall", MSG_TYPE_LEVEL)

overlayed_widget::OverlayedWidget::OverlayedWidget(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, overlayedWidgetOverall,  "Overlayed widget constructor");

}

overlayed_widget::OverlayedWidget::~OverlayedWidget() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, overlayedWidgetOverall,  "Overlayed widget destructor");
}

void overlayed_widget::OverlayedWidget::paintEvent(QPaintEvent * event) {
	QStyleOption styleOption;
	styleOption.init(this);

	QPainter painter(this);
	QStyle::PrimitiveElement primitiveElement = QStyle::PE_Widget;
	this->style()->drawPrimitive(primitiveElement, &styleOption, &painter, this);

	QWidget::paintEvent(event);
}

void overlayed_widget::OverlayedWidget::setGeometry(const QRect & rect) {

	QWidget::setGeometry(rect);

	// Widgets should occupy the fill size of the popup container, hence pass the new geometry down to them
	const QList<QWidget *> widgets = this->findChildren<QWidget *>();
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			widget->setGeometry(rect);
			widget->updateGeometry();
		}
	}


}
