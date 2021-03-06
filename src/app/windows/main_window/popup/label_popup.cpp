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

#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/windows/main_window/popup/label_popup.h"
#include "app/shared/exception.h"
#include "app/widgets/elided_label/elided_label.h"

// Categories
LOGGING_CONTEXT(labelPopupOverall, labelPopup.overall, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace popup {

			namespace label_popup {

				namespace {

					/**
					 * @brief default origin of text
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
					 * @brief Spacing between widgets
					 *
					 */
					static constexpr int widgetLabelSpacing = 10;

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

		}

	}

}

app::main_window::popup::LabelPopup::LabelPopup(QWidget * parent, Qt::WindowFlags flags) : app::main_window::popup::PopupBase(parent, true, app::main_window::popup::label_popup::padding, flags) {

	LOG_INFO(app::logger::info_level_e::ZERO, labelPopupOverall, "Creating label popup");

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

app::main_window::popup::LabelPopup::~LabelPopup() {
	LOG_INFO(app::logger::info_level_e::ZERO, labelPopupOverall, "Destructor of label popup class");
}

void app::main_window::popup::LabelPopup::popupLayout() {

	if (this->layout() == Q_NULLPTR) {
		// Layout
		QVBoxLayout * layout = new QVBoxLayout(this);
		layout->setSpacing(app::main_window::popup::label_popup::widgetSpacing);
		layout->setContentsMargins(app::main_window::popup::label_popup::leftMargin, app::main_window::popup::label_popup::topMargin, app::main_window::popup::label_popup::rightMargin, app::main_window::popup::label_popup::bottomMargin);

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

void app::main_window::popup::LabelPopup::fillPopup() {

	this->label = std::make_unique<app::elided_label::ElidedLabel>(this, this->windowFlags(), QString(), app::main_window::popup::label_popup::textOrigin, Qt::ElideRight);
	this->label->setTextFormat(Qt::PlainText);

	// font
	QFont labelFont(label->font());
	labelFont.setBold(true);
	this->label->setFont(labelFont);

	this->timer = std::make_unique<QTimer>(this);
}

void app::main_window::popup::LabelPopup::connectSignals() {
	LOG_INFO(app::logger::info_level_e::ZERO, labelPopupOverall, "Connect signals");

	connect(this->timer.get(), &QTimer::timeout, [this] () {
		this->close();
	});

}

void app::main_window::popup::LabelPopup::setLabelText(const QString & text) {
	this->label->setText(text);
}

void app::main_window::popup::LabelPopup::activatePopup() {

	this->timer->start(app::main_window::popup::label_popup::duration);

}

QSize app::main_window::popup::LabelPopup::sizeHint() const {

	// Width of the widget is the one of its geometry
	const int width = this->geometry().width();
	const int height = QWidget::sizeHint().height();

	QSize hint(width,height);

	return hint;
}

void app::main_window::popup::LabelPopup::close() {

	// Make popup container invisible
	QWidget * parent(this->parentWidget());
	parent->setVisible(false);

	// Give focus back to the window
	this->window()->setFocus();
}
