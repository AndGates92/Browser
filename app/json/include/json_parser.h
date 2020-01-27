#ifndef JSON_PARSER_H
#define JSON_PARSER_H
/**
 * @copyright
 * @file json_parser.h
 * @author Andrea Gianarda
 * @date 27th January 2020
 * @brief JSON Parser header file
*/

#include "json_wrapper.h"

/** @defgroup JsonParserGroup JSON Parser Doxygen Group
 *  JSON Parser control functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(jsonParserOverall)
Q_DECLARE_LOGGING_CATEGORY(jsonParserFile)

namespace json_parser {

	/**
	 * @brief JsonParser class
	 *
	 */
	class JsonParser: public json_wrapper::JsonWrapper {

		public:

			/**
			 * @brief Function: explicit JsonParser(QString fileName, QIODevice::OpenModeFlag openFlags)
			 *
			 * \param fileName: filename of the JSON file
			 * \param openFlags: flags used to open the file (It must be QIODevice::ReadOnly, QIODevice::WriteOnly QIODevice::ReadWrite and optionally additional flags)
			 *
			 * JSON parser constructor
			 */
			explicit JsonParser(QString fileName, QIODevice::OpenModeFlag openFlags);

			/**
			 * @brief Function: ~JsonParser()
			 *
			 * JSON parser destructor
			 */
			~JsonParser();

		protected:

		private:

	};

}
/** @} */ // End of JsonParserGroup group

#endif // JSON_PARSER_H
