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

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(const main_window_shared_types::tab_type_e type, const void * data, const void * tabContent, web_engine_profile::WebEngineProfile * profile, QWidget * parent): web_engine_page::WebEnginePage(profile, parent), tabData(main_window_tab_data::MainWindowTabData::makeTabData(type, data)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

	this->setBody(type, tabContent);

}

void main_window_web_engine_page::MainWindowWebEnginePage::setBody(const main_window_shared_types::tab_type_e & type, const void * content) {

	if (type == main_window_shared_types::tab_type_e::WEB_ENGINE) {
		const QString * search = static_cast<const QString *>(content);
		QUrl url(this->createUrl(*search));
		this->setUrl(url);
	} else if (type == main_window_shared_types::tab_type_e::LABEL) {
		const QString * contentPtr = static_cast<const QString *>(content);
		const QByteArray content = contentPtr->toUtf8();
		this->setContent(content);
	} else {
		QEXCEPTION_ACTION(throw, "Unable to set body for this page as type " << type << " is not recognised");
	}
}

const QUrl main_window_web_engine_page::MainWindowWebEnginePage::createUrl(const QString & search) const {
	const bool containsSpace = search.contains(" ");
	const bool containsWww = search.contains(main_window_web_engine_page::www);
	const int numberDots = search.count(".");

	QString urlStr(QString::null);

	// if contains at least 1 dot and no space, it could be a URL
	if ((numberDots > 0) && (containsSpace == false)) {
		urlStr = main_window_web_engine_page::https;
		if (containsWww == true) {
			urlStr += search;
		} else {
			urlStr += main_window_web_engine_page::www + search;
		}
	} else {
		urlStr = main_window_web_engine_page::defaultSearchEngine.arg(search);
	}

	const QUrl url(urlStr);

	return url;
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
