#ifndef JSON_WRAPPER_H
#define JSON_WRAPPER_H
/**
 * @copyright
 * @file wrapper.h
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Wrapper header file
*/

// Qt libraries
#include <QtCore/QJsonValue>

#include <QtCore/QString>
#include <QtCore/QFile>

#include "app/shared/type_print_macros.h"

/** @defgroup JsonGroup Json Doxygen Group
 *  Json functions and classes
 *  @{
 */

namespace app {

	namespace utility {

		namespace json {

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
			OVERLOAD_OPERATORS_CUSTOM_TYPE_FUNCTION_PROTOTYPE(json_content_type_list, app::utility::json::json_content_type_e)

			/**
			 * @brief Wrapper class
			 *
			 */
			class Wrapper {

				public:

					/**
					 * @brief Function: explicit Wrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags)
					 *
					 * \param jsonFileName: filename of the JSON file
					 * \param jsonOpenFlags: flags used to open the file (It must be QIODevice::ReadOnly, QIODevice::WriteOnly QIODevice::ReadWrite and optionally additional flags)
					 *
					 * JSON wrapper constructor
					 */
					explicit Wrapper(QString jsonFileName, QIODevice::OpenModeFlag jsonOpenFlags);

					// Move and copy constructor
					/**
					 * @brief Function: Wrapper(const app::utility::json::Wrapper & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * JSON wrapper copy constructor
					 */
					explicit Wrapper(const app::utility::json::Wrapper & rhs);

					/**
					 * @brief Function: Wrapper::Wrapper(app::utility::json::Wrapper && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * JSON wrapper move constructor
					 */
					explicit Wrapper(app::utility::json::Wrapper && rhs);

					// Move and copy assignment operators
					/**
					 * @brief Function: Wrapper & operator=(const app::utility::json::Wrapper & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * JSON wrapper copy assignment operator
					 */
					Wrapper & operator=(const app::utility::json::Wrapper & rhs);

					/**
					 * @brief Function: Wrapper & operator=(app::utility::json::Wrapper && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * JSON wrapper move assignment operator
					 */
					Wrapper & operator=(app::utility::json::Wrapper && rhs);

					/**
					 * @brief Function: virtual ~Wrapper()
					 *
					 * JSON wrapper destructor
					 */
					virtual ~Wrapper();

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
					app::utility::json::json_content_type_e type;

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

	}

}
/** @} */ // End of JsonGroup group

#endif // JSON_WRAPPER_H
