#ifndef JSON_WRAPPER_H
#define JSON_WRAPPER_H
/**
 * @copyright
 * @file json_wrapper.h
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Wrapper header file
*/

// Qt libraries
#include <QtCore/QJsonValue>

#include <QtCore/QString>
#include <QtCore/QFile>

#include "common/include/type_print_macros.h"

/** @defgroup JsonWrapperGroup JSON Wrapper Doxygen Group
 *  JSON Wrapper control functions and classes
 *  @{
 */

namespace json_wrapper {

	Q_NAMESPACE

	/**
	 * @brief JSON content type
	 *
	 */
	typedef enum class json_content_type_list {
		OBJECT,    /**< JSON data stores data into an object */
		ARRAY,     /**< JSON file stores data into an array */
		UNKNOWN    /**< JSON file stores data into an unknown data structure */
	} json_content_type_e;

	/**
	 * @brief Overload operators to ease print of JSON content type
	 *
	 */
	OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(json_content_type_list, json_wrapper::json_content_type_e)

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

			// Move and copy constructor
			/**
			 * @brief Function: JsonWrapper(const json_wrapper::JsonWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON wrapper copy constructor
			 */
			explicit JsonWrapper(const json_wrapper::JsonWrapper & rhs);

			/**
			 * @brief Function: JsonWrapper::JsonWrapper(json_wrapper::JsonWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON wrapper move constructor
			 */
			explicit JsonWrapper(json_wrapper::JsonWrapper && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: JsonWrapper & operator=(const json_wrapper::JsonWrapper & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * JSON wrapper copy assignment operator
			 */
			JsonWrapper & operator=(const json_wrapper::JsonWrapper & rhs);

			/**
			 * @brief Function: JsonWrapper & operator=(json_wrapper::JsonWrapper && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * JSON wrapper move assignment operator
			 */
			JsonWrapper & operator=(json_wrapper::JsonWrapper && rhs);

			/**
			 * @brief Function: virtual ~JsonWrapper()
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
			 * @brief Function: void walkJsonGroupValue(const QJsonValue & content) const
			 *
			 * \param content: input content to walk through
			 *
			 * function that walks through a JSON file
			 */
			void walkJson(const QJsonValue & content) const;

			/**
			 * @brief Function: void addJsonValue(QJsonValue & content, QJsonValue val, const QString & key = QString())
			 *
			 * \param content: input content to add to
			 * \param key: key of the item to add (available only when the file is a QJsonObject)
			 * \param val: value to add to JSON value
			 *
			 * function that adds a JSON value. It doesn't write to the file
			 */
			void addJsonValue(QJsonValue & content, const QJsonValue & val, const QString & key = QString());

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
			 * @brief Function: void appendJsonObject(QJsonObject & jsonObj, const QJsonObject & newObj)
			 *
			 * \param jsonObj: JSON object to be appended
			 * \param newObj: JSON object to append
			 *
			 * function that adds a JSON object
			 */
			void appendJsonObject(QJsonObject & jsonObj, const QJsonObject & newObj);

			/**
			 * @brief Function: void insertToJsonObject(QJsonObject & jsonObj, const QString & key, QJsonValue val)
			 *
			 * \param jsonObj: jsonObj to be updated
			 * \param key: key of the item to add
			 * \param val: value to add to JSON object
			 *
			 * function that inserts a JSON value to a JSON object and check the operation is successful
			 */
			void insertToJsonObject(QJsonObject & jsonObj, const QString & key, const QJsonValue & val);

	};

}
/** @} */ // End of JsonWrapperGroup group

#endif // JSON_WRAPPER_H
