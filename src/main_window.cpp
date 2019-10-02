/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QShortcut>
#include <qt5/QtWidgets/QTabBar>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	QWidget * mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	// main window body
	this->fillMainWindow(mainWidget);

	// Menu bar
	this->fillMenuBar();

	// main window layout
	this->mainWindowLayout(mainWidget);

	// Shortcuts
	this->createShortcuts();

	QString msg(tr("status bar message"));
	statusBar()->showMessage(msg);

	setWindowTitle(tr("Browser"));

	QSize winSize(320,400);
	resize(winSize);
}

void main_window::MainWindow::fillMainWindow(QWidget * mainWidget) {
	// Customize QTabWidget
	this->createTabs(mainWidget);

	QLabel * centerWindow = new QLabel(tr("Example"), mainWidget);
	centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	centerWindow->setAlignment(Qt::AlignCenter);

	QLabel * centerWindow1 = new QLabel(tr("Example 1"), mainWidget);
	centerWindow1->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	centerWindow1->setAlignment(Qt::AlignCenter);

	this->tabs->addTab(centerWindow, "test");
	this->tabs->addTab(centerWindow1, "test1");

	//this->centerWindow = new QLabel(tr("Example"), mainWidget);

}

void main_window::MainWindow::createTabs(QWidget * mainWidget) {
	this->tabs = new QTabWidget(mainWidget);
	// size policy horintally and vertically to expanding
	this->tabs->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	this->tabs->tabBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	this->tabs->tabBar()->setExpanding(true);

	this->tabs->setStyleSheet(
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

void main_window::MainWindow::mainWindowLayout(QWidget * mainWidget) {
	// Layout
	// -------------------------------------------------
	// |  <label>  |     <text to open>    | <browse>  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------

	QVBoxLayout * layout = new QVBoxLayout(mainWidget);
	layout->setContentsMargins(5,5,5,5);
	layout->addWidget(this->tabs);
//	layout->addWidget(this->centerWindow);

	mainWidget->setLayout(layout);
}

void main_window::MainWindow::fillMenuBar() {
	this->fileMenu = new file_menu::FileMenu(this, this->menuBar(), "File", Qt::Key_F);
	connect(this->fileMenu, &file_menu::FileMenu::updateCenterWindow, this, &main_window::MainWindow::setCenterWindow);
	this->editMenu = new edit_menu::EditMenu(this, this->menuBar(), "Edit", Qt::Key_E);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::createShortcuts() {
	// m will hide/show the menu bar
	QShortcut * hideMenuBar = new QShortcut(this);
	hideMenuBar->setKey(Qt::Key_M);
	connect(hideMenuBar, &QShortcut::activated, this, &main_window::MainWindow::disableMenubar);
}

void main_window::MainWindow::disableMenubar() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->tabs->currentWidget());
	currentWidget->setText(str);
	currentWidget->repaint();
}
