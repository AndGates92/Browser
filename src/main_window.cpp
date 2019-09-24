/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
#include <qt5/QtWidgets/QMainWindow>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QMenuBar>
#include <qt5/QtWidgets/QMenu>

#include <qt5/QtCore/QLoggingCategory>

// Required by qInfo
#include <qt5/QtCore/QtDebug>

#include <qt5/QtCore/QObject>

#include "global_macros.h"
#include "global_types.h"
#include "main_window.h"


// Categories
Q_LOGGING_CATEGORY(mainWindowOverall, "mainWindow.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowFileMenu, "mainWindow.menu.file", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowEditMenu, "mainWindow.menu.edit", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow() {

	QWidget * mainWidget = new QWidget();
	setCentralWidget(mainWidget);

	QWidget * topWidget = new QWidget();
	// size policy horintally and vertically to expanding
	topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	this->centerWindow = new QLabel(tr("Example"));
	this->centerWindow->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->centerWindow->setAlignment(Qt::AlignCenter);

	QWidget * bottomWidget = new QWidget();
	// size policy horintally and vertically to expanding
	bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout * layout = new QVBoxLayout;
	layout->setContentsMargins(5,5,5,5);
	layout->addWidget(topWidget);
	layout->addWidget(centerWindow);
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
}

void main_window::MainWindow::undoSlot() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowEditMenu,  "undo slot");
}
