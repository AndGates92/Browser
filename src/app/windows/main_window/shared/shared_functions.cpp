/**
 * @copyright
 * @file shared_functions.cpp
 * @author Andrea Gianarda
 * @date 2nd June 2020
 * @brief Main Window Shared Functions
 */

// Qt libraries
#include <QtCore/QFile>
#include <QtCore/QUrl>

#include "app/shared/constants.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/windows/main_window/shared/shared_functions.h"
#include "app/windows/main_window/shared/constants.h"

bool app::main_window::isUrl(const QString & text) {

	const bool containsWww = text.contains(app::shared::www);
	const bool containsHttps = text.contains(app::shared::https);

	// Check also the number of dots in the argument text.
	// In fact QUrl considers as valid an URL that is missing the .TLD (example .com)
	// For example, if text is "cc", the URL built by this method is https://www.cc. It is considered a valid URL by QT whereas it is not
	QString urlStr = QString();

	if (containsHttps == false) {
		urlStr += app::shared::https;
	}

	if (containsWww == false) {
		urlStr += app::shared::www;
	}

	urlStr += text;

	QUrl url(urlStr, QUrl::StrictMode);

	const int numberDots = text.count(".");

	return ((url.isValid() == true) && (numberDots > 0));
}

bool app::main_window::isFile(const QString & text) {
	QFile file(text);
	return file.exists();
}

bool app::main_window::isText(const QString & text) {
	bool validUrl = app::main_window::isUrl(text);
	bool validFile = app::main_window::isFile(text);

	return ((validUrl == false) && (validFile == false));
}

app::main_window::page_type_e app::main_window::textToPageType(const QString & text) {
	app::main_window::page_type_e type = app::main_window::page_type_e::UNKNOWN;
	if (app::main_window::isFile(text) == true) {
		type = app::main_window::page_type_e::TEXT;
	} else if ((app::main_window::isUrl(text) == true) || (app::main_window::isText(text) == true)) {
		type = app::main_window::page_type_e::WEB_CONTENT;
	} else {
		EXCEPTION_ACTION(throw, "Unable to associate a page type to text " << text);
	}
	return type;
}

QString app::main_window::deletePrefix(QString text) {
	const QString filePrefix(app::main_window::filePrefix);
	if (text.contains(filePrefix) == true) {
		text.remove(filePrefix, Qt::CaseSensitive);
	}
	return text;
}
