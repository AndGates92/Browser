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
#include "global_functions.h"
#include "main_window_web_engine_page.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEnginePageOverall, "mainWindowWebEnginePage.overall", MSG_TYPE_LEVEL)

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(const main_window_shared_types::tab_type_e type, const QString & src, const void * content, web_engine_profile::WebEngineProfile * profile, const void * data, QWidget * parent): web_engine_page::WebEnginePage(profile, parent), source(src), tabData(main_window_tab_data::MainWindowTabData::makeTabData(type, data)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

	this->setBody(type, content);

}

void main_window_web_engine_page::MainWindowWebEnginePage::setSource(const QString & src) {
	if (this->source != src) {
		this->source = src;
		emit srcChanged(this->source);
	}
}

void main_window_web_engine_page::MainWindowWebEnginePage::setBody(const main_window_shared_types::tab_type_e & type, const void * content) {

	if (type == main_window_shared_types::tab_type_e::WEB_CONTENT) {
		const QUrl * urlPtr = static_cast<const QUrl *>(content);
		QUrl url(*urlPtr);
		this->setUrl(url);
	} else if (type == main_window_shared_types::tab_type_e::TEXT) {
		const QString * contentPtr = static_cast<const QString *>(content);
		const QByteArray content = contentPtr->toUtf8();
		this->setContent(content);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to set body for this page as type " << type << " is not recognised");
	}
}

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(QWidget * parent): web_engine_page::WebEnginePage(parent), tabData(main_window_tab_data::MainWindowTabData::makeTabData(main_window_shared_types::tab_type_e::UNKNOWN, nullptr)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

}

main_window_web_engine_page::MainWindowWebEnginePage::~MainWindowWebEnginePage() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page destructor");

	if (tabData != nullptr) {
		delete tabData;
	}

}

main_window_tab_data::MainWindowTabData * main_window_web_engine_page::MainWindowWebEnginePage::getTabData() const {
	return this->tabData;
}

main_window_shared_types::tab_type_e main_window_web_engine_page::MainWindowWebEnginePage::getTabType() const {
	return this->tabData->getType();
}

const void * main_window_web_engine_page::MainWindowWebEnginePage::getTabExtraData() const {
	return this->tabData->getData();
}

const QString main_window_web_engine_page::MainWindowWebEnginePage::getSource() const {
	return this->source;
}

void main_window_web_engine_page::MainWindowWebEnginePage::reload() {
	const main_window_shared_types::tab_type_e type = this->getTabType();
	if (type == main_window_shared_types::tab_type_e::WEB_CONTENT) {
		this->triggerAction(QWebEnginePage::Reload);
	} else if (type == main_window_shared_types::tab_type_e::TEXT) {
		// Retrive filename
		const void * tabData = this->getTabExtraData();
		const char * filename = static_cast<const char *>(tabData);
		const QString content(QString::fromStdString(global_functions::readFile(filename)));
		this->setContent(content.toUtf8());

	}
}
