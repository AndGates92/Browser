/**
 * @copyright
 * @file label_popup.cpp
 * @author Andrea Gianarda
 * @date 13th of August 2020
 * @brief Label Popup functions
 */

#include <string>

// Qt libraries
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>

#include <QtGui/QKeyEvent>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QApplication>

#include "utility/logger/include/macros.h"
#include "common/include/global_enums.h"
#include "windows/main_window/popup/include/label_popup.h"
#include "common/include/exception_macros.h"


// Categories
LOGGING_CONTEXT(labelPopupOverall, labelPopup.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace label_popup {

	namespace {
		/**
		 * @brief default origin of text in label popup
		 *
		 */
		static const QPoint textOrigin(0,0);

		/**
		 * @brief popup menu padding
		 *
		 */
		static constexpr int padding = 15;

		/**
		 * @brief Spacing between widgets
		 *
		 */
		static constexpr int widgetSpacing = 2;

		/**
		 * @brief Top margin of the layout
		 *
		 */
		static constexpr int topMargin = 10;

		/**
		 * @brief Bottom margin of the layout
		 *
		 */
		static constexpr int bottomMargin = 10;

		/**
		 * @brief Left margin of the layout
		 *
		 */
		static constexpr int leftMargin = 10;

		/**
		 * @brief Right margin of the layout
		 *
		 */
		static constexpr int rightMargin = 10;

		/**
		 * @brief Duration of the popup in milliseconds
		 *
		 */
		static constexpr std::chrono::seconds duration = std::chrono::seconds(4);
	}

}

label_popup::LabelPopup::LabelPopup(QWidget * parent, Qt::WindowFlags flags) : main_window::PopupBase(parent, true, label_popup::padding, flags) {

	LOG_INFO(logger::info_level_e::ZERO, labelPopupOverall,  "Creating label popup");

	// Create widgets to put in the window
	this->fillPopup();

	// define window layout
	this->popupLayout();

	// Connect signals and slots
	this->connectSignals();

	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	this->setFocusPolicy(Qt::NoFocus);

	this->setStyleSheet(
		"QLabel {"
			"color: black;"
		"}"
	);
}

label_popup::LabelPopup::~LabelPopup() {
	LOG_INFO(logger::info_level_e::ZERO, labelPopupOverall,  "Destructor of label popup class");
}

void label_popup::LabelPopup::popupLayout() {

	if (this->layout() == Q_NULLPTR) {
		// Layout
		QVBoxLayout * layout = new QVBoxLayout(this);
		layout->setSpacing(label_popup::widgetSpacing);
		layout->setContentsMargins(label_popup::leftMargin, label_popup::topMargin, label_popup::rightMargin, label_popup::bottomMargin);

		this->setLayout(layout);
	}

	try {
		// Remove all widgets in the layout in order to redraw it
		QVBoxLayout * layout = dynamic_cast<QVBoxLayout *>(this->layout());
		const int layoutSize = layout->count();
		for (int idx = 0; idx < layoutSize; idx++) {
			QLayoutItem * item(layout->takeAt(idx));

			if (item != nullptr) {
				QWidget * itemWidget = item->widget();
				// If item manages a widget, then itemWidget will not be null
				if (item->widget() == nullptr) {
					layout->removeItem(item);
				} else {
					layout->removeWidget(itemWidget);
				}
				delete item;
			}
		}

		// Add widgets
		layout->addWidget(this->label.get(), 0, Qt::AlignTop);

	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}

}

void label_popup::LabelPopup::fillPopup() {

	this->label = std::make_unique<elided_label::ElidedLabel>(this, this->windowFlags(), QString(), label_popup::textOrigin, Qt::ElideRight);
	this->label->setTextFormat(Qt::PlainText);

	// font
	QFont labelFont(label->font());
	labelFont.setBold(true);
	this->label->setFont(labelFont);

	this->timer = std::make_unique<QTimer>(this);
}

void label_popup::LabelPopup::connectSignals() {
	LOG_INFO(logger::info_level_e::ZERO, labelPopupOverall,  "Connect signals");

	connect(this->timer.get(), &QTimer::timeout, [this] () {
		this->close();
	});

}

void label_popup::LabelPopup::setLabelText(const QString & text) {
	this->label->setText(text);
}

void label_popup::LabelPopup::activatePopup() {

	this->timer->start(label_popup::duration);

}

QSize label_popup::LabelPopup::sizeHint() const {

	// Width of the widget is the one of its geometry
	const int width = this->geometry().width();
	const int height = QWidget::sizeHint().height();

	QSize hint(width,height);

	return hint;
}

void label_popup::LabelPopup::close() {

	// Make popup container invisible
	QWidget * parent(this->parentWidget());
	parent->setVisible(false);

	// Give focus back to the window
	this->window()->setFocus();
}
