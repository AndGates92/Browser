/**
 * @copyright
 * @file web_engine_view.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine view functions
 */

// Qt libraries
#include <QtGui/QKeyEvent>
#include <QtGui/QClipboard>
#include <QtWidgets/QMenu>
#include <QtWidgets/QApplication>
#include <QtWebEngineWidgets/QWebEngineHistory>

#include "app/widgets/commands/action.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/shared/setters_getters.h"
#include "app/shared/exception.h"
#include "app/windows/main_window/tabs/tab.h"
#include "app/windows/main_window/tabs/web_engine_view.h"
#include "app/windows/main_window/tabs/web_engine_page.h"

// Categories
LOGGING_CONTEXT(mainWindowWebEngineViewOverall, mainWindowWebEngineView.overall, TYPE_LEVEL, INFO_VERBOSITY)
LOGGING_CONTEXT(mainWindowWebEngineViewMenu, mainWindowWebEngineView.menu, TYPE_LEVEL, INFO_VERBOSITY)

app::main_window::tab::WebEngineView::WebEngineView(QWidget * parent, std::weak_ptr<app::main_window::tab::Tab> attachedTab, const app::main_window::page_type_e & type, const QString & src, const void * data): app::base::tab::WebEngineView(parent, attachedTab) {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineViewOverall, "Web engine view constructor");

	// Use deleteLater to schedule a destruction event in the event loop
	std::shared_ptr<app::main_window::tab::WebEnginePage> newPage = std::shared_ptr<app::main_window::tab::WebEnginePage>(new app::main_window::tab::WebEnginePage(parent, type, src, app::main_window::tab::WebEngineProfile::defaultProfile(), data), [] (app::main_window::tab::WebEnginePage * p) {
		p->deleteLater();
	});
	this->updatePage(newPage);

	this->connectSignals();
}

app::main_window::tab::WebEngineView::~WebEngineView() {
	LOG_INFO(app::logger::info_level_e::ZERO, mainWindowWebEngineViewOverall, "Web engine view destructor");
}

CASTED_SHARED_PTR_GETTER(app::main_window::tab::WebEngineView::page, app::main_window::tab::WebEnginePage, app::base::tab::WebEngineView::page())

CONST_CASTED_SHARED_PTR_GETTER(app::main_window::tab::WebEngineView::getTab, app::main_window::tab::Tab, app::base::tab::WebEngineView::getTab())

void app::main_window::tab::WebEngineView::connectSignals() {
	connect(this, &app::main_window::tab::WebEngineView::urlChanged, this, &app::main_window::tab::WebEngineView::updatePageSource, Qt::UniqueConnection);
}

void app::main_window::tab::WebEngineView::updatePageSource(const QUrl & url) {

	std::shared_ptr<app::main_window::tab::WebEnginePage> enginePage = this->page();

	if (enginePage != nullptr) {
		const app::main_window::page_type_e type = enginePage->getType();

		// Propagate URL only if page is of type WEB_CONTENT - if no URL is set, this function is called with about::black
		if ((type == app::main_window::page_type_e::WEB_CONTENT) && (url.isValid())) {
			const QString urlStr = url.toDisplayString(QUrl::FullyDecoded);
			enginePage->setSource(urlStr);
		}
	}
}

const std::string app::main_window::tab::WebEngineView::printActionMap() const {
	std::string actionListString = std::string();
	const app::main_window::tab::action_list_t::size_type numberOfActions = this->contextMenuExtraActions.size();
	app::main_window::tab::action_list_t::size_type counter = 0;
	if (numberOfActions == 0) {
		actionListString.append("Empty action map");
	} else {
		for (const auto & element : this->contextMenuExtraActions) {
			QAction * action = element.action;
			counter++;
			if ((action != nullptr) && (action->isSeparator() == false)) {
				actionListString.append(action->text().toStdString());
				if (counter < numberOfActions) {
					// From first to third last element
					actionListString.append(", ");
				}
			}
		}
	}

	return actionListString;
}

void app::main_window::tab::WebEngineView::enableMenuCustomAction(QMenu * menu) {

	// Enable or disable actions according to value of map
	const std::list<QAction *> menuActions(menu->actions().cbegin(), menu->actions().cend());
	for (const auto & extraAction : this->contextMenuExtraActions) {
		const auto & menuActionIt = std::find_if(menuActions.cbegin(), menuActions.cend(), [&extraAction] (const auto & menuAction) {
			return (app::shared::QActionCompare()(*(extraAction.action), *menuAction) == app::shared::QActionCompare()(*menuAction, *(extraAction.action)));
		});
		EXCEPTION_ACTION_COND((menuActionIt == menuActions.cend()), throw, "Unable to find action " << (*menuActionIt)->text() << " in action map: " << this->printActionMap());
		(*menuActionIt)->setEnabled(extraAction.enabled());
	}

}

void app::main_window::tab::WebEngineView::contextMenuEvent(QContextMenuEvent * event) {

	QMenu * contextMenu = this->page()->createStandardContextMenu();

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

	this->enableMenuCustomAction(contextMenu);

	const QPoint & position = event->pos();
	// Show context menu
	contextMenu->popup(position);

}
