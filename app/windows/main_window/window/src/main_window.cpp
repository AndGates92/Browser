/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabBar>
#include <QtWidgets/QSizePolicy>
#include <QtGui/QKeyEvent>

// Required by qInfo
#include <QtCore/QtDebug>

#include <QtCore/QObject>

#include "main_window_menu_bar.h"
#include "main_window_status_bar.h"
#include "main_window_tab_widget.h"
#include "command_menu.h"
#include "logging_macros.h"
#include "global_enums.h"
#include "main_window.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

namespace main_window {

	namespace {
		/**
		 * @brief vertical spacing between widgets
		 *
		 */
		static constexpr int verticalWidgetSpacing = 0;

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

	}

}

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), main_window_base::MainWindowBase(std::shared_ptr<main_window_core::MainWindowCore>(new main_window_core::MainWindowCore(this))), overlayedWidgets(std::list<std::shared_ptr<overlayed_widget::OverlayedWidget>>()) {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Main window constructor");

	this->setEnabled(true);

	// main widget
	this->customizeMainWidget();

	// main window body
	this->fillMainWindow();

	// Control
	this->createCtrl();

	// Connect signals and slots
	this->connectSignals();

	// main window layout
	this->mainWindowLayout();

	QString msg(tr("status bar message"));
	this->statusBar()->showMessage(msg);
	this->statusBar()->hide();

	this->setWindowTitle(tr("Browser"));

	this->setStyleSheet(
		"QMainWindow {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);

	const QSize winSize(320,400);
	this->resize(winSize);
}

main_window::MainWindow::~MainWindow() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Main window destructor");

	const QList<QShortcut *> shortcuts = this->findChildren<QShortcut *>(QString(), Qt::FindDirectChildrenOnly);

	for (QShortcut * shortcut : shortcuts) {
		if (shortcut != Q_NULLPTR) {
			QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowCtrlOverall,  "Delete shortcut associated with key " << shortcut->key());
			delete shortcut;
		}
	}

}

CONST_GETTER(main_window::MainWindow::getCtrl, std::unique_ptr<main_window_ctrl_wrapper::MainWindowCtrlWrapper> &, this->ctrl)

void main_window::MainWindow::customizeMainWidget() {
	this->core->mainWidget->setAttribute(Qt::WA_DeleteOnClose);
	// Disable widget resizing - it will get as much space as possible
	this->core->mainWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	this->core->mainWidget->setStyleSheet(
		"QWidget {"
			"background: brown; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);
	this->setCentralWidget(this->core->mainWidget.get());
}

void main_window::MainWindow::fillMainWindow() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Fill main window");

	// Customize MainWidget
	// Tabs
	this->customizeTabs();

	// Menu bar
	this->customizeTopMenuBar();

	// Status bar
	this->customizeBottomStatusBar();

	this->populateOverlayedWidgetList();

	if (this->core->cmdMenu != Q_NULLPTR) {
		// command menu
		this->core->cmdMenu->setVisible(false);
	}

	if (this->core->popup != Q_NULLPTR) {
		// prompt widget
		this->core->popup->setVisible(false);
	}

}

void main_window::MainWindow::customizeTabs() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Customize tabs");

	// Disable widget resizing
	this->core->tabs->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	this->core->tabs->setStyleSheet(
		"QTabBar::tab {"
			"background: gray; "
			"color: white; "
			"text-align: center; "
		"}"
		"QTabBar::tab::selected {"
			"background: black; "
		"}"
	);

}

void main_window::MainWindow::customizeTopMenuBar() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Customize top menu bar");

	// set menu bar of the main window
	this->setMenuBar(this->core->topMenuBar.get());
}

void main_window::MainWindow::customizeBottomStatusBar() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Customize top menu bar");

}

void main_window::MainWindow::mainWindowLayout() {

	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Define layout");

	// Layout
	// -------------------------------------------------
	// |                     <tabs>                    |
	// |                    <content>                  |
	// |                    <prompt>                   |
	// |                   <statusbar>                 |
	// -------------------------------------------------

	QVBoxLayout * layout = new QVBoxLayout(this);

	// tabs
	layout->addWidget(this->core->tabs.get());

	// command menu
	layout->addWidget(this->core->cmdMenu.get(), 0, (Qt::AlignHCenter | Qt::AlignBottom));

	// status bar
	layout->addWidget(this->core->bottomStatusBar.get(), Qt::AlignBottom);

	layout->setSpacing(main_window::verticalWidgetSpacing);
	layout->setContentsMargins(main_window::leftMargin, main_window::topMargin, main_window::rightMargin, main_window::bottomMargin);

	this->core->mainWidget->setLayout(layout);
}

void main_window::MainWindow::connectSignals() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Connect signals");

	// Close window
	connect(this->ctrl->winctrl.get(), &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window::MainWindow::closeWindow);

	for (std::list<std::shared_ptr<overlayed_widget::OverlayedWidget>>::const_iterator widget = this->overlayedWidgets.cbegin(); widget != this->overlayedWidgets.cend(); widget++) {
		connect((*widget).get(), &overlayed_widget::OverlayedWidget::updateGeometryRequest, this, &main_window::MainWindow::updateWidgetGeometry);
	}
}

void main_window::MainWindow::createCtrl() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Create controller");

	// main window control object
	this->ctrl = std::make_unique<main_window_ctrl_wrapper::MainWindowCtrlWrapper>(this, this->core);
	this->setFocusProxy(this->ctrl.get());
	this->ctrl->setFocus();

}

void main_window::MainWindow::closeWindow() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Close main window");
	const bool success = this->close();
	Q_ASSERT_X(success, "main window close success check", "Main window close request was not handled properly");
}

void main_window::MainWindow::resizeEvent(QResizeEvent *event) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowOverall,  "Resizing window from size " << event->oldSize() << " to size " << event->size());

	for (const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget : this->overlayedWidgets) {
		this->updateWidgetGeometry(widget);
	}

	QMainWindow::resizeEvent(event);
}

void main_window::MainWindow::addOverlayedWidget(const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget) {
	this->overlayedWidgets.push_back(widget);
}

void main_window::MainWindow::populateOverlayedWidgetList() {
	this->addOverlayedWidget(std::static_pointer_cast<overlayed_widget::OverlayedWidget>(this->core->popup));
}

void main_window::MainWindow::updateWidgetGeometry(const std::shared_ptr<overlayed_widget::OverlayedWidget> & widget) {

	// Widget information
	const QSize widgetSizeHint(widget->sizeHint());
	const QSizePolicy::Policy horizontalSizePolicy = widget->sizePolicy().horizontalPolicy();
	const bool centered = widget->isCentered();
	const int padding = widget->getPadding();

	// Window information
	const int windowWidth = this->width();
	const int windowHeight = this->height();

	int totalPadding = 0;
	if (centered == true) {
		// Widget width is the width of the window minus 2 times the padding (i.e. padding on the left and right hand side)
		totalPadding = 2 * padding;
	} else {
		// Widget width is the width of the window minus the padding (i.e. padding on the right hand side)
		totalPadding = padding;
	}

	int expandingWidth = 0;
	// If window width is smaller than the total padding, the widget is expanded to occupy the entire width of the window
	if (windowWidth > totalPadding) {
		expandingWidth = windowWidth - totalPadding;
	} else {
		expandingWidth = windowWidth;
	}

	int widgetLeft = 0;
	int widgetWidth = 0;

	// Horizontal position (left coordinate) and dimension (width)
	if (horizontalSizePolicy == QSizePolicy::Expanding) {
		widgetWidth = expandingWidth;
		if (centered == true) {
			widgetLeft = padding;
		} else {
			widgetLeft = 0;
		}
	} else {
		// Pick minimum between widget size hint and adjusted centered width accounting for padding (width of the window minus total padding)
		widgetWidth = std::min(widgetSizeHint.width(), expandingWidth);
		if (centered == true) {

			// Keep widget at the center of the window
			widgetLeft = (windowWidth - widgetSizeHint.width()) / 2;

		} else {
			widgetLeft = 0;
		}
	}

	// Vertical position (top coordinate) and dimension (height)
	const int widgetHeight = widgetSizeHint.height();

	int distanceYFromBottom = widgetHeight;
	if (this->core->bottomStatusBar->isVisible() == true) {
		const int statusBarHeight = this->core->bottomStatusBar->height();
		distanceYFromBottom += statusBarHeight;
	}

	const int widgetTop = windowHeight - distanceYFromBottom;

	QEXCEPTION_ACTION_COND((widgetHeight <= 0), throw, "Widget height " << widgetHeight << " is not within the valid range (width > 0)");
	QEXCEPTION_ACTION_COND((widgetTop < 0), throw, "Widget top coordinate " << widgetTop << " is not within the valid range (coordinate >= 0)");
	QEXCEPTION_ACTION_COND((widgetWidth <= 0), throw, "Widget width " << widgetWidth << " is not within the valid range (width > 0)");
	QEXCEPTION_ACTION_COND((widgetLeft < 0), throw, "Widget left coordinate " << widgetLeft << " is not within the valid range (coordinate >= 0)");

	QPoint topLeftCorner(widgetLeft, widgetTop);
	QSize widgetSize(widgetWidth, widgetHeight);

	QRect widgetRect(topLeftCorner, widgetSize);
	if (widgetRect.isValid() == true) {
		widget->setGeometry(widgetRect);
		widget->resize(widgetSizeHint);
	}

}
