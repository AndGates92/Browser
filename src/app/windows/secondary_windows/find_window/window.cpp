/**
 * @copyright
 * @file window.cpp
 * @author Andrea Gianarda
 * @date 17th of July 2020
 * @brief Find Window functions
 */

#include <string>

// Qt libraries
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLayoutItem>

#include "app/utility/logger/macros.h"
#include "app/shared/exception.h"
#include "app/widgets/commands/action.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/windows/secondary_windows/find_window/window_settings.h"
#include "app/windows/secondary_windows/find_window/window.h"
#include "app/windows/secondary_windows/shared/utility.h"

// Categories
LOGGING_CONTEXT(findButtonWindowOverall, findButtonWindow.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(findButtonWindowCancel, findButtonWindow.cancel_button, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(findButtonWindowFind, findButtonWindow.find, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace find_window {

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

app::find_window::Window::Window(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags) {

	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowOverall, "Creating find button window");

	// Set modal because no other windows should be active
	this->setWindowModality(Qt::ApplicationModal);

	// Create action
	this->createActions();

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

app::find_window::Window::~Window() {
	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowOverall, "Destructor of Window class");
}

void app::find_window::Window::cancel() {
	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowCancel, "Closing dialog as Cancel button has been clicked");
	if (this->textToFind->hasFocus() == true) {
		this->setFocus();
	} else {
		this->close();
	}
}

void app::find_window::Window::close() {
	QWidget::close();
}

void app::find_window::Window::apply() {

	const QString & textToFind = this->textToFind->text();
	const app::shared::offset_type_e direction = this->settingsBox->getSearchDirection();
	const bool & caseSensitive = this->settingsBox->isCaseSensitiveSearch();
	const bool & matchFullWord = this->settingsBox->isMatchFullWordSearch();

	const app::windows::shared::FindSettings settings(textToFind, direction, caseSensitive, matchFullWord);
	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowFind, "Settings:" << settings);

	emit find(settings);

}

void app::find_window::Window::windowLayout() {

	// Layout
	// -------------------------------------------------
	// |                <text to find>                 |
	// |         <settings group box title>            |
	// |    <direction drop down>    |     <case>      |
	// |    <direction drop down>    |   <full word>   |
	// |         <find>         |       <cancel>       |
	// -------------------------------------------------

	if (this->layout() == Q_NULLPTR) {
		QVBoxLayout * layout = new QVBoxLayout(this);
//		layout->setSizeConstraint(QLayout::SetFixedSize);
		layout->setSpacing(app::find_window::window::widgetVSpacing);
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

		QHBoxLayout * lastRow = new QHBoxLayout(this);
		// find button
		lastRow->addWidget(this->findButton.get(), app::find_window::window::defaultStretch, Qt::AlignLeft);
		lastRow->addSpacing(app::find_window::window::widgetHSpacing);
		// cancel button
		lastRow->addWidget(this->cancelButton.get(), app::find_window::window::defaultStretch, Qt::AlignRight);

		// Add layouts to main layout
		layout->addWidget(this->textToFind.get(), app::find_window::window::defaultStretch);
		layout->addWidget(this->settingsBox.get(), app::find_window::window::defaultStretch);
		layout->addLayout(lastRow);

	} catch (const std::bad_cast & badCastE) {
		EXCEPTION_ACTION(throw, badCastE.what());
	}
}

void app::find_window::Window::createActions() {

	this->findAction = std::move(app::secondary_window::createAction(this, "Find", "Find text in the current page", app::commands::KeySequence(Qt::Key_F)));
	this->cancelAction = std::move(app::secondary_window::createAction(this, "Cancel", "Cancel operation", app::commands::KeySequence(Qt::Key_Escape)));
	this->typeAction = std::move(app::secondary_window::createAction(this, "Insert", "Insert", app::commands::KeySequence(Qt::Key_I)));

}

void app::find_window::Window::fillWindow() {

	this->textToFind = app::secondary_window::createLineEdit(this, "<text to search>", this->typeAction);
	this->textToFind->setText(QString());

	this->findButton = std::move(app::secondary_window::createPushButton(this, this->findAction));
	this->cancelButton = std::move(app::secondary_window::createPushButton(this, this->cancelAction));

	this->settingsBox = std::make_unique<app::find_window::Settings>(this);

}

void app::find_window::Window::connectSignals() {
	LOG_INFO(app::logger::info_level_e::ZERO, findButtonWindowOverall, "Connect signals");

	connect(this->findAction.get(), &app::commands::Action::triggered, this, &app::find_window::Window::apply);
	connect(this->findButton.get(), &QPushButton::pressed, this, &app::find_window::Window::apply);
	connect(this->cancelAction.get(), &app::commands::Action::triggered, this, &app::find_window::Window::cancel);
	connect(this->cancelButton.get(), &QPushButton::pressed, this, &app::find_window::Window::cancel);
}

QSize app::find_window::Window::sizeHint() const {

	int width = 0;

	const QList<QWidget *> widgets = this->findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
	for (QWidget * widget : widgets) {
		if (widget != Q_NULLPTR) {
			width = std::max(width, widget->sizeHint().width());
		}
	}

	// Adding 4 times the vertical spacing to account for spacing between widgets and top and bottom margins as well as space between 2 rows of widgets
	int height = this->textToFind->height() + this->settingsBox->height() + this->findButton->height() + 4 * app::find_window::window::widgetVSpacing;

	return QSize(width,height);
}
