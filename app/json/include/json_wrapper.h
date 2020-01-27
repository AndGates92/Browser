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
	 * @brief JsonWrapper class
	 *
	 */
	class JsonWrapper {

		public:

			/**
			 * @brief Function: explicit JsonWrapper(QString fileName, QIODevice::OpenModeFlag openFlags)
			 *
			 * \param fileName: filename of the JSON file
			 * \param openFlags: flags used to open the file (It must be QIODevice::ReadOnly, QIODevice::WriteOnly QIODevice::ReadWrite and optionally additional flags)
			 *
			 * JSON wrapper constructor
			 */
			explicit JsonWrapper(QString fileName, QIODevice::OpenModeFlag openFlags);

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
			QString content;

			/**
			 * @brief Function: void readJson()
			 *
			 * function that reads a JSON file and stores into a QString
			 */
			void readJson();

			/**
			 * @brief Function: void writeJson()
			 *
			 * function that write a JSON file from a QString
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
			QFile * filePtr;

	};

}
/** @} */ // End of JsonWrapperGroup group

#endif // JSON_WRAPPER_H
