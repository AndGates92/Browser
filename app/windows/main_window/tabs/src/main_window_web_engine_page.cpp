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

main_window_web_engine_page::MainWindowWebEnginePage::MainWindowWebEnginePage(QWidget * parent, const main_window_shared_types::page_type_e type, const QString & src, main_window_web_engine_profile::MainWindowWebEngineProfile * profile, const void * data): web_engine_page::WebEnginePage(parent, profile), pageData(main_window_page_data::MainWindowPageData::makePageData(type, src.toStdString(), data)) {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page constructor");

	this->setBody();
	if (src != QString::null) {
		emit this->sourceChanged(src);
	}

}

void main_window_web_engine_page::MainWindowWebEnginePage::setSource(const QString & src) {
	bool changed = this->pageData->setSource(src.toStdString());

	if (changed == true) {
		emit this->sourceChanged(src);
	}
}

void main_window_web_engine_page::MainWindowWebEnginePage::setBody() {

	main_window_shared_types::page_type_e type = this->getType();

	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
		{
			const QUrl url(this->getSource(), QUrl::StrictMode);
			QEXCEPTION_ACTION_COND((url.isValid() == false), throw,  "URL is not valid. The following error has been identified: " << url.errorString());
			this->setUrl(url);
			break;
		}
		case main_window_shared_types::page_type_e::TEXT:
			this->setContent(this->getTextFileBody());
			break;
		case main_window_shared_types::page_type_e::UNKNOWN:
			break;
		default:
			QEXCEPTION_ACTION(throw, "Unable to set body for this page as type " << type << " is not recognised");
			break;
	}
}

main_window_web_engine_page::MainWindowWebEnginePage::~MainWindowWebEnginePage() {
	QINFO_PRINT(global_enums::qinfo_level_e::ZERO, mainWindowWebEnginePageOverall,  "Web engine page destructor");
}

BASE_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getType, main_window_shared_types::page_type_e, this->pageData->type)
CONST_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getSource, QString, QString::fromStdString(this->pageData->source))
CONST_PTR_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getExtraData, void, this->pageData->data)
CONST_GETTER(main_window_web_engine_page::MainWindowWebEnginePage::getData, std::shared_ptr<main_window_page_data::MainWindowPageData> &, this->pageData)

void main_window_web_engine_page::MainWindowWebEnginePage::reload() {
	const main_window_shared_types::page_type_e type = this->getType();
	switch (type) {
		case main_window_shared_types::page_type_e::WEB_CONTENT:
			this->triggerAction(QWebEnginePage::Reload);
			break;
		case main_window_shared_types::page_type_e::TEXT:
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
		main_window_shared_types::page_type_e type = this->getType();
		QEXCEPTION_ACTION_COND((type != main_window_shared_types::page_type_e::TEXT), throw,  "Unable to get body of text file for tab of type " << type);
		// Convert QString to std::string
		std::string filename = source.toStdString();
		const QString fileContent(QString::fromStdString(global_functions::readFile(filename.c_str())));
		pageContent = fileContent.toUtf8();
	}

	return pageContent;
}

void main_window_web_engine_page::MainWindowWebEnginePage::setData(const std::shared_ptr<main_window_page_data::MainWindowPageData> newData) {
	this->pageData = newData;
	emit this->sourceChanged(QString::fromStdString(this->pageData->source));
}

void main_window_web_engine_page::MainWindowWebEnginePage::applyScrollRequest(const int x, const int y) {
	// Quite annoying work-around as QT C++ API doesn't allow the user to set the scroll position of a web page direction
	this->runJavaScript(QString("window.scrollTo(%1, %2)").arg(x).arg(y));
}
