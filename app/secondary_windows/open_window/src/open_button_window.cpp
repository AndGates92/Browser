/**
 * @copyright
 * @file open_button_window.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Open Button Window functions
 */

#include <string>

// Qt libraries
// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>
#include <qt5/QtCore/QFile>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QLayoutItem>

#include "logging_macros.h"
#include "global_types.h"
#include "open_button_window.h"
#include "exception_macros.h"


// Categories
Q_LOGGING_CATEGORY(openButtonWindowOverall, "openButtonWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowLayout, "openButtonWindow.layout", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowOpen, "openButtonWindow.open_button", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowBrowse, "openButtonWindow.browse_button", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(openButtonWindowCancel, "openButtonWindow.cancel_button", MSG_TYPE_LEVEL)

namespace open_button_window {

	namespace {
		/**
		 * @brief maximum number of location in the array storing a line of the user selected file
		 *
		 */
		static constexpr int userFileSize = 1024;

		/**
		 * @brief margin above the text inside the push button
		 *
		 */
		static constexpr int topButtonMargin = 5;

		/**
		 * @brief margin underneat the text inside the push button
		 *
		 */
		static constexpr int bottomButtonMargin = 5;

		/**
		 * @brief default layout stretch
		 *
		 */
		static constexpr int defaultStretch = 0;

		/**
		 * @brief vertical spacing between widgets
		 *
		 */
		static constexpr int widgetVSpacing = 10;

		/**
		 * @brief horizontal spacing between widgets
		 *
		 */
		static constexpr int widgetHSpacing = 10;

		/**
		 * @brief number of column used by a QPushButton instance
		 *
		 */
		static constexpr int pushButtonWidth = 1;

		/**
		 * @brief number of rows used by a QPushButton instance
		 *
		 */
		static constexpr int pushButtonHeight = 1;

		/**
		 * @brief number of column used by a QLineEdit instance
		 *
		 */
		static constexpr int pathToOpenWidth = 20;

		/**
		 * @brief number of rows used by a QLineEdit instance
		 *
		 */
		static constexpr int pathToOpenHeight = 1;

		/**
		 * @brief number of column used by a QTreeView instance
		 *
		 */
		static constexpr int fileSystemWidth = 40;

		/**
		 * @brief number of rows used by a QTreeView instance
		 *
		 */
		static constexpr int fileSystemHeight = 40;
	}

}

open_button_window::OpenButtonWindow::OpenButtonWindow(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), open_content::OpenContent(this) {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Creating open button window");

	// Set modal because no other windows should be active
	this->setWindowModality(Qt::ApplicationModal);

	// Create widgets to put in the window
	this->fillWindow();

	this->addAction(this->typeAction.get());

	// define window layout
	this->windowLayout();

	// Connect signals and slots
	this->connectSignals();

	// Set focus to the window
	// Don't allow other widgets to grab the focus - by default QLineEdit grabs it first
	this->setFocus();

	this->setFixedHeight(this->sizeHint().height());
}

open_button_window::OpenButtonWindow::~OpenButtonWindow() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Destructor of OpenButtonWindow class");
}

void open_button_window::OpenButtonWindow::browse() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowBrowse,  "Browsing files - selected MIME are: " << this->fileModel->nameFilters());
	const bool isFileViewVisible = this->fileView->isVisible();

	if (isFileViewVisible == true) {
		this->fileView->hide();
		this->setFixedHeight(this->sizeHint().height());
	} else {
		this->fileView->show();
		this->setMinimumHeight(0);
		this->setMaximumHeight(QWIDGETSIZE_MAX);
		this->resize(this->sizeHint());
	}
//	this->windowLayout();
}

void open_button_window::OpenButtonWindow::cancel() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowCancel,  "Closing dialog as Cancel button has been clicked");
	if (this->pathToOpen->hasFocus() == true) {
		this->setFocus();
	} else {
		this->close();
	}
}

void open_button_window::OpenButtonWindow::close() {
	QWidget::close();
}

void open_button_window::OpenButtonWindow::apply() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOpen,  "Open file: " << this->pathToOpen->text());
	this->openPath();
}



void open_button_window::OpenButtonWindow::insert() {
	// Using here setFocus on the QLineEdit instead of setProxyFocus because of bug QTBUG-79707
	this->pathToOpen->setFocus();
	//this->setFocusProxy(this->pathToOpen);
}

void open_button_window::OpenButtonWindow::openItem(const QString & path) {
	emit this->fileRead(path, nullptr);
}

void open_button_window::OpenButtonWindow::pathChangedAction(const QString & path) {
	const QFileInfo pathInfo(path);
	this->openButton->setEnabled(pathInfo.exists());
}

void open_button_window::OpenButtonWindow::windowLayout() {

	// Layout
	// -------------------------------------------------
	// |           <path to open>          | <browse>  |
	// |                 <file model>                  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(open_button_window::widgetVSpacing);
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

		QHBoxLayout * firstRow = new QHBoxLayout(this);
		// path or URL to open
		firstRow->addWidget(this->pathToOpen.get(), open_button_window::defaultStretch);
		firstRow->addSpacing(open_button_window::widgetHSpacing);
		// browse button
		firstRow->addWidget(this->browseButton.get(), open_button_window::defaultStretch, Qt::AlignRight);

		QHBoxLayout * lastRow = new QHBoxLayout(this);
		// open button
		lastRow->addWidget(this->openButton.get(), open_button_window::defaultStretch, Qt::AlignLeft);
		lastRow->addSpacing(open_button_window::widgetHSpacing);
		// cancel button
		lastRow->addWidget(this->cancelButton.get(), open_button_window::defaultStretch, Qt::AlignRight);

		// Add layouts to main layout
		layout->addLayout(firstRow);
		layout->addWidget(this->fileView.get(), open_button_window::defaultStretch);
		layout->addLayout(lastRow);

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}
}

void open_button_window::OpenButtonWindow::fillWindow() {

	this->openButton = std::move(this->createPushButton(this, this->applyAction));
	this->browseButton = std::move(this->createPushButton(this, this->browseAction));
	this->cancelButton = std::move(this->createPushButton(this, this->cancelAction));

	// Hide file view as user didn't ask for it
	this->fileView->setMinimumSize(this->fileView->sizeHint());
	this->fileView->hide();

	this->pathChangedAction(this->pathToOpen->text());

}

void open_button_window::OpenButtonWindow::connectSignals() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, openButtonWindowOverall,  "Connect signals");

	connect(this->applyAction.get(), &action::Action::triggered, this, &open_button_window::OpenButtonWindow::apply);
	connect(this->openButton.get(), &QPushButton::pressed, this, &open_button_window::OpenButtonWindow::apply);
	connect(this->browseAction.get(), &action::Action::triggered, this, &open_button_window::OpenButtonWindow::browse);
	connect(this->browseButton.get(), &QPushButton::pressed, this, &open_button_window::OpenButtonWindow::browse);
	connect(this->cancelAction.get(), &action::Action::triggered, this, &open_button_window::OpenButtonWindow::cancel);
	connect(this->cancelButton.get(), &QPushButton::released, this, &open_button_window::OpenButtonWindow::cancel);
	connect(this->typeAction.get(), &action::Action::triggered, this, &open_button_window::OpenButtonWindow::insert);

	connect(this->pathToOpen.get(), &QLineEdit::textChanged, this, &open_button_window::OpenButtonWindow::pathChangedAction);

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

std::unique_ptr<QPushButton> open_button_window::OpenButtonWindow::createPushButton(QWidget *parent, const std::shared_ptr<action::Action> & actionPtr) {
	// Push button text is <actionName> (<shortcut>)
	std::string buttonText(actionPtr->text().toStdString());
	if (actionPtr->shortcut().isEmpty() == false) {
		buttonText.append(" (");
		buttonText.append(actionPtr->shortcut().toString().toStdString());
		buttonText.append(")");
	}
	std::unique_ptr<QPushButton> button = std::make_unique<QPushButton>(QPushButton::tr(buttonText.c_str()), parent);
	button->addAction(const_cast<action::Action *>(actionPtr.get()));
	button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	button->setFixedHeight(button->fontMetrics().height() + open_button_window::topButtonMargin + open_button_window::bottomButtonMargin);

	return button;
}

QSize open_button_window::OpenButtonWindow::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 3 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between the 2 row of widgets
	int height = std::max(this->pathToOpen->height(), this->browseButton->height()) + this->openButton->height() + 3 * open_button_window::widgetVSpacing;
	const bool isFileViewVisible = this->fileView->isVisible();
	if (isFileViewVisible == true) {
		height += this->fileView->height() + open_button_window::widgetVSpacing;
	}

	return QSize(width,height);
}
