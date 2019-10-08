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
#include <qt5/QtGui/QKeyEvent>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowCenterWindow, "mainWindow.centerWindow", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowSearch, "mainWindow.search", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	mainWindowState = main_window::MainWindow::state_e::IDLE;

	// main widget
	this->createMainWidget();

	// main window body
	this->fillMainWindow();

	// Menu bar
	this->fillMenuBar();

	// main window layout
	this->mainWindowLayout();

	// Shortcuts
	this->createShortcuts();

	QString msg(tr("status bar message"));
	this->statusBar()->showMessage(msg);

	setWindowTitle(tr("Browser"));

	QSize winSize(320,400);
	this->resize(winSize);
}


void main_window::MainWindow::createMainWidget() {
	this->mainWidget = new QWidget(this);
	this->mainWidget->setFocusPolicy(Qt::StrongFocus);
	setCentralWidget(this->mainWidget);
}

void main_window::MainWindow::fillMainWindow() {
	// Customize MainWidget
	this->createTabs();

}

void main_window::MainWindow::createTabs() {
	this->tabs = new tab_widget::TabWidget(this->mainWidget);
	// size policy horintally and vertically to expanding
	this->tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	this->tabs->setStyleSheet(
		"QTabBar::tab {"
			"background: gray; "
			"color: white; "
			"min-width: 100px; "
			"min-heigth: 20px; "
			"text-align: center; "
		"}"
		"QTabBar::tab::selected {"
			"background: black; "
		"}"
	);

}

void main_window::MainWindow::mainWindowLayout() {
	// Layout
	// -------------------------------------------------
	// |  <label>  |     <text to open>    | <browse>  |
	// |  <open>   |                       | <cancel>  |
	// -------------------------------------------------

	QVBoxLayout * layout = new QVBoxLayout(this->mainWidget);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(this->tabs);
//	layout->addWidget(this->centerWindow);

	this->mainWidget->setLayout(layout);
}

void main_window::MainWindow::fillMenuBar() {
	this->fileMenu = new file_menu::FileMenu(this, this->menuBar(), "File", Qt::Key_F);
	// When the file has been read, then show it on the screen
	connect(this->fileMenu, &file_menu::FileMenu::updateCenterWindow, this, &main_window::MainWindow::setCenterWindow);
	this->editMenu = new edit_menu::EditMenu(this, this->menuBar(), "Edit", Qt::Key_E);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::createShortcuts() {
	// m will hide/show the menu bar
	QShortcut * toggleShowMenuBarKey = new QShortcut(this);
	toggleShowMenuBarKey->setKey(Qt::Key_M);
	connect(toggleShowMenuBarKey, &QShortcut::activated, this, &main_window::MainWindow::toggleShowMenubarSlot);

	// o + t will open a new tab
	QShortcut * openNewTabKey = new QShortcut(this);
	openNewTabKey->setKey(Qt::Key_O);
	connect(openNewTabKey, &QShortcut::activated, this, &main_window::MainWindow::openNewTabSlot);

	// s will open a new tab
	QShortcut * newSearchTabKey = new QShortcut(this);
	newSearchTabKey->setKey(Qt::Key_S);
	connect(newSearchTabKey, &QShortcut::activated, this, &main_window::MainWindow::newSearchTabSlot);

}

void main_window::MainWindow::toggleShowMenubarSlot() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::addNewTab(QString search) {
	QLabel * centerWindow = new QLabel(tr("Searching"), this->mainWidget);
	centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	centerWindow->setAlignment(Qt::AlignCenter);

	int tabIndex = this->tabs->addTab(centerWindow, search);
	this->newSearchTab(tabIndex, search);
}

void main_window::MainWindow::openNewTabSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search in new tab");
	mainWindowState = main_window::MainWindow::state_e::OPEN_TAB;

}

void main_window::MainWindow::newSearchCurrentTab(QString search) {
	int tabIndex = this->tabs->currentIndex();
	this->newSearchTab(tabIndex, search);
}


void main_window::MainWindow::newSearchTab(int index, QString search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search " << search << " in tab " << index);
	this->tabs->setTabText(index, search);
}

void main_window::MainWindow::newSearchTabSlot() {

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "Search in current tab");
	mainWindowState = main_window::MainWindow::state_e::SEARCH;

}

// 
void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->tabs->currentWidget());
	currentWidget->setText(str);
	currentWidget->repaint();
}

void main_window::MainWindow::keyPressEvent(QKeyEvent * event) {

	QMainWindow::keyPressEvent(event);

	int pressedKey = event->key();

	if ((pressedKey == Qt::Key_Enter) || (pressedKey == Qt::Key_Return)) {
		if (this->userText.isEmpty()) {
			this->userText.append("No text provided");
		}

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "User typed text " << this->userText << " to search");

		if (mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) {
			this->addNewTab(this->userText);
		} else if (mainWindowState == main_window::MainWindow::state_e::SEARCH) {
			this->newSearchCurrentTab(this->userText);
		}
		this->userText.clear();
		mainWindowState = main_window::MainWindow::state_e::IDLE;
	} else {
		if ((mainWindowState == main_window::MainWindow::state_e::OPEN_TAB) || (mainWindowState == main_window::MainWindow::state_e::SEARCH)) {
			if (pressedKey == Qt::Key_Backspace) {
				// Last position of the string
				int endString = this->userText.count() - 1;
				this->userText.remove(endString, 1);
			} else {
				this->userText.append(event->text());
			}
		} else {
			this->userText.clear();
		}
	}

	this->mainWidget->repaint();
}
