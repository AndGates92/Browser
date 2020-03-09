/**
 * @copyright
 * @file elided_label.cpp
 * @author Andrea Gianarda
 * @date 04th of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtGui/QPainter>

#include "elided_label.h"
#include "global_macros.h"
#include "global_types.h"

// Categories
Q_LOGGING_CATEGORY(elidedLabelOverall, "elidedLabel.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(elidedLabelElision, "elidedLabel.elision", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(elidedLabelPaint, "elidedLabel.paint", MSG_TYPE_LEVEL)

elided_label::ElidedLabel::ElidedLabel(QString textLabel, QPoint labelOrigin, QWidget * parent, Qt::WindowFlags flags, Qt::TextElideMode textElisionMode) : QLabel(textLabel, parent, flags), elisionMode(textElisionMode), origin(labelOrigin) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelOverall,  "Elided label constructor for text " << this->text() << " origin " << this->origin << " elision mode " << this->elisionMode);

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	this->updateElidedText(this->geometry().width());
}

elided_label::ElidedLabel::~ElidedLabel() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelOverall,  "Elided label destructor");
}

void elided_label::ElidedLabel::setText(const QString & text) {

	QLabel::setText(text);
	this->updateElidedText(this->geometry().width());

}

void elided_label::ElidedLabel::updateElidedText(const int width) {
	// If no elision or text is null, then set elision text to null
	if ((this->elisionMode == Qt::ElideNone) || (this->text() == QString::null)) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelElision,  "Elided text is set to null");
		this->elisionText = QString::null;
	} else {
		this->elisionText = this->fontMetrics().elidedText(this->text(), this->elisionMode, width, Qt::TextShowMnemonic);
	}
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelElision,  "Elided text is set to " << this->elisionText);
}

void elided_label::ElidedLabel::resizeEvent(QResizeEvent * event) {
	QLabel::resizeEvent(event);

	const QSize size(event->size());
	this->updateElidedText(size.width());
}

void elided_label::ElidedLabel::paintEvent(QPaintEvent * event) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelPaint,  "Paint text " << this->text() << " elision mode " << this->elisionMode);
	if (this->elisionMode == Qt::ElideNone) {
		QLabel::paintEvent(event);
	} else {
		event->accept();
		QPainter textPainter(this);
		const QRect dimensions = this->geometry();
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelPaint, "Drawing elided text " << this->elisionText);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelPaint, "Origin " << this->origin);
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, elidedLabelPaint, "Dimensions width " << dimensions.width() << " height " << dimensions.height());
		textPainter.drawText(this->origin.x(), this->origin.y(), dimensions.width(), dimensions.height(), this->alignment(), this->elisionText);
	}
}
