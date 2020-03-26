/**
 * @copyright
 * @file logging.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Logging functions
 */

#include <qt5/QtCore/QMessageLogContext>
#include <qt5/QtCore/QTextStream>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QtGlobal>

// Get pointer to default category
#include <qt5/QtCore/QLoggingCategory>

#include "exception_macros.h"
#include "logging_macros.h"
#include "logging.h"

/**
	* @brief bottom information label height
	* QtMsgType
	* | Name          | Value  |
	* |---------------|--------|
	* | QtDebugMsg    | 0      |
	* | QtInfoMsg     | 4      |
	* | QtWarningMsg  | 1      |
	* | QtCritcalMsg  | 2      |
	* | QtFatalMsg    | 3      |
	* Enable messge level if:
	* - MSG_LEVEL_TYPE is set to QtInfoMsg and trying to enable QtDebugMsg
	* - MSG_LEVEL_TYPE is set to QtDebugMsg
	* - MSG_LEVEL_TYPE is not set to QtDebugMsg or QtInfoMsg and not trying to enable QtInfoMsg and MsgLevel is larger than MSG_TYPE_LEVEL
*/
#define SetMsgLevel(MsgLevel, Category) \
	if (Category != Q_NULLPTR) { \
		if (((MsgLevel != QtDebugMsg) && (static_cast<QtMsgType>(MSG_TYPE_LEVEL) == QtInfoMsg)) || \
		    (static_cast<QtMsgType>(MSG_TYPE_LEVEL) == QtDebugMsg) || \
		    ((static_cast<QtMsgType>(MSG_TYPE_LEVEL) != QtDebugMsg) && (static_cast<QtMsgType>(MSG_TYPE_LEVEL) != QtInfoMsg) && (MsgLevel >= static_cast<QtMsgType>(MSG_TYPE_LEVEL)) && (MsgLevel != QtDebugMsg)) \
		) { \
			Category->setEnabled(MsgLevel, true); \
		} else { \
			Category->setEnabled(MsgLevel, false); \
		} \
	}

void logging::handler(QtMsgType type, const QMessageLogContext & context, const QString & message) {

	QString info_str("");

	// CategoryFunction
	if (context.category != Q_NULLPTR) {
		info_str.append("[");
		info_str.append(context.category);
		info_str.append("] ");
	}

	// Filename
	if (context.file != Q_NULLPTR) {
		info_str.append("File ");
		info_str.append(context.file);
	}

	// Function
	if (context.function != Q_NULLPTR) {
		info_str.append(" in function ");
		info_str.append(context.function);
	}

	bool success = logfile.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text);
	QEXCEPTION_ACTION_COND((!success), throw, "Unable to open file " << logfile.fileName());

	QTextStream ologfile(&logfile);

	switch(type) {
		case QtDebugMsg:
			ologfile << "Debug" << info_str << " " << message << endl;
			break;
		case QtInfoMsg:
			ologfile << "Info" << info_str << " " << message <<  endl;
			break;
		case QtWarningMsg:
			ologfile << "Warning" << info_str << " " << message << endl;
			break;
		case QtCriticalMsg:
			ologfile << "Critical" << info_str << " " << message << endl;
			break;
		case QtFatalMsg:
			ologfile << "Fatal" << info_str << " " << message << endl;
			break;
	}

	logfile.close();

}

void logging::set_default_category() {
	QLoggingCategory * defaultMsgCategory = QLoggingCategory::defaultCategory();

	// Fatal cannpt be disabled therefore not trying to enable it here
	SetMsgLevel(QtDebugMsg, defaultMsgCategory)
	SetMsgLevel(QtInfoMsg, defaultMsgCategory)
	SetMsgLevel(QtWarningMsg, defaultMsgCategory)
	SetMsgLevel(QtCriticalMsg, defaultMsgCategory)

}
