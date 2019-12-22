/**
 * @copyright
 * @file main_window.cpp
 * @author Andrea Gianarda
 * @date 23th September 2019
 * @brief Main Window functions
 */

// Qt libraries
// QtGlobal defines qWarning
#include <qt5/QtCore/QtGlobal>
#include <qt5/QtWidgets/QGridLayout>
#include <qt5/QtWidgets/QStatusBar>
#include <qt5/QtWidgets/QShortcut>
#include <qt5/QtWidgets/QTabBar>
#include <qt5/QtWebEngineWidgets/QWebEngineView>
#include <qt5/QtCore/QUrl>
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
Q_LOGGING_CATEGORY(mainWindowUserInput, "mainWindow.userInput", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowSearch, "mainWindow.search", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowTabs, "mainWindow.tabs", MSG_TYPE_LEVEL)

main_window::MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	this->setFocusPolicy(Qt::StrongFocus);

	// main widget
	this->createMainWidget();

	// main window body
	this->fillMainWindow();

	// Control
	this->createCtrl();

	// Menu bar
	this->fillMenuBar();

	// Connect signals and slots
	this->connectSignals();

	// main window layout
	this->mainWindowLayout();

	QString msg(tr("status bar message"));
	this->statusBar()->showMessage(msg);
	this->statusBar()->hide();

	setWindowTitle(tr("Browser"));

	this->setStyleSheet(
		"QMainWindow {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);

	this->setAttribute(Qt::WA_DeleteOnClose);

	QSize winSize(320,400);
	this->resize(winSize);
}


void main_window::MainWindow::createMainWidget() {
	this->mainWidget = new QWidget(this);
	this->mainWidget->setAttribute(Qt::WA_DeleteOnClose);
//	this->mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->mainWidget->setFocusPolicy(Qt::StrongFocus);

	this->mainWidget->setStyleSheet(
		"QWidget {"
			"background: brown; "
			"color: white; "
			"text-align: center; "
			"border: none; "
		"}"
	);
	setCentralWidget(this->mainWidget);
}

QLabel * main_window::MainWindow::newWindowLabel() {
	QLabel * label = new QLabel("", this);
	label->setAttribute(Qt::WA_DeleteOnClose);
	label->setFrameStyle(QFrame::NoFrame | QFrame::Sunken);
	label->setFixedHeight(main_window::labelHeight);
	label->setStyleSheet(
		"QLabel {"
			"background: black; "
			"color: white; "
			"text-align: center; "
			"border-right: 1px solid black; "
			"border-left: 1px solid black; "
		"}"
	);

	return label;
}

void main_window::MainWindow::fillMainWindow() {
	// Customize MainWidget
	this->createTabs();

	// user input
	this->userInputText = this->newWindowLabel();
	this->userInputText->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
	this->userInputText->setFocus(Qt::OtherFocusReason);

	// website URL
	this->websiteText = this->newWindowLabel();
	this->websiteText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// info
	this->infoText = this->newWindowLabel();
	this->infoText->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	// Update info label
	updateInfo();
}

void main_window::MainWindow::createTabs() {
	this->tabs = new tab_widget::TabWidget(this->mainWidget);
	// size policy horintally and vertically to expanding
	this->tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

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

void main_window::MainWindow::mainWindowLayout() {
	// Layout
	// -------------------------------------------------
	// |                     <tabs>                    |
	// |                    <content>                  |
	// |  <search>   |      <website>     | <tab info> |
	// -------------------------------------------------

	QGridLayout * layout = new QGridLayout(this->mainWidget);
	int tabsRowSpan = 20;
	int tabsColumnSpan = 10;
	int tabsFromRow = 0;
	int tabsFromColumn = 0;
	layout->addWidget(this->tabs, tabsFromRow, tabsFromColumn, tabsRowSpan, tabsColumnSpan);
	int searchRowSpan = 1;
	int searchColumnSpan = 3;
	int searchFromRow = tabsRowSpan;
	int searchFromColumn = 0;
	layout->addWidget(this->userInputText, searchFromRow, searchFromColumn, searchRowSpan, searchColumnSpan);
	int websiteRowSpan = 1;
	int websiteColumnSpan = 5;
	int websiteFromRow = tabsRowSpan;
	int websiteFromColumn = searchFromColumn + searchColumnSpan;
	layout->addWidget(this->websiteText, websiteFromRow, websiteFromColumn, websiteRowSpan, websiteColumnSpan);
	int infoRowSpan = 1;
	int infoColumnSpan = 2;
	int infoFromRow = tabsRowSpan;
	int infoFromColumn = websiteFromColumn + websiteColumnSpan;
	layout->addWidget(this->infoText, infoFromRow, infoFromColumn, infoRowSpan, infoColumnSpan);

	layout->setHorizontalSpacing(main_window::horizontalWidgetSpacing);
	layout->setVerticalSpacing(main_window::verticalWidgetSpacing);
	layout->setContentsMargins(main_window::leftMargin, main_window::topMargin, main_window::rightMargin, main_window::bottomMargin);

	this->mainWidget->setLayout(layout);
}

void main_window::MainWindow::fillMenuBar() {
	this->fileMenu = new file_menu::FileMenu(this, this->menuBar(), "File", Qt::Key_F);
	this->editMenu = new edit_menu::EditMenu(this, this->menuBar(), "Edit", Qt::Key_E);
}

QMenuBar * main_window::MainWindow::getMenuBar() {
	return this->menuBar();
}

void main_window::MainWindow::connectSignals() {

	// When the file has been read, then show it on the screen
	connect(this->fileMenu, &file_menu::FileMenu::updateCenterWindowSignal, this, &main_window::MainWindow::setCenterWindow);

	// open tab action
	connect(this->fileMenu->openTabAction, &QAction::triggered, this->ctrl, &main_window_ctrl::MainWindowCtrl::openNewTab);

	// enable/disable file menu
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::enabledPropertyMenuSignal, this->fileMenu, &file_menu::FileMenu::setEnabledProperty);

	// enable/disable edit menu
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::enabledPropertyMenuSignal, this->editMenu, &edit_menu::EditMenu::setEnabledProperty);

	// Update info in the info bar following action
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::updateInfoActionSignal, this, &main_window::MainWindow::updateInfo);

	// Update website in info bar
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::updateWebsiteSignal, this, &main_window::MainWindow::updateWebsite);

	// Add tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::addNewTabSignal, this, &main_window::MainWindow::addNewTab);

	// Close tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeTabSignal, this, &main_window::MainWindow::closeTab);

	// Move tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::moveSignal, this, &main_window::MainWindow::move);

	// Search in current tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::searchCurrentTabSignal, this, &main_window::MainWindow::searchCurrentTab);

	// Refresh URL tab
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::refreshUrlSignal, this, &main_window::MainWindow::refreshUrl);

	// Update user input
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::updateUserInputBarSignal, this, &main_window::MainWindow::updateUserInputBar);

	// Close window
	connect(this->fileMenu->exitAction, &QAction::triggered, this, &main_window::MainWindow::closeWindow);
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::closeWindowSignal, this, &main_window::MainWindow::closeWindow);

	// show/hide menu bar
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::toggleShowMenubarSignal, this, &main_window::MainWindow::toggleShowMenubar);

	// share current tab index
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::requestCurrentTabIndexSignal, this, &main_window::MainWindow::getCurrentTabIndex);
	connect(this, &main_window::MainWindow::sendCurrentTabIndexSignal, this->ctrl, &main_window_ctrl::MainWindowCtrl::receiveCurrentTabIndex);

	// share tab count
	connect(this->ctrl, &main_window_ctrl::MainWindowCtrl::requestTabCountSignal, this, &main_window::MainWindow::getTabCount);
	connect(this, &main_window::MainWindow::sendTabCountSignal, this->ctrl, &main_window_ctrl::MainWindowCtrl::receiveTabCount);

	// Update info bar
	connect(this->tabs, &QTabWidget::currentChanged, this, &main_window::MainWindow::updateInfoSlot);
	connect(this->tabs, &QTabWidget::tabCloseRequested, this, &main_window::MainWindow::updateInfoSlot);
//	connect(this->tabs, &QTabWidget::currentChanged, this->ctrl, &main_window_ctrl::MainWindowCtrl::updateWebsite);

	// Disable/Enable menu shortcuts
	connect(this->tabs, &tab_widget::TabWidget::setShortcutEnabledPropertySignal, this->ctrl, &main_window_ctrl::MainWindowCtrl::setShortcutEnabledProperty);
}

void main_window::MainWindow::createCtrl() {
	// main window control class
	this->ctrl = new main_window_ctrl::MainWindowCtrl(this, this->tabs->currentIndex(), this->tabs->count());
}

void main_window::MainWindow::addNewTab(QString search) {
	QWebEngineView * centerWindow = new QWebEngineView(this->mainWidget);

	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Open tab with label " << search);
	int tabIndex = this->tabs->addTab(centerWindow, search);
	this->newSearchTab(tabIndex, search);

	// Move to the newly opened tab
	this->tabs->setCurrentIndex(tabIndex);

	// Update info label
	updateInfo();
}

void main_window::MainWindow::newSearchTab(int index, QString search) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowSearch,  "User input " << search << " in tab " << index);

	QWebEngineView * centerWindow = dynamic_cast<QWebEngineView *>(this->tabs->widget(index));

	bool containsSpace = search.contains(" ");
	bool containsWww = search.contains(main_window_ctrl::www);
	int numberDots = search.count(".");

	QString tabTitle = Q_NULLPTR;
	QString Url = Q_NULLPTR;

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		Url = main_window_ctrl::https;
		tabTitle = search;
		if (containsWww == true) {
			Url += search;
		} else {
			Url += main_window_ctrl::www + search;
		}
	} else {
		tabTitle = search;
		Url = main_window_ctrl::defaultSearchEngine.arg(search);
	}
	this->tabs->setTabText(index, tabTitle);
	centerWindow->setUrl(QUrl(Url));

	updateWebsite(index);
}

void main_window::MainWindow::searchCurrentTab(QString search) {
	int tabIndex = this->tabs->currentIndex();
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Search " << search << " in tab " << tabIndex);
	this->newSearchTab(tabIndex, search);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
// Function connected to both currentChanged and tabCloseRequested signals
// In the case of currentChanged signal, index is the current tab
// In the case of tabCloseRequested signal, index is the closed tab
void main_window::MainWindow::updateInfoSlot(int index) {
	updateInfo();
}
#pragma GCC diagnostic pop

void main_window::MainWindow::updateInfo() {
	QString info("");
	int tabIndex = this->tabs->currentIndex() + 1;
	int tabCount = this->tabs->count();
	if (tabCount == 0) {
		info.append("No tabs");
	} else {
		info.append("tab ");
		info.append(QString("%1").arg(tabIndex));
		info.append(" out of ");
		info.append(QString("%1").arg(tabCount));
	}
	this->infoText->setText(info);
}

void main_window::MainWindow::updateWebsite(int index) {

	int tabCount = this->tabs->count();

	if (tabCount > 0) {
		QWebEngineView * centerWindow = dynamic_cast<QWebEngineView *>(this->tabs->widget(index));
		QUrl websiteUrl = centerWindow->url();

		QString websiteStr (websiteUrl.toDisplayString(QUrl::FullyDecoded));
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Set URL in websiteText to " << websiteStr);
		this->websiteText->setText(websiteStr);
	} else {
		this->websiteText->clear();
	}
}

void main_window::MainWindow::setCenterWindow(QString str) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  "Change texts in center window");
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowCenterWindow,  str);
	// Convert back QWidget to QLabel
	QLabel * currentWidget = dynamic_cast<QLabel *>(this->tabs->currentWidget());
	currentWidget->setText(str);
	currentWidget->repaint();
}

void main_window::MainWindow::move(int offset, int sign, const main_window_shared_types::object_type_e & object) {

	Q_ASSERT_X(((sign == 0) || (sign == -1) || (sign == 1)), "main window move", "sign input must be either 0 or -1 or 1");
	// number of tabs to move by
	int distance = 0;
	// index is main_window_ctrl::emptyUserInput if the argument is not passed
	if (offset == main_window_ctrl::emptyUserInput) {
		distance = 1;
	} else {
		distance = offset;
	}

	int tabCount = this->tabs->count();
	int tabIndexCurrent = this->tabs->currentIndex();
	int tabIndexDst = 0;
	if (sign == 0) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = tabIndexCurrent + (sign * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		qWarning(mainWindowTabs) << "Offset " << offset << " is bigger than the number of tabs " << tabCount << " Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange << ")\n";
	}
	while (tabIndexDst < 0) {
		tabIndexDst +=  tabCount;
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	int tabIndex = tabIndexDst % tabCount;

	if (object == main_window_shared_types::object_type_e::CURSOR) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move to tab " << tabIndex << " distance " << distance << " on object " << object << " sign " << sign);
		this->tabs->setCurrentIndex(tabIndex);
	} else if (object == main_window_shared_types::object_type_e::TAB) {
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Move tab " << tabIndexCurrent << " to position " << tabIndex << " on object " << object << " sign " << sign);
		this->tabs->tabBar()->moveTab(tabIndexCurrent, tabIndex);
	}
}

void main_window::MainWindow::refreshUrl(int offset, int sign) {
	int distance = 0;
	// index is main_window_ctrl::emptyUserInput if the argument is not passed
	if (offset == main_window_ctrl::emptyUserInput) {
		distance = 1;
	} else {
		distance = offset;
	}

	int tabCount = this->tabs->count();
	int tabIndexCurrent = this->tabs->currentIndex();
	int tabIndexDst = 0;
	if (sign == 0) {
		tabIndexDst = distance;
	} else {
		tabIndexDst = tabIndexCurrent + (sign * distance);
	}
	if (offset > tabCount) {
		int maxTabRange = tabCount - 1;
		qWarning(mainWindowTabs) << "Offset " << offset << " is bigger than the number of tabs " << tabCount << " Bringing tab index withing the valid range of tab (between 0 and " << maxTabRange << ")\n";
	}

	// Keep tabIndex values within valid range (0 and (tabCount -1))
	int tabIndex = tabIndexDst % tabCount;

	QWebEngineView * centerWindow = dynamic_cast<QWebEngineView *>(this->tabs->widget(tabIndex));
	QUrl currUrl = centerWindow->url();

	centerWindow->setUrl(QUrl(currUrl));

}

void main_window::MainWindow::closeTab(int index) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowTabs,  "Close tab " << index);
	this->tabs->removeTab(index);
}

void main_window::MainWindow::updateUserInputBar(QString textLabel) {
	if (textLabel == Q_NULLPTR) {
		this->userInputText->clear();
	} else {
		this->userInputText->setText(textLabel);
	}
}

void main_window::MainWindow::closeWindow() {
	this->close();
}

void main_window::MainWindow::toggleShowMenubar() {
	bool menubarVisible = this->menuBar()->isVisible();
	this->menuBar()->setVisible(!menubarVisible);
}

void main_window::MainWindow::getCurrentTabIndex() {
	emit sendCurrentTabIndexSignal(this->tabs->currentIndex());
}

void main_window::MainWindow::getTabCount() {
	emit sendTabCountSignal(this->tabs->count());
}

void main_window::MainWindow::keyPressEvent(QKeyEvent * event) {

	QMainWindow::keyPressEvent(event);

	ctrl->keyPressEvent(event);

	this->mainWidget->repaint();
}
