/**
 * @copyright
 * @file elided_label.cpp
 * @author Andrea Gianarda
 * @date 04th of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <QtGui/QPainter>

#include "app/utility/cpp/cpp_operator.h"
#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/widgets/text/elided_label.h"

// Categories
LOGGING_CONTEXT(elidedLabelOverall, elidedLabel.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(elidedLabelElision, elidedLabel.elision, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(elidedLabelPaint, elidedLabel.paint, TYPE_LEVEL, INFO_VERBOSITY)

app::text_widgets::ElidedLabel::ElidedLabel(QWidget * parent, Qt::WindowFlags flags, const QString & text, const QPoint & labelOrigin, const Qt::TextElideMode & textElisionMode) : QLabel(text, parent, flags), elisionMode(textElisionMode), origin(labelOrigin) {

	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelOverall, "Elided label constructor for text " << this->text() << " origin " << this->origin << " elision mode " << this->elisionMode);

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	this->updateElidedText(this->geometry().width());
}

app::text_widgets::ElidedLabel::~ElidedLabel() {
	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelOverall, "Elided label destructor");
}

void app::text_widgets::ElidedLabel::setText(const QString & text) {

	QLabel::setText(text);
	this->updateElidedText(this->geometry().width());

}

void app::text_widgets::ElidedLabel::updateElidedText(const int & width) {
	// If no elision or text is null, then set elision text to null
	if ((this->elisionMode == Qt::ElideNone) || (this->text() == QString())) {
		this->elisionText = QString();
		LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelElision, "Elided text is set to null");
	} else {
		this->elisionText = this->fontMetrics().elidedText(this->text(), this->elisionMode, width, Qt::TextShowMnemonic);
		LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelElision, "Unprocessed text is \"" << this->text() << "\" and elided text is set to " << this->elisionText);
	}
}

void app::text_widgets::ElidedLabel::resizeEvent(QResizeEvent * event) {
	QLabel::resizeEvent(event);

	const QSize size(event->size());
	this->updateElidedText(size.width());
}

void app::text_widgets::ElidedLabel::paintEvent(QPaintEvent * event) {
	LOG_INFO(app::logger::info_level_e::ZERO, elidedLabelPaint, "Paint text " << this->text() << " elision mode " << this->elisionMode);
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

CONST_SETTER_GETTER(app::text_widgets::ElidedLabel::setElisionMode, app::text_widgets::ElidedLabel::getElisionMode, Qt::TextElideMode &, this->elisionMode)
CONST_SETTER_GETTER(app::text_widgets::ElidedLabel::setOrigin, app::text_widgets::ElidedLabel::getOrigin, QPoint &, this->origin)
