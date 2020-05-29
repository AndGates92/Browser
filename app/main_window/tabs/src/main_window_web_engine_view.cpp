/**
 * @copyright
 * @file main_window_web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>
#include <qt5/QtWidgets/QMenu>
#include <qt5/QtWebEngineWidgets/QWebEngineHistory>

#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"
#include "main_window_web_engine_view.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineViewOverall, "mainWindowWebEngineView.overall", MSG_TYPE_LEVEL)

main_window_web_engine_view::MainWindowWebEngineView::MainWindowWebEngineView(QWidget * parent, const main_window_shared_types::page_type_e type, const QString & src, const void * data): web_engine_view::WebEngineView(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view constructor");

	main_window_web_engine_page::MainWindowWebEnginePage * page = new main_window_web_engine_page::MainWindowWebEnginePage(parent, type, src, main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile(), data);
	this->setPage(page);

	this->connectSignals();
}

main_window_web_engine_view::MainWindowWebEngineView::~MainWindowWebEngineView() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view destructor");

}

CASTED_PTR_GETTER(main_window_web_engine_view::MainWindowWebEngineView::page, main_window_web_engine_page::MainWindowWebEnginePage, web_engine_view::WebEngineView::page())

void main_window_web_engine_view::MainWindowWebEngineView::connectSignals() {
	connect(this, &main_window_web_engine_view::MainWindowWebEngineView::urlChanged, this, &main_window_web_engine_view::MainWindowWebEngineView::updatePageSource, Qt::UniqueConnection);
}

void main_window_web_engine_view::MainWindowWebEngineView::updatePageSource(const QUrl & url) {

	main_window_web_engine_page::MainWindowWebEnginePage * enginePage = this->page();

	const main_window_shared_types::page_type_e type = enginePage->getType();

	// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
	if ((type == main_window_shared_types::page_type_e::WEB_CONTENT) && (url.isValid())) {
		const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
		enginePage->setSource(urlStr);
	}
}

bool main_window_web_engine_view::MainWindowWebEngineView::isSameAction(const QAction * lhs, const QAction * rhs) const {
	const QList<QKeySequence> keyList1(lhs->shortcuts());
	const QList<QKeySequence> keyList2(rhs->shortcuts());

	if (keyList1.size() != keyList2.size()) {
		return false;
	}

	for(QList<QKeySequence>::const_iterator keyIt1 = keyList1.cbegin(), keyIt2 = keyList2.cbegin(); (keyIt1 != keyList1.cend() && keyIt2 != keyList2.cend()); keyIt1++, keyIt2++) {
		if ((*keyIt1) != (*keyIt2)) {
			return false;
		}
	}

	// Discard mnemonic that could cause comparison to mismatch
	QString lhsText(lhs->text().replace(QString("&"), QString("")));
	QString rhsText(rhs->text().replace(QString("&"), QString("")));

	if (QString::compare(lhsText, rhsText, Qt::CaseSensitive) != 0) {
			return false;
	}

	return true;

}

void main_window_web_engine_view::MainWindowWebEngineView::contextMenuEvent(QContextMenuEvent * event) {
	QMenu * contextMenu(this->page()->createStandardContextMenu());

	contextMenu->setStyleSheet(
		"QMenu {"
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
		"QMenu::item {"
			// Backgorund color to be transparent to be the same as the menu color
			"background: transparent; "
		"}"
		"QMenu::item::selected {"
			// Set a gray background color when hovering items with the mouse
			"background: grey; "
		"}"
		"QMenu::item::disabled {"
			// Gray out disabled items
			"color: gray; "
		"}"
	);

	const QList<QAction *> actions(contextMenu->actions());

	for(QList<QAction *>::const_iterator actionIt = actions.cbegin(); actionIt != actions.cend(); actionIt++) {
		QAction * action(*actionIt);
		// Eliminates mnemonic shortcuts
		action->setText(action->text().replace(QString("&"), QString("")));
		QFont actionFont(action->font());
		if (this->isSameAction(action, this->page()->action(QWebEnginePage::Forward)) == true) {
			action->setEnabled(this->history()->canGoForward());
		}
		action->setFont(actionFont);
	}

	contextMenu->popup(event->globalPos());

}
