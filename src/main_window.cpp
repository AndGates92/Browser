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

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "open_button_window.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowFileMenu, "mainWindow.menu.file", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowEditMenu, "mainWindow.menu.edit", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	QWidget * mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);

	QWidget * topWidget = new QWidget(mainWidget);
	// size policy horintally and vertically to expanding
	topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->centerWindow = new QLabel(tr("Example"), mainWidget);
	this->centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->centerWindow->setAlignment(Qt::AlignCenter);

	QWidget * bottomWidget = new QWidget(mainWidget);
	// size policy horintally and vertically to expanding
	bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout * layout = new QVBoxLayout(mainWidget);
	layout->setContentsMargins(5,5,5,5);
	layout->addWidget(topWidget);
	layout->addWidget(this->centerWindow);
	layout->addWidget(bottomWidget);

	mainWidget->setLayout(layout);

	this->fileMenu = new file_menu::FileMenu(this, this->menuBar());
	this->editMenu = new edit_menu::EditMenu(this, this->menuBar());
	this->createShortcuts();

	QString msg = tr("status bar message");
	statusBar()->showMessage(msg);

	setWindowTitle(tr("Browser"));

	QSize winSize(320,400);
	resize(winSize);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::createShortcuts() {
	// m will hide/show the menu bar
	QShortcut * hideMenuBar = new QShortcut(this);
	hideMenuBar->setKey(Qt::Key_M);
	connect(hideMenuBar, SIGNAL(activated()), this, SLOT(disableMenubar()));
}

void main_window::MainWindow::disableMenubar() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}
