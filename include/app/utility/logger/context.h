#ifndef LOGGER_CONTEXT_H
#define LOGGER_CONTEXT_H
/**
 * @copyright
 * @file context.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Logger context header file
*/

#include <string>
#include <memory>

#include <QtCore/QLoggingCategory>

#include "app/utility/logger/enums.h"

/** @defgroup LoggerGroup Logger Doxygen Group
 *  Logger functions and classes
 *  @{
 */

namespace app {

	namespace logger {

		class Context {

			public:
				/**
				 * @brief Function: static app::logger::Context getDefaultContext(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity)
				 *
				 * \return the default context logger
				 *
				 * This function returns the default logger context
				 */
				static app::logger::Context getDefaultContext();

				/**
				 * @brief Function: void setLogFilename(const std::string & value)
				 *
				 * \param value: the name of the file to log messages into
				 *
				 * This function sets the name of the file to log messages into
				 */
				void setLogFilename(const std::string & value);

				/**
				 * @brief Function: const std::string & getLogFilename() const
				 *
				 * \return the name of the file to log messages into
				 *
				 * This function returns the name of the file to log messages into
				 */
				const std::string & getLogFilename() const;

				/**
				 * @brief Function: void setName(const std::string & value)
				 *
				 * \param value: the name of the category
				 *
				 * This function sets the name of the category
				 */
				void setName(const std::string & value);

				/**
				 * @brief Function: const std::string & getName() const
				 *
				 * \return the name of the category
				 *
				 * This function returns the name of the category
				 */
				const std::string & getName() const;

				/**
				 * @brief Function: const std::string & getFile() const
				 *
				 * \return file of the context
				 *
				 * This function returns the file of the context
				 */
				const std::string & getFile() const;

				/**
				 * @brief Function: const int & getLine() const
				 *
				 * \return line of the context
				 *
				 * This function returns the line of the context
				 */
				const int & getLine() const;

				/**
				 * @brief Function: const std::string & getFunction() const
				 *
				 * \return function of the context
				 *
				 * This function returns the function of the context
				 */
				const std::string & getFunction() const;

				/**
				 * @brief Function: void setType(const app::logger::msg_type_e & value)
				 *
				 * \param value: the minimum type of messages printed by this context
				 *
				 * This function sets the minimum type of messages printed by this context
				 */
				void setType(const app::logger::msg_type_e & value);

				/**
				 * @brief Function: const app::logger::msg_type_e & getType() const
				 *
				 * \return the minimum type of messages printed by this context
				 *
				 * This function returns the minimum type of messages printed by this context
				 */
				const app::logger::msg_type_e & getType() const;

				/**
				 * @brief Function: void setInfoVerbosity(const app::logger::info_level_e & value)
				 *
				 * \param value: the minimum verbosity level of information messages printed by this context
				 *
				 * This function sets the minimum verbosity level of information messages printed by this context
				 */
				void setInfoVerbosity(const app::logger::info_level_e & value);

				/**
				 * @brief Function: const app::logger::info_level_e & getInfoVerbosity() const
				 *
				 * \return the minimum verbosity level of information messages printed by this context
				 *
				 * This function returns the minimum verbosity level of information messages printed by this context
				 */
				const app::logger::info_level_e & getInfoVerbosity() const;

				/**
				 * @brief Function: explicit Context(const std::string contextName, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity, const std::string ologfilename)
				 *
				 * \param contextName: name of the context
				 * \param contextType: minimum message type accepted
				 * \param contextInfoVerbosity: minimum verbosity level of information messages
				 * \param ologfilename: filename of the file where messages will be printed
				 *
				 * Logger context constructor
				 */
				explicit Context(const std::string contextName, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity, const std::string ologfilename);

				/**
				 * @brief Function: explicit Context(const std::string contextName, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity)
				 *
				 * \param contextName: name of the context
				 * \param contextType: minimum message type accepted
				 * \param contextInfoVerbosity: minimum verbosity level of information messages
				 *
				 * Logger context constructor
				 */
				explicit Context(const std::string contextName, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity);

				/**
				 * @brief Function: explicit Context(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity, const std::string ologfilename)
				 *
				 * \param contextName: name of the context
				 * \param contextFile: file of the context
				 * \param contextLine: line of the context
				 * \param contextFunction: function of the context
				 * \param contextType: minimum message type accepted
				 * \param contextInfoVerbosity: minimum verbosity level of information messages
				 * \param ologfilename: filename of the file where messages will be printed
				 *
				 * Logger context constructor
				 */
				explicit Context(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity, const std::string ologfilename);


				/**
				 * @brief Function: explicit Context(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity)
				 *
				 * \param contextName: name of the context
				 * \param contextFile: file of the context
				 * \param contextLine: line of the context
				 * \param contextFunction: function of the context
				 * \param contextType: minimum message type accepted
				 * \param contextInfoVerbosity: minimum verbosity level of information messages
				 *
				 * Logger context constructor
				 */
				explicit Context(const std::string contextName, const std::string contextFile, const int contextLine, const std::string contextFunction, const app::logger::msg_type_e contextType, const app::logger::info_level_e contextInfoVerbosity);

				/**
				 * @brief Function: virtual ~Context()
				 *
				 * Logger context destructor
				 */
				virtual ~Context();

			protected:

			private:
				/**
				 * @brief name of the context
				 *
				 */
				std::string name;

				/**
				 * @brief file of the context
				 *
				 */
				std::string file;

				/**
				 * @brief line of the context
				 *
				 */
				int line;

				/**
				 * @brief function of the context
				 *
				 */
				std::string function;

				/**
				 * @brief filename to log into
				 *
				 */
				std::string logFilename;

				/**
				 * @brief minimum message type printed by the context
				 *
				 */
				app::logger::msg_type_e type;

				/**
				 * @brief minimum verbosity level of information messages
				 *
				 */
				app::logger::info_level_e infoVerbosity;

		};

	}

}
/** @} */ // End of LoggerGroup group

#endif // LOGGER_CONTEXT_H
