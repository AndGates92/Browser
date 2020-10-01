/**
 * @copyright
 * @file main_window_web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <QtCore/QLoggingCategory>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QMenu>
#include <QtWebEngineWidgets/QWebEngineHistory>

#include "logging_macros.h"
#include "function_macros.h"
#include "exception_macros.h"
#include "main_window_web_engine_view.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineViewOverall, "mainWindowWebEngineView.overall", MSG_TYPE_LEVEL)

main_window_web_engine_view::MainWindowWebEngineView::MainWindowWebEngineView(QWidget * parent, const main_window_shared_types::page_type_e & type, const QString & src, const void * data): web_engine_view::WebEngineView(parent) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view constructor");

	// Use deleteLater to schedule a destruction event in the event loop
	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> newPage = std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage>(new main_window_web_engine_page::MainWindowWebEnginePage(parent, type, src, main_window_web_engine_profile::MainWindowWebEngineProfile::defaultProfile(), data), [] (main_window_web_engine_page::MainWindowWebEnginePage * p) {
		p->deleteLater();
	});
	this->updatePage(newPage);

	this->connectSignals();
}

main_window_web_engine_view::MainWindowWebEngineView::~MainWindowWebEngineView() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEngineViewOverall,  "Web engine view destructor");
}

CASTED_SHARED_PTR_GETTER(main_window_web_engine_view::MainWindowWebEngineView::page, main_window_web_engine_page::MainWindowWebEnginePage, web_engine_view::WebEngineView::page())

void main_window_web_engine_view::MainWindowWebEngineView::connectSignals() {
	connect(this, &main_window_web_engine_view::MainWindowWebEngineView::urlChanged, this, &main_window_web_engine_view::MainWindowWebEngineView::updatePageSource, Qt::UniqueConnection);
}

void main_window_web_engine_view::MainWindowWebEngineView::updatePageSource(const QUrl & url) {

	std::shared_ptr<main_window_web_engine_page::MainWindowWebEnginePage> enginePage = this->page();

	if (enginePage != nullptr) {
		const main_window_shared_types::page_type_e type = enginePage->getType();

		// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
		if ((type == main_window_shared_types::page_type_e::WEB_CONTENT) && (url.isValid())) {
			const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
			enginePage->setSource(urlStr);
		}
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
		} else if (this->isSameAction(action, this->page()->action(QWebEnginePage::Back)) == true) {
			action->setEnabled(this->history()->canGoBack());
		}

		action->setFont(actionFont);
	}

	if (this->hasSelection() == true) {
		std::list<QWebEnginePage::WebAction> actionsToAdd;
		actionsToAdd.push_back(QWebEnginePage::Cut);
		actionsToAdd.push_back(QWebEnginePage::Copy);
		actionsToAdd.push_back(QWebEnginePage::Paste);

		QAction * separator(contextMenu->addSeparator());

		QList<QAction *>::const_iterator actionIt = actions.cbegin();
		QAction * action(*actionIt);

		QList<QAction *> actionList;

		for (std::list<QWebEnginePage::WebAction>::const_iterator newActionIt = actionsToAdd.cbegin(); newActionIt != actionsToAdd.cend(); ++newActionIt) {
			if (newActionIt == actionsToAdd.cbegin()) {
				actionList.clear();
			}

			QWebEnginePage::WebAction webAction(*newActionIt);
			if (webAction == QWebEnginePage::NoWebAction) {
				// Add separator to the list. If we it this line, it means that we have more elements coming next
				actionList.append(separator);
				action = this->addActionListToMenu(contextMenu, action, actionList);

				// Clear list
				actionList.clear();

			} else {
				actionList.append(this->page()->action(webAction));
			}
		}

		if (actions.empty() == false) {
			// Add separator to the list. If we it this line, it means that we have more elements coming next
			actionList.append(separator);
		}
		this->addActionListToMenu(contextMenu, action, actionList);
	}

	contextMenu->popup(event->globalPos());

}

QAction * main_window_web_engine_view::MainWindowWebEngineView::addActionListToMenu(QMenu * menu, QAction * pos, const QList<QAction *> & actionList) {

	QAction * action(pos);
	const QList<QAction *> actions(menu->actions());

	// Only add actions if list is not empty
	if (actionList.empty() == false) {

		menu->insertActions(action, actionList);

		// get iterator of next item after the last added
		// 1. Get iterator over last added element
		QList<QAction *>::const_iterator posIt = actionList.cend();

		// 2. Find last added element in the action list
		const QList<QAction *> actionTmp(menu->actions());
		posIt = std::find(actionTmp.cbegin(), actionTmp.cend(), *posIt);

		// 3. Increment iterator by 1 to compute the element next set of action must be appended before
		posIt++;
		if (posIt == actionTmp.cend()) {
			// Reached end of list of actions
			action = Q_NULLPTR;
		} else {
			action = *posIt;
		}
	}

	return action;
}
