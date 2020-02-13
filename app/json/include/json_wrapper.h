#ifndef JSON_WRAPPER_H
#define JSON_WRAPPER_H
/**
 * @copyright
 * @file json_wrapper.h
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Wrapper header file
*/

#include <qt5/QtCore/QtDebug>
#include <qt5/QtCore/QLoggingCategory>
#include <qt5/QtCore/QJsonValue>

#include <qt5/QtCore/QString>
#include <qt5/QtCore/QFile>

/** @defgroup JsonWrapperGroup JSON Wrapper Doxygen Group
 *  JSON Wrapper control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(jsonWrapperOverall)
Q_DECLARE_LOGGING_CATEGORY(jsonWrapperFile)
Q_DECLARE_LOGGING_CATEGORY(jsonWrapperFileContent)

namespace json_wrapper {

	/**
	 * @brief JSON content type
	 *
	 */
	typedef enum class json_content_type_list {
		OBJECT,   /**< JSON data stores data into an object */
		ARRAY     /**< JSON file stores data into an array */
	} json_content_type_e;

	/**
	 * @brief Function: QDebug & operator<< (QDebug & os, const json_wrapper::json_content_type_e & type)
	 *
	 * \param os: output stream
	 * \param type: type of the JSON content
	 *
	 * Overload << operator to print text type
	 */
	QDebug & operator<< (QDebug & os, const json_wrapper::json_content_type_e & type);

	/**
	 * @brief Function: QString & operator<< (QString & os, const json_wrapper::json_content_type_e & type)
	 *
	 * \param os: output stream
	 * \param type: type of the JSON content
	 *
	 * Overload << operator to print text type
	 */
	QString & operator<< (QString & os, const json_wrapper::json_content_type_e & type);

	/**
	 * @brief JSON content structure
	 *
	 */
	typedef struct json_content_list {
		json_wrapper::json_content_type_e type;       /**< JSON content type */
		QVariant body;                                /**< JSON file body */
	} json_content_s;

	/**
	 * @brief JsonWrapper class
	 *
	 */
	class JsonWrapper {

		public:

			/**
			 * @brief Function: explicit JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags)
			 *
			 * \param jsonFileName: filename of the JSON file
			 * \param jsonOpenFlags: flags used to open the file (It must be QIODevice::ReadOnly, QIODevice::WriteOnly QIODevice::ReadWrite and optionally additional flags)
			 *
			 * JSON wrapper constructor
			 */
			explicit JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags);

			/**
			 * @brief Function: ~JsonWrapper()
			 *
			 * JSON wrapper destructor
			 */
			virtual ~JsonWrapper();

		protected:
			/**
			 * @brief JSON file content
			 *
			 */
			QJsonValue jsonContent;

			/**
			 * @brief JSON content type
			 *
			 */
			json_wrapper::json_content_type_e type;
			/**
			 * @brief Function: void readJson()
			 *
			 * function that reads a JSON file and stores into a QString
			 */
			void readJson();

			/**
			 * @brief Function: bool addJsonValue(QJsonValue jsonVal, QString key = QString::null)
			 *
			 * \param key: key of the item to add (available only when the file is a QJsonObject) 
			 * \param jsonVal: value to add to JSON file
			 *
			 * \return whether the operation was successful (true) or not (false)
			 *
			 * function that adds a JSON value. It doesn't write to the file
			 */
			bool addJsonValue(QJsonValue jsonVal, QString key = QString::null);

			/**
			 * @brief Function: void writeJson()
			 *
			 * function that write a JSON file
			 */
			void writeJson();

		private:
			/**
			 * @brief open flags
			 *
			 */
			QIODevice::OpenModeFlag openFlags;

			/**
			 * @brief JSON file pointer
			 *
			 */
			QFile * jsonFile;

			/**
			 * @brief Function: void walkJsonGroupValue(const QJsonValue & content)
			 *
			 * \param content: input content to walk through
			 *
			 * function that walks through a JSON file
			 */
			void walkJson(const QJsonValue & content);
	};

}
/** @} */ // End of JsonWrapperGroup group

#endif // JSON_WRAPPER_H
