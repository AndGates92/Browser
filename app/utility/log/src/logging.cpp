/**
 * @copyright
 * @file logging.cpp
 * @author Andrea Gianarda
 * @date 17th September 2019
 * @brief Logging functions
 */

#include <mutex>

// Qt libraries
#include <QtCore/QtGlobal>
#include <QtCore/QTextStream>

// Get pointer to default category
#include <QtCore/QLoggingCategory>

#include "utility/stl/include/cpp_operator.h"
#include "common/include/logging_functions.h"
#include "common/include/exception_macros.h"
#include "common/include/logging_macros.h"
#include "utility/log/include/logging.h"

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

/**
 * @brief Qt log filename
 *
 */
#if !defined(QT_LOGFILE)
	#define QT_LOGFILE browser.qt.log
#endif

namespace logging {

	namespace {
		/**
		 * @brief Global variable logfile
		 *
		 */
		QFile logfile(QT_STRINGIFY(QT_LOGFILE));

		/**
		 * @brief mutex to handle concurrent access to logfile
		 *
		 */
		std::mutex logfile_mutex;
	}

}

void logging::handler(QtMsgType type, const QMessageLogContext & context, const QString & message) {

	logfile_mutex.lock();

	QString info_str("");

	info_str.append("[");
	info_str.append(logging_functions::getDateTime());
	info_str.append("] ");

	switch(type) {
		case QtDebugMsg:
			info_str.append("DEBUG ");
			break;
		case QtInfoMsg:
			info_str.append("INFO ");
			break;
		case QtWarningMsg:
			info_str.append("WARNING ");
			break;
		case QtCriticalMsg:
			info_str.append("CRITICAL ");
			break;
		case QtFatalMsg:
			info_str.append("FATAL ");
			break;
		default:
			info_str.append("UNKNOWN TYPE ");
			break;
	}

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
	EXCEPTION_ACTION_COND((!success), throw, "Unable to open file " << logfile.fileName());

	QTextStream ologfile(&logfile);

	ologfile << info_str << " " << message;
	#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
	ologfile << Qt::endl;
	#else
	ologfile << endl;
	#endif

	logfile.close();

	logfile_mutex.unlock();

}

void logging::set_default_category() {
	QLoggingCategory * defaultMsgCategory = QLoggingCategory::defaultCategory();

	// Fatal cannot be disabled therefore not trying to enable it here
	SetMsgLevel(QtDebugMsg, defaultMsgCategory)
	SetMsgLevel(QtInfoMsg, defaultMsgCategory)
	SetMsgLevel(QtWarningMsg, defaultMsgCategory)
	SetMsgLevel(QtCriticalMsg, defaultMsgCategory)

}
