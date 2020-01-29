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
	 * @brief JSON content structure
	 *
	 */
	typedef struct json_content_list {
		json_wrapper::json_content_type_e contentType;   /**< JSON content type */
		QVariant content;                                /**< JSON file content */
	} json_content_e;

	/**
	 * @brief JsonWrapper class
	 *
	 */
	class JsonWrapper {

		public:

			/**
			 * @brief Function: explicit JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags, json_wrapper::json_content_type_e jsonContentType)
			 *
			 * \param jsonFileName: filename of the JSON file
			 * \param jsonOpenFlags: flags used to open the file (It must be QIODevice::ReadOnly, QIODevice::WriteOnly QIODevice::ReadWrite and optionally additional flags)
			 * \param jsonContentType: content type of the JSON file (array or object)
			 *
			 * JSON wrapper constructor
			 */
			explicit JsonWrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags, json_wrapper::json_content_type_e jsonContentType = json_wrapper::json_content_type_e::OBJECT);

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
			json_wrapper::json_content_e jsonContent;

			/**
			 * @brief Function: void readJson()
			 *
			 * function that reads a JSON file and stores into a QString
			 */
			void readJson();

			/**
			 * @brief Function: bool addJsonValue(QString key, QJsonValue jsonVal)
			 *
			 * \param key: key of the item to add (available only when the file is a QJsonObject) 
			 * \param jsonVal: value to add to JSON file
			 *
			 * \return whether the operation was successful (true) or not (false)
			 *
			 * function that adds a JSON value. It doesn't write to the file
			 */
			bool addJsonValue(QString key, QJsonValue jsonVal);

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

	};

}
/** @} */ // End of JsonWrapperGroup group

#endif // JSON_WRAPPER_H
