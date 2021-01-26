/**
 * @copyright
 * @file window.cpp
 * @author Andrea Gianarda
 * @date 25th September 2019
 * @brief Open Window functions
 */

#include <string>

// Qt libraries
#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLayoutItem>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/enums.h"
#include "app/shared/exception.h"
#include "app/windows/secondary_windows/open_window/window.h"
#include "app/windows/secondary_windows/shared/utility.h"

// Categories
LOGGING_CONTEXT(openButtonWindowOverall, openButtonWindow.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openButtonWindowOpen, openButtonWindow.open_button, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openButtonWindowBrowse, openButtonWindow.browse_button, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(openButtonWindowCancel, openButtonWindow.cancel_button, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace open_window {

		namespace window {

			namespace {
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
			}

		}

	}

}

app::open_window::Window::Window(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), app::base::window::OpenContent(this) {

	LOG_INFO(app::logger::info_level_e::ZERO, openButtonWindowOverall, "Creating open button window");

	// Set modal because no other windows should be active
	this->setWindowModality(Qt::ApplicationModal);

	// Create widgets to put in the window
	this->fillWindow();

	// define window layout
	this->windowLayout();

	// Connect signals and slots
	this->connectSignals();

	// Set focus to the window
	// Don't allow other widgets to grab the focus - by default QLineEdit grabs it first
	this->setFocus();

	this->setFixedHeight(this->sizeHint().height());
}

app::open_window::Window::~Window() {
	LOG_INFO(app::logger::info_level_e::ZERO, openButtonWindowOverall, "Destructor of Window class");
}

void app::open_window::Window::browse() {
	LOG_INFO(app::logger::info_level_e::ZERO, openButtonWindowBrowse, "Browsing files - selected MIME are: " << this->fileModel->nameFilters());
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
}

void app::open_window::Window::cancel() {
	LOG_INFO(app::logger::info_level_e::ZERO, openButtonWindowCancel, "Closing dialog as Cancel button has been clicked");
	if (this->pathToOpen->hasFocus() == true) {
		this->setFocus();
	} else {
		this->close();
	}
}

void app::open_window::Window::close() {
	QWidget::close();
}

void app::open_window::Window::apply() {
	LOG_INFO(app::logger::info_level_e::ZERO, openButtonWindowOpen, "Open file: " << this->pathToOpen->text());
	this->openPath();
}

void app::open_window::Window::openItem(const QString & path) {
	emit this->fileRead(path, nullptr);
}

void app::open_window::Window::pathChanged(const QString & path) {
	const QFileInfo pathInfo(path);
	this->openButton->setEnabled(pathInfo.exists());
}

void app::open_window::Window::windowLayout() {

	// Layout
	// -------------------------------------------------
	// |           <path to open>          | <browse>  |
	// |                 <file model>                  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(app::open_window::window::widgetVSpacing);
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
		firstRow->addWidget(this->pathToOpen.get(), app::open_window::window::defaultStretch);
		firstRow->addSpacing(app::open_window::window::widgetHSpacing);
		// browse button
		firstRow->addWidget(this->browseButton.get(), app::open_window::window::defaultStretch, Qt::AlignRight);

		QHBoxLayout * lastRow = new QHBoxLayout(this);
		// open button
		lastRow->addWidget(this->openButton.get(), app::open_window::window::defaultStretch, Qt::AlignLeft);
		lastRow->addSpacing(app::open_window::window::widgetHSpacing);
		// cancel button
		lastRow->addWidget(this->cancelButton.get(), app::open_window::window::defaultStretch, Qt::AlignRight);

		// Add layouts to main layout
		layout->addLayout(firstRow);
		layout->addWidget(this->fileView.get(), app::open_window::window::defaultStretch);
		layout->addLayout(lastRow);

	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void app::open_window::Window::fillWindow() {

	this->openButton = std::move(app::secondary_window::createPushButton(this, this->applyAction));
	this->browseButton = std::move(app::secondary_window::createPushButton(this, this->browseAction));
	this->cancelButton = std::move(app::secondary_window::createPushButton(this, this->cancelAction));

	// Hide file view as user didn't ask for it
	this->fileView->setMinimumSize(this->fileView->sizeHint());
	this->fileView->hide();

	this->pathChanged(this->pathToOpen->text());

}

void app::open_window::Window::connectSignals() {
	LOG_INFO(app::logger::info_level_e::ZERO, openButtonWindowOverall, "Connect signals");

	connect(this->applyAction.get(), &app::commands::Action::triggered, this, &app::open_window::Window::apply);
	connect(this->openButton.get(), &QPushButton::pressed, this, &app::open_window::Window::apply);
	connect(this->browseAction.get(), &app::commands::Action::triggered, this, &app::open_window::Window::browse);
	connect(this->browseButton.get(), &QPushButton::pressed, this, &app::open_window::Window::browse);
	connect(this->cancelAction.get(), &app::commands::Action::triggered, this, &app::open_window::Window::cancel);
	connect(this->cancelButton.get(), &QPushButton::released, this, &app::open_window::Window::cancel);

	connect(this->pathToOpen.get(), &QLineEdit::textChanged, this, &app::open_window::Window::pathChanged);

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

QSize app::open_window::Window::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 3 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between the 2 row of widgets
	int height = std::max(this->pathToOpen->height(), this->browseButton->height()) + this->openButton->height() + 3 * app::open_window::window::widgetVSpacing;
	const bool isFileViewVisible = this->fileView->isVisible();
	if (isFileViewVisible == true) {
		height += this->fileView->height() + app::open_window::window::widgetVSpacing;
	}

	return QSize(width,height);
}
