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
#include <qt5/QtWidgets/QMenuBar>

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

	QWidget * topWidget = new QWidget(this);
	// size policy horintally and vertically to expanding
	topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->centerWindow = new QLabel(tr("Example"), this);
	this->centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->centerWindow->setAlignment(Qt::AlignCenter);

	QWidget * bottomWidget = new QWidget(this);
	// size policy horintally and vertically to expanding
	bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout * layout = new QVBoxLayout(this);
	layout->setContentsMargins(5,5,5,5);
	layout->addWidget(topWidget);
	layout->addWidget(this->centerWindow);
	layout->addWidget(bottomWidget);

	mainWidget->setLayout(layout);

	this->createActions();
	this->createTopMenu();

	QString msg = tr("status bar message");
	statusBar()->showMessage(msg);

	setWindowTitle(tr("Browser"));

	QSize winSize(320,400);
	resize(winSize);
}

void main_window::MainWindow::createActions() {

	// File menu
	this->openAction = new QAction(tr("Open"), this);
	this->openAction->setStatusTip(tr("Open URL"));
	connect(this->openAction, &QAction::triggered, this, &MainWindow::openSlot);

	// Edit menu
	this->undoAction = new QAction(tr("Undo"), this);
	this->undoAction->setStatusTip(tr("Undo previous action"));
	connect(this->undoAction, &QAction::triggered, this, &MainWindow::undoSlot);
}

void main_window::MainWindow::createTopMenu() {

	// File
	this->fileMenu = menuBar()->addMenu(tr("File"));
	this->fileMenu->addAction(openAction);

	// Edit
	this->editMenu = menuBar()->addMenu(tr("Edit"));
	this->editMenu->addAction(undoAction);
}

void main_window::MainWindow::openSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowFileMenu,  "open slot");

	open_button_window::OpenButtonWindow OpenWindow(this, Qt::Dialog);
	OpenWindow.exec();
}

void main_window::MainWindow::undoSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowEditMenu,  "undo slot");
}
