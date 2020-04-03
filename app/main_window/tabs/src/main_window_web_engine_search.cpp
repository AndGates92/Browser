/**
 * @copyright
 * @file main_window_web_engine_search.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine search functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include <qt5/QtWidgets/QMessageBox>

#include "logging_macros.h"
#include "main_window_web_engine_search.h"
#include "main_window_web_engine_view.h"
#include "main_window_tab.h"
#include "exception_macros.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEngineSearchOverall, "mainWindowWebEngineSearch.overall", MSG_TYPE_LEVEL)
Q_LOGGING_CATEGORY(mainWindowWebEngineSearchFind, "mainWindowWebEngineSearch.find", MSG_TYPE_LEVEL)

main_window_web_engine_search::MainWindowWebEngineSearch::MainWindowWebEngineSearch(QWidget * attachedTab, QObject * parent): web_engine_search::WebEngineSearch(attachedTab, parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchOverall,  "Web engine search constructor");

}

main_window_web_engine_search::MainWindowWebEngineSearch::~MainWindowWebEngineSearch() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchOverall,  "Web engine search destructor");

}

void main_window_web_engine_search::MainWindowWebEngineSearch::FindTabContent(const QString & search, const bool & reverse, const bool & caseSensitive, void (* callback)(bool)) {

	try {
		main_window_tab::MainWindowTab * currentTab = dynamic_cast<main_window_tab::MainWindowTab *>(this->tab);
		main_window_web_engine_view::MainWindowWebEngineView * currentTabView = currentTab->widgetView;
		QWebEnginePage * currentTabPage = currentTabView->page();
		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchFind,  "DEBUG Searching " << search);

		// Declare here the callback to improve readability
		auto wrapperCallback = [&](bool found) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchFind,  "DEBUG Callback find");
			if (found) {
				QMessageBox::information(currentTabView,  QString(), QString("DADA"), QMessageBox::NoButton, QMessageBox::NoButton);
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchFind,  "DEBUG Found");
			} else {
				QMessageBox::information(currentTabView,  QString(), QString("NOT DADA"), QMessageBox::NoButton, QMessageBox::NoButton);
				QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchFind,  "DEBUG not Found");
			}

			callback(found);
		};

		// No flag set by default
		// Available search flags are:
		// - QWebEnginePage::FindBackward
		// - QWebEnginePage::FindCaseSensitively
		QWebEnginePage::FindFlags options = QWebEnginePage::FindFlag(0);
		if (reverse == true) {
			options |= QWebEnginePage::FindBackward;
		}

		if (caseSensitive == true) {
			options |= QWebEnginePage::FindCaseSensitively;
		}

		currentTabPage->findText(search, options,
			[&](bool found) {
				wrapperCallback(found);
			}
		);

		QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEngineSearchFind,  "DEBUG Selection " << currentTabView->selectedText());

	} catch (const std::bad_cast & badCastE) {
		QEXCEPTION_ACTION(throw, badCastE.what());
	}

}

