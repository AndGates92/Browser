/**
 * @copyright
 * @file main_window_web_engine_page.cpp
 * @author Andrea Gianarda
 * @date 02rd April 2020
 * @brief Web engine page functions
 */

// Qt libraries
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtGui/QKeyEvent>

#include "logging_macros.h"
#include "main_window_web_engine_page.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEnginePageOverall, "mainWindowWebEnginePage.overall", MSG_TYPE_LEVEL)

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(const main_window_shared_types::tab_type_e type, const void * tabContent, web_engine_profile::WebEngineProfile * profile, QWidget * parent): web_engine_page::WebEnginePage(profile, parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		const QUrl * urlPtr = static_cast<const QUrl *>(tabContent);
		const QUrl url = *urlPtr;
		this->setUrl(url);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		const QString * contentPtr = static_cast<const QString *>(tabContent);
		const QByteArray content = contentPtr->toUtf8();
		this->setContent(content);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to add tab page as the provided tab type " << type << " is not recognized");
	}

}

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(QWidget * parent): web_engine_page::WebEnginePage(parent) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

}

main_window_web_engine_page::MainWindowWebEnginePage::~MainWindowWebEnginePage() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page destructor");

}
