/**
 * @copyright
 * @file main_window_shared_functions.cpp
 * @author Andrea Gianarda
 * @date 2nd June 2020
 * @brief Main Window Shared Functions
 */

// Qt libraries
#include <QtCore/QFile>
#include <QtCore/QUrl>

#include "global_constants.h"
#include "main_window_shared_functions.h"

bool main_window_shared_functions::isUrl(const QString & text) {

	const bool containsWww = text.contains(global_constants::www);
	const bool containsHttps = text.contains(global_constants::https);

	// Check also the number of dots in the argument text.
	// In fact QUrl considers as valid an URL that is missing the .TLD (example .com)
	// For example, if text is "cc", the URL built by this method is https://www.cc. It is considered a valid URL by QT whereas it is not
	QString urlStr = QString();

	if (containsHttps == false) {
		urlStr += global_constants::https;
	}

	if (containsWww == false) {
		urlStr += global_constants::www;
	}

	urlStr += text;

	QUrl url(urlStr, QUrl::StrictMode);

	const int numberDots = text.count(".");

	return ((url.isValid() == true) && (numberDots > 0));
}

bool main_window_shared_functions::isFile(const QString & text) {
	QFile file(text);
	return file.exists();
}

bool main_window_shared_functions::isText(const QString & text) {
	bool validUrl = main_window_shared_functions::isUrl(text);
	bool validFile = main_window_shared_functions::isFile(text);

	return ((validUrl == false) && (validFile == false));
}
