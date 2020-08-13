/**
 * @copyright
 * @file open_popup.cpp
 * @author Andrea Gianarda
 * @date 03rd of June 2020
 * @brief Open Popup functions
 */

#include <string>

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>

#include <QtGui/QKeyEvent>

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QApplication>

#include "logging_macros.h"
#include "global_enums.h"
#include "open_popup.h"
#include "exception_macros.h"


// Categories
Q_LOGGING_CATEGORY(openPopupOverall, "openPopup.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openPopupOpen, "openPopup.open", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openPopupBrowse, "openPopup.browse", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openPopupCancel, "openPopup.cancel", MSG_TYPE_LEVEL)

namespace open_popup {

	namespace {

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
	}

}

open_popup::OpenPopup::OpenPopup(QWidget * parent, Qt::WindowFlags flags) : main_window_popup_base::MainWindowPopupBase(parent, true, open_popup::padding, flags), open_content::OpenContent(this) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openPopupOverall,  "Creating open popup");

	// Create widgets to put in the window
	this->fillPopup();

	// add actions to popup
	this->addActionsToWidget(this);

	// define window layout
	this->popupLayout();

	// Connect signals and slots
	this->connectSignals();

	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	this->setFocusPolicy(Qt::StrongFocus);

	this->setStyleSheet(
		"QLabel {"
			"color: black;"
		"}"
		"QLabel::disabled {"
			"color: lightgray;"
		"}"
		"QLineEdit {"
			"border-color: black;"
			"border-width: 2px;"
			"background-color: white;"
			"color: black;"
		"}"
		"QTreeView {"
			"border-color: black;"
			"border-width: 2px;"
		"}"
		// Background colour of items and corner between 2 scrollbars
		"QTreeView::item, QTreeView::corner {"
			"background-color: gray;"
		"}"
		"QTreeView::item:hover {"
			"background-color: lightyellow;"
			"color: black;"
		"}"
		"QTreeView::item:selected:active, QTreeView::item:selected:!active {"
			"background-color: lightgray;"
			"color: black;"
		"}"
		"QTreeView::branch {"
			"background-color: gray;"
		"}"
		"QScrollBar:horizontal, QScrollBar:vertical {"
			"background-color: lightgray;"
		"}"
	);
}

open_popup::OpenPopup::~OpenPopup() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openPopupOverall,  "Destructor of open popup class");
}

void open_popup::OpenPopup::popupLayout() {

	if (this->layout() == Q_NULLPTR) {
		// Layout
		QVBoxLayout * layout = new QVBoxLayout(this);
		layout->setSpacing(open_popup::widgetSpacing);
		layout->setContentsMargins(open_popup::leftMargin, open_popup::topMargin, open_popup::rightMargin, open_popup::bottomMargin);

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

		layout->addWidget(this->pathToOpen.get());
		layout->addSpacing(open_popup::widgetLabelSpacing);
		layout->addWidget(this->openLabel.get());
		layout->addWidget(this->insertLabel.get());
		layout->addWidget(this->browseLabel.get());
		layout->addWidget(this->cancelLabel.get());
		layout->addSpacing(open_popup::widgetLabelSpacing);
		layout->addWidget(this->fileView.get());

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

}

void open_popup::OpenPopup::fillPopup() {

	this->openLabel = std::move(this->actionToLabel(this, this->applyAction));
	this->browseLabel = std::move(this->actionToLabel(this, this->browseAction));
	this->cancelLabel = std::move(this->actionToLabel(this, this->cancelAction));
	this->insertLabel = std::move(this->actionToLabel(this, this->typeAction));

	// Hide file view as user didn't ask for it
	// Use hide and not setVisible(false) because function hide also does not show it in the layout
	this->fileView->hide();

	this->pathChanged(this->pathToOpen->text());
}

void open_popup::OpenPopup::connectSignals() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openPopupOverall,  "Connect signals");

	connect(this->applyAction.get(), &action::Action::triggered, this, &open_popup::OpenPopup::apply);
	connect(this->cancelAction.get(), &action::Action::triggered, this, &open_popup::OpenPopup::cancel);
	connect(this->browseAction.get(), &action::Action::triggered, this, &open_popup::OpenPopup::browse);
	connect(this->typeAction.get(), &action::Action::triggered, this, &open_popup::OpenPopup::postProcessTypeAction);

	connect(this->pathToOpen.get(), &QLineEdit::textChanged, this, &open_popup::OpenPopup::pathChanged);

	// Need to use lambda function as fileViewClickAction is not a slot
	connect(this->fileView.get(), &QTreeView::clicked, [this] (const QModelIndex & index) {
		this->fileViewClickAction(index);
	});

	// Need to use lambda function as fileViewDoubleClickAction is not a slot
	connect(this->fileView.get(), &QTreeView::doubleClicked, [this] (const QModelIndex & index) {
		this->fileViewDoubleClickAction(index);
	});

	connect(this->fileModel.get(), &QFileSystemModel::directoryLoaded, [this] (const QString & path) {
		this->directoryLoadedAction(path);
	});

}

void open_popup::OpenPopup::postProcessTypeAction() {
	this->insertLabel->setEnabled(false);
	this->typeAction->setEnabled(false);
}

void open_popup::OpenPopup::apply() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openPopupOpen,  "Open file: " << this->pathToOpen->text());
	this->close();
	this->openPath();
}

void open_popup::OpenPopup::browse() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openPopupBrowse,  "Browsing files - selected MIME are: " << this->fileModel->nameFilters());
	const bool isFileViewVisible = this->fileView->isVisible();

	if (isFileViewVisible == true) {
		this->fileView->hide();
	} else {
		this->fileView->show();
	}

	emit this->sizeChanged();

}

void open_popup::OpenPopup::cancel() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, openPopupCancel,  "Closing popup as Cancel button has been clicked");
	if (this->pathToOpen->hasFocus() == true) {
		this->setFocus();
		this->insertLabel->setEnabled(true);
		this->typeAction->setEnabled(true);
	} else {
		this->close();
	}
}

void open_popup::OpenPopup::close() {

	// Make popup container invisible
	QWidget * parent(this->parentWidget());
	if (parent == Q_NULLPTR) {
		QWidget::setVisible(false);
	} else {
		parent->setVisible(false);
	}
	emit this->closePopup();
	// Give focus back to the window
	this->window()->setFocus();
}

void open_popup::OpenPopup::openItem(const QString & path) {
	emit this->fileRead(path, nullptr);
}

void open_popup::OpenPopup::activatePopup() {
	this->setFocus(Qt::PopupFocusReason);
}

void open_popup::OpenPopup::keyPressEvent(QKeyEvent * event) {

	const int pressedKey = event->key();
	const Qt::KeyboardModifiers keyModifiers = event->modifiers();

	const key_sequence::KeySequence keySeq(pressedKey | keyModifiers);

	if (event->type() == QEvent::KeyPress) {

		switch (pressedKey) {
			case Qt::Key_Return:
			case Qt::Key_Enter:
				this->openPath();
				break;
			default:
				break;
		}
	}

}

QSize open_popup::OpenPopup::sizeHint() const {

	// Width of the widget is the one of its geometry
	const int width = this->geometry().width();
	const int height = QWidget::sizeHint().height();

	QSize hint(width,height);

	return hint;
}

void open_popup::OpenPopup::pathChanged(const QString & path) {
	const QFileInfo pathInfo(path);
	this->openLabel->setEnabled(pathInfo.exists());
	this->applyAction->setEnabled(pathInfo.exists());
}
