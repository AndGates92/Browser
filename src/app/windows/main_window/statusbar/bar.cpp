/**
 * @copyright
 * @file bar.cpp
 * @author Andrea Gianarda
 * @date 03rd of February 2020
 * @brief Main Window statusbar functions
*/

// Qt libraries
#include <QtWidgets/QHBoxLayout>

#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/shared/enums.h"
#include "app/widgets/elided_label/elided_label.h"
#include "app/widgets/progress_bar/bar.h"
#include "app/widgets/commands/key_sequence.h"
#include "app/windows/main_window/shared/constants.h"
#include "app/windows/main_window/statusbar/bar.h"

// Categories
LOGGING_CONTEXT(mainWindowStatusBarOverall, mainWindowStatusBar.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowStatusBarMouse, mainWindowStatusBar.mouse, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowStatusBarUserInput, mainWindowStatusBar.userInput, TYPE_LEVEL, INFO_VERBOSITY)

namespace app {

	namespace main_window {

		namespace statusbar {

			namespace {

				/**
				 * @brief default origin of text in status bar widget
				 *
				 */
				static const QPoint textOrigin(0,0);

				/**
				 * @brief bottom information text height
				 *
				 */
				static constexpr int textHeight = 20;

				/**
				 * @brief horizontal spacing between widgets
				 *
				 */
				static constexpr int horizontalWidgetSpacing = 0;

				/**
				 * @brief left margin between widget and window
				 *
				 */
				static constexpr int leftMargin = 0;

				/**
				 * @brief right margin between widget and window
				 *
				 */
				static constexpr int rightMargin = 0;

				/**
				 * @brief top margin between widget and window
				 *
				 */
				static constexpr int topMargin = 0;

				/**
				 * @brief bottom margin between widget and window
				 *
				 */
				static constexpr int bottomMargin = 0;

				/**
				 * @brief minimum value of scrolling
				 *
				 */
				static constexpr int minScrollValue = 0;

				/**
				 * @brief maximum value of scrolling
				 *
				 */
				static constexpr int maxScrollValue = 100;

				/**
				 * @brief string to print when cursor is at the top of the page
				 *
				 */
				static const QString topScroll = "top";

				/**
				 * @brief string to print when cursor is at the bottom of the page
				 *
				 */
				static const QString bottomScroll = "bot";

			}

		}

	}

}

app::main_window::statusbar::Bar::Bar(QWidget * parent, Qt::WindowFlags flags) : QWidget(parent, flags), userInput(Q_NULLPTR), contentPath(Q_NULLPTR), scroll(Q_NULLPTR), info(Q_NULLPTR), searchResult(Q_NULLPTR), loadBar(Q_NULLPTR) {

	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarOverall, "Main window status bar constructor");

	this->userInput = std::move(this->newWindowLabel());
	this->contentPath = std::move(this->newWindowLabel());
	this->scroll = std::move(this->newWindowLabel());
	this->info = std::move(this->newWindowLabel());
	this->searchResult = std::move(this->newWindowLabel());
	this->loadBar = std::move(this->newProgressBar());

	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	this->setStyleSheet(
		"QWidget {"
			"background-color: black;"
		"}"
	);

	// user input
	this->userInput->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

	// path to the content
	this->contentPath->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->contentPath->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// info
	this->info->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->info->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// scroll
	this->scroll->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->scroll->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// search result
	this->showSearchResult(false);
	this->searchResult->setAlignment(Qt::AlignRight | Qt::AlignBottom);
	this->searchResult->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// loadBar
	this->loadBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// Populate statusbar
	this->fillStatusBar();
}

app::main_window::statusbar::Bar::~Bar() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarOverall, "Main window status bar destructor");

}

std::unique_ptr<app::elided_label::ElidedLabel> app::main_window::statusbar::Bar::newWindowLabel() {
	std::unique_ptr<app::elided_label::ElidedLabel> newLabel = std::make_unique<app::elided_label::ElidedLabel>(this, this->windowFlags(), QString(), app::main_window::statusbar::textOrigin, Qt::ElideRight);
	newLabel->setAttribute(Qt::WA_DeleteOnClose);
	newLabel->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	newLabel->setFixedHeight(app::main_window::statusbar::textHeight);
	newLabel->setTextFormat(Qt::PlainText);
	// Align at the bottom of the widget - this override the default of vertically centered
	newLabel->setAlignment(Qt::AlignBottom);
	// Set style sheet from the parent object because it can be customized based on the parent object properties
	newLabel->setStyleSheet(
		"QLabel {"
			// Backgorund color to be inherited from the parent one
			"background: inherit; "
			// Text color
			// Set to white as status bar backgorund color is black
			"color: white; "
			"text-align: center; "
			"border-right: 1px solid inherit; "
			"border-left: 1px solid inherit; "
			// Inherit font
			"font: inherit; "
		"}"
	);

	return newLabel;
}

std::unique_ptr<app::progress_bar::Bar> app::main_window::statusbar::Bar::newProgressBar() {
	std::unique_ptr<app::progress_bar::Bar> bar = std::make_unique<app::progress_bar::Bar>(this);

	// Set style sheet from the parent object because it can be customized based on the parent object properties
	bar->setStyleSheet(
		"QProgressBar {"
			// Backgorund color to be inherited from the parent one
			"background-color: inherit; "
			"text-align: center; "
			// Text color
			// Set to black as progress bar backgorund color is white
			"color: black; "
			// How rounded borders are. No rounding in this case
			"border-radius: 0px; "
			"border-right: 1px solid inherit; "
			"border-left: 1px solid inherit; "
			// Inherit font
			"font: inherit; "
		"}"
		"QProgressBar::chunk {"
			// Set to white as status bar backgorund color is black
			"background-color: white; "
			"margin-left: 2px; "
			"margin-right: 2px; "
			"margin-top: 4px; "
			"margin-bottom: 4px; "
		"}"
	);

	return bar;
}

void app::main_window::statusbar::Bar::fillStatusBar() {

	// Layout
	// ------------------------------------------------------------------------------------
	// | <user text> |      <content>     |   <info>   | <progress bar> | <search result> |
	// ------------------------------------------------------------------------------------

	QHBoxLayout * layout = new QHBoxLayout(this);

	// user input text
	layout->addWidget(this->userInput.get());

	// path to the content
	layout->addWidget(this->contentPath.get());

	// scroll
	layout->addWidget(this->scroll.get());

	// info
	layout->addWidget(this->info.get());

	// load bar
	layout->addWidget(this->loadBar.get());

	// search result
	layout->addWidget(this->searchResult.get());

	layout->setSpacing(app::main_window::statusbar::horizontalWidgetSpacing);
	layout->setContentsMargins(app::main_window::statusbar::leftMargin, app::main_window::statusbar::topMargin, app::main_window::statusbar::rightMargin, app::main_window::statusbar::bottomMargin);

	this->setLayout(layout);
}

QSize app::main_window::statusbar::Bar::minimumSizeHint() const {
	int width = QWidget::minimumSizeHint().width();
	int height = this->fontMetrics().height() + app::main_window::statusbar::topMargin + app::main_window::statusbar::bottomMargin;

	return QSize(width,height);
}

bool app::main_window::statusbar::Bar::isValidScrollValue(const int & value) const {
	return  ((value >= app::main_window::statusbar::minScrollValue) && (value <= app::main_window::statusbar::maxScrollValue));
}

void app::main_window::statusbar::Bar::setVScroll(const int & vScroll) {
	QString vScrollText = QString();
	// Keep 3 characters for all scroll positions
	if (this->isValidScrollValue(vScroll) == true) {
		if ((vScroll == app::main_window::statusbar::minScrollValue) && (app::main_window::statusbar::topScroll.isEmpty() == false)) {
			vScrollText.append(app::main_window::statusbar::topScroll);
		} else if ((vScroll == app::main_window::statusbar::maxScrollValue) && (app::main_window::statusbar::bottomScroll.isEmpty() == false)) {
			vScrollText.append(app::main_window::statusbar::bottomScroll);
		} else {
			// arg(value, field width, base, fill character)
			vScrollText.append(QString("%1").arg(vScroll, 2, 10, QChar('0')));
			vScrollText.append("%");
		}
	}

	this->scroll->setText(vScrollText);
}

int app::main_window::statusbar::Bar::getVScroll() const {
	QString vScrollText(this->scroll->text());
	int topCompare = QString::compare(vScrollText, app::main_window::statusbar::topScroll);
	int bottomCompare = QString::compare(vScrollText, app::main_window::statusbar::bottomScroll);

	int value = 0;

	if (topCompare == 0) {
		value = app::main_window::statusbar::minScrollValue;
	} else if (bottomCompare == 0) {
		value = app::main_window::statusbar::maxScrollValue;
	} else {
		vScrollText.resize(vScrollText.size() - 1);
		bool success = false;
		value = vScrollText.toInt(&success, 10);
		EXCEPTION_ACTION_COND((success == false), throw, "Conversion of " << vScrollText << " to integer failed");
	}

	return value;
}

void app::main_window::statusbar::Bar::setProgressValue(const int & value) {
	this->loadBar->setValue(value);
}
BASE_GETTER(app::main_window::statusbar::Bar::getProgressValue, int, this->loadBar->value())
BASE_GETTER(app::main_window::statusbar::Bar::getLoadBarVisibility, bool, this->loadBar->isVisible())
CONST_GETTER(app::main_window::statusbar::Bar::getLoadBar, std::unique_ptr<app::progress_bar::Bar> &, this->loadBar)

void app::main_window::statusbar::Bar::setInfoText(const QString & text) {
	this->info->setText(text);
}
CONST_GETTER(app::main_window::statusbar::Bar::getInfoText, QString, this->info->text())
CONST_GETTER(app::main_window::statusbar::Bar::getInfo, std::unique_ptr<app::elided_label::ElidedLabel> &, this->info)

void app::main_window::statusbar::Bar::setUserInputText(const QString & text) {
	this->userInput->setText(text);
}
CONST_GETTER(app::main_window::statusbar::Bar::getUserInputText, QString, this->userInput->text())
CONST_GETTER(app::main_window::statusbar::Bar::getUserInput, std::unique_ptr<app::elided_label::ElidedLabel> &, this->userInput)

void app::main_window::statusbar::Bar::setContentPathText(const QString & text) {
	this->contentPath->setText(text);
}
CONST_GETTER(app::main_window::statusbar::Bar::getContentPathText, QString, this->contentPath->text())
CONST_GETTER(app::main_window::statusbar::Bar::getContentPath, std::unique_ptr<app::elided_label::ElidedLabel> &, this->contentPath)

void app::main_window::statusbar::Bar::setSearchResultText(const QString & text) {
	this->searchResult->setText(text);
}
CONST_GETTER(app::main_window::statusbar::Bar::getSearchResultText, QString, this->searchResult->text())
CONST_GETTER(app::main_window::statusbar::Bar::getSearchResult, std::unique_ptr<app::elided_label::ElidedLabel> &, this->searchResult)

void app::main_window::statusbar::Bar::showSearchResult(const bool & showWidget) {
	const bool isTextEmpty = this->searchResult->text().isEmpty();
	if ((showWidget == true) && (isTextEmpty == false)) {
		this->searchResult->show();
	} else {
		this->searchResult->hide();
	}
}

void app::main_window::statusbar::Bar::mousePressEvent(QMouseEvent * event) {

	if (event->type() == QEvent::MouseButtonPress) {

		const Qt::MouseButton & button = event->button();

		if (button & Qt::LeftButton) {

			// Do not give focus if not tabs are opened
			const QString infoText(this->info->text());
			if (infoText.compare(app::main_window::noTabInfoText, Qt::CaseSensitive) != 0) {
				// Position relative to the widget
				const QPointF & relativePosition = event->localPos();
				QWidget * clickedWidget = this->childAt(relativePosition.toPoint());

				// Do not give focus to the status bar if clicking on the progress bar
				if (clickedWidget == this->userInput.get()) {
					LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarMouse, "Give focus to window " << this->window());
					// If wanting to type a command give the focus to the window as it will proxy it to the control wrapper
					this->window()->setFocus();
				} else if (clickedWidget == this->contentPath.get()) {
					LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarMouse, "Give focus proxy to widget " << clickedWidget);
					this->setFocus();
					this->setFocusProxy(clickedWidget);
					emit this->childFocusIn();
				}

			}

		}

	}
}

void app::main_window::statusbar::Bar::keyPressEvent(QKeyEvent * event) {

	if (event->type() == QEvent::KeyPress) {

		const int pressedKey = event->key();
		const Qt::KeyboardModifiers keyModifiers = event->modifiers();

		const app::commands::KeySequence keySeq(pressedKey | keyModifiers);

		// Retrieve main window controller state
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarUserInput, "Key pressed " << keySeq.toString());

		QWidget * focusWidget = this->focusProxy();
		EXCEPTION_ACTION_COND((focusWidget == this->userInput.get()), throw, "Key events towards the command label should be sent directly through the main window");
		EXCEPTION_ACTION_COND((focusWidget == this->loadBar.get()), throw, "Loadbar is unable to accept key inputs");
		EXCEPTION_ACTION_COND((focusWidget == this->scroll.get()), throw, "Unable to scroll to the " + std::to_string(this->getVScroll()) + " %% of the page");
		EXCEPTION_ACTION_COND((focusWidget == this->info.get()), throw, "Cannot change tab by changing the information text \"" + this->getInfoText() + "\" in the statusbar");
		EXCEPTION_ACTION_COND((focusWidget == this->searchResult.get()), throw, "Cannot change search result match number by changing the text \"" + this->getSearchResultText() + "\" in the statusbar");

		app::elided_label::ElidedLabel * label = static_cast<app::elided_label::ElidedLabel *>(focusWidget);
		QString labelText(label->text());

		// Print visible text characters
		if ((pressedKey >= Qt::Key_Space) && (pressedKey <= Qt::Key_ydiaeresis)) {
			labelText.append(event->text());
			label->setText(labelText);

		} else if ((pressedKey == Qt::Key_Enter) || (pressedKey == Qt::Key_Return)) {
			if ((focusWidget == this->loadBar.get()) || (focusWidget == this->userInput.get())) {
				EXCEPTION_ACTION(throw, "Unable to execute action because focus widget is set to " << focusWidget);
			} else if (focusWidget == this->contentPath.get()) {
				QString path = this->contentPath->text();
				LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarUserInput, "Opening URL or file " << path);
				// Notify that the content path has changed
				emit this->contentPathChanged(path);
				this->window()->setFocus();
			} else {
				EXCEPTION_ACTION(throw, "Unable to accept key events because focus widget is set to " << focusWidget);
			}
			// TODO handle enter or return key
			// TODO: emit signal to execute action
		}
	}
}

void app::main_window::statusbar::Bar::keyReleaseEvent(QKeyEvent * event) {
	if (event->type() == QEvent::KeyRelease) {

		const int releasedKey = event->key();
		const Qt::KeyboardModifiers keyModifiers = event->modifiers();

		const app::commands::KeySequence keySeq(releasedKey | keyModifiers);

		// Retrieve main window controller state
		LOG_INFO(app::logger::info_level_e::ZERO, mainWindowStatusBarUserInput, "Released key " << keySeq.toString());

		QWidget * focusWidget = this->focusProxy();
		app::elided_label::ElidedLabel * label = static_cast<app::elided_label::ElidedLabel *>(focusWidget);
		QString labelText(label->text());

		switch (releasedKey) {
			case Qt::Key_Escape:
				this->window()->setFocus();
				this->setFocusProxy(nullptr);
				break;
			case Qt::Key_Backspace:
				if (labelText.isEmpty() == false) {
					labelText.chop(1);
					label->setText(labelText);
				}
			default:
				break;
		}
	}
}


