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
#include "function_macros.h"
#include "global_functions.h"
#include "main_window_web_engine_page.h"

// Categories
Q_LOGGING_CATEGORY(mainWindowWebEnginePageOverall, "mainWindowWebEnginePage.overall", MSG_TYPE_LEVEL)

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(const main_window_shared_types::tab_type_e type, const QString & src, web_engine_profile::WebEngineProfile * profile, const void * data, QWidget * parent): web_engine_page::WebEnginePage(profile, parent), tabData(main_window_tab_data::MainWindowTabData::makeTabData(type, src.toStdString(), data)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

	this->setBody();
	emit this->sourceChanged(src);

}

void main_window_web_engine_page::MainWindowWebEnginePage::setSource(const QString & src) {
	bool changed = this->tabData->setSource(src.toStdString());

	if (changed == true) {
		emit this->sourceChanged(src);
	}
}

void main_window_web_engine_page::MainWindowWebEnginePage::setBody() {

	main_window_shared_types::tab_type_e type = this->getType();

	switch (type) {
		case main_window_shared_types::tab_type_e::WEB_CONTENT:
		{
			const QUrl url(this->getSource(), QUrl::TolerantMode);
			QEXCEPTION_ACTION_COND((url.isValid() == false), throw,  "URL is not valid. The following error has been identified: " << url.errorString());
			this->setUrl(url);
			break;
		}
		case main_window_shared_types::tab_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to set body for this page as type " << type << " is not recognised");
			break;
	}
}

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(QWidget * parent): web_engine_page::WebEnginePage(parent), tabData(main_window_tab_data::MainWindowTabData::makeTabData(main_window_shared_types::tab_type_e::UNKNOWN, std::string(), nullptr)) {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

}

main_window_web_engine_page::MainWindowWebEnginePage::~MainWindowWebEnginePage() {
	QINFO_PRINT(global_types::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page destructor");

	if (tabData != nullptr) {
		delete tabData;
	}

}

BASE_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getType, main_window_shared_types::tab_type_e, this->tabData->type)
CONST_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getSource, QString, QString::fromStdString(this->tabData->source))
CONST_PTR_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getExtraData, void, this->tabData->data)
CONST_PTR_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getData, main_window_tab_data::MainWindowTabData, this->tabData)

void main_window_web_engine_page::MainWindowWebEnginePage::reload() {
	const main_window_shared_types::tab_type_e type = this->getType();
	switch (type) {
		case main_window_shared_types::tab_type_e::WEB_CONTENT:
			this->triggerAction(QWebEnginePage::Reload);
			break;
		case main_window_shared_types::tab_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to reload page as type " << type << " is not recognised");
			break;
	}
}

QByteArray main_window_web_engine_page::MainWindowWebEnginePage::getTextFileBody() const {

	QByteArray pageContent(nullptr, -1);

	const QString source = this->getSource();

	if (source.isEmpty() == false) {
		main_window_shared_types::tab_type_e type = this->getType();
		QEXCEPTION_ACTION_COND((type != main_window_shared_types::tab_type_e::TEXT), throw,  "Unable to get body of text file for tab of type " << type);
		// Convert QString to std::string
		std::string filename = source.toStdString();
		const QString fileContent(QString::fromStdString(global_functions::readFile(filename.c_str())));
		pageContent = fileContent.toUtf8();
	}

	return pageContent;
}

void main_window_web_engine_page::MainWindowWebEnginePage::setData(const main_window_tab_data::MainWindowTabData * newData) {
	*(this->tabData) = *newData;
	emit this->sourceChanged(QString::fromStdString(this->tabData->source));
}
