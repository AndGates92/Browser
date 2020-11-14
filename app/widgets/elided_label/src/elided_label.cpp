/**
 * @copyright
 * @file elided_label.cpp
 * @author Andrea Gianarda
 * @date 04th of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <QtGui/QPainter>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/function_macros.h"
#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "widgets/elided_label/include/elided_label.h"

// Categories
LOGGING_CONTEXT(elidedLabelOverall, elidedLabel.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(elidedLabelElision, elidedLabel.elision, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(elidedLabelPaint, elidedLabel.paint, TYPE_LEVEL, INFO_VERBOSITY)

app::elided_label::ElidedLabel::ElidedLabel(QWidget * parent, Qt::WindowFlags flags, const QString & textLabel, const QPoint & labelOrigin, const Qt::TextElideMode & textElisionMode) : QLabel(textLabel, parent, flags), elisionMode(textElisionMode), origin(labelOrigin) {

	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelOverall,  "Elided label constructor for text " << this->text() << " origin " << this->origin << " elision mode " << this->elisionMode);

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	this->updateElidedText(this->geometry().width());
}

app::elided_label::ElidedLabel::~ElidedLabel() {
	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelOverall,  "Elided label destructor");
}

void app::elided_label::ElidedLabel::setText(const QString & text) {

	QLabel::setText(text);
	this->updateElidedText(this->geometry().width());

}

void app::elided_label::ElidedLabel::updateElidedText(const int & width) {
	// If no elision or text is null, then set elision text to null
	if ((this->elisionMode == Qt::ElideNone) || (this->text() == QString())) {
		LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelElision,  "Elided text is set to null");
		this->elisionText = QString();
	} else {
		this->elisionText = this->fontMetrics().elidedText(this->text(), this->elisionMode, width, Qt::TextShowMnemonic);
	}
	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelElision,  "Elided text is set to " << this->elisionText);
}

void app::elided_label::ElidedLabel::resizeEvent(QResizeEvent * event) {
	QLabel::resizeEvent(event);

	const QSize size(event->size());
	this->updateElidedText(size.width());
}

void app::elided_label::ElidedLabel::paintEvent(QPaintEvent * event) {
	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelPaint,  "Paint text " << this->text() << " elision mode " << this->elisionMode);
	if (this->elisionMode == Qt::ElideNone) {
		QLabel::paintEvent(event);
	} else {
		event->accept();
		QPainter textPainter(this);
		const QRect dimensions = this->geometry();
		LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelPaint, "Drawing elided text " << this->elisionText);
		LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelPaint, "Origin " << this->origin);
		LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelPaint, "Dimensions width " << dimensions.width() << " height " << dimensions.height());
		textPainter.drawText(this->origin.x(), this->origin.y(), dimensions.width(), dimensions.height(), this->alignment(), this->elisionText);
	}

}

CONST_SETTER_GETTER(app::elided_label::ElidedLabel::setElisionMode, app::elided_label::ElidedLabel::getElisionMode, Qt::TextElideMode &, this->elisionMode)
CONST_SETTER_GETTER(app::elided_label::ElidedLabel::setOrigin, app::elided_label::ElidedLabel::getOrigin, QPoint &, this->origin)
