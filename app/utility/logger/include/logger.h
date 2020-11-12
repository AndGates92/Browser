#ifndef LOGGER_H
#define LOGGER_H
/**
 * @copyright
 * @file logger.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Logger header file
*/

#include <string>
#include <memory>
#include <mutex>
#include <fstream>

#include "logging.h"
#include "config.h"
#include "context.h"

/** @defgroup LoggerGroup Logger Doxygen Group
 *  Logger functions and classes
 *  @{
 */
namespace logger {

	class Logger {

		public:

			/**
			 * @brief prototype of a function returning a constant reference to a context
			 *
			 */
			typedef std::function<const logger::Context &(void)> context_function_t;

			/**
			 * @brief Function: explicit Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const logger::Context loggerContext, const logger::info_level_e loggerVerbosity, const std::string ologfilename = logger::Config::getInstance()->getDefaultOutputFile())
			 *
			 * \param loggerType: message type associated with the logger
			 * \param contextFile: filename of the context
			 * \param line: line of the context
			 * \param function: function of the context
			 * \param loggerContext: context to get data from
			 * \param loggerVerbosity: verbosity level of information messages
			 * \param ologfilename: filename of the file where messages will be printed
			 *
			 * Logger constructor with context
			 */
			explicit Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const logger::Context loggerContext, const logger::info_level_e loggerVerbosity, const std::string ologfilename = logger::Config::getInstance()->getDefaultOutputFile());

			/**
			 * @brief Function: explicit Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, context_function_t loggerContextConstRef, const logger::info_level_e loggerVerbosity, const std::string ologfilename = logger::Config::getInstance()->getDefaultOutputFile())
			 *
			 * \param loggerType: message type associated with the logger
			 * \param contextFile: filename of the context
			 * \param line: line of the context
			 * \param function: function of the context
			 * \param loggerContextConstRef: pointer to a function that returns a constant reference to the context
			 * \param loggerVerbosity: verbosity level of information messages
			 * \param ologfilename: filename of the file where messages will be printed
			 *
			 * Logger constructor with context
			 */
			explicit Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, context_function_t loggerContextConstRef, const logger::info_level_e loggerVerbosity, const std::string ologfilename = logger::Config::getInstance()->getDefaultOutputFile());

			/**
			 * @brief Function: explicit Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const logger::info_level_e loggerVerbosity = logger::Config::getInstance()->getDefaultVerbosity(), const std::string ologfilename = logger::Config::getInstance()->getDefaultOutputFile())
			 *
			 * \param loggerType: message type associated with the logger
			 * \param contextFile: filename of the context
			 * \param line: line of the context
			 * \param function: function of the context
			 * \param loggerVerbosity: verbosity level of information messages
			 * \param ologfilename: filename of the file where messages will be printed
			 *
			 * Logger constructor
			 */
			explicit Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const logger::info_level_e loggerVerbosity = logger::Config::getInstance()->getDefaultVerbosity(), const std::string ologfilename = logger::Config::getInstance()->getDefaultOutputFile());

			/**
			 * @brief Function: virtual ~Logger()
			 *
			 * Logger destructor
			 */
			virtual ~Logger();

			/**
			 * @brief Function: void initAndLog(const logger::Context & messageContext, argTypes... args)
			 *
			 * \param messageContext: message context to copy data from
			 * \param args: arguments used to print the message
			 *
			 * This function prints context information and message to the output file
			 */
			template <typename... argTypes>
			void initAndLog(const logger::Context & messageContext, argTypes... args);

			/**
			 * @brief Function: void initAndLog(context_function_t loggerContextConstRef, argTypes... args)
			 *
			 * \param loggerContextConstRef: pointer to a function that returns a constant reference to the context
			 * \param args: arguments used to print the message
			 *
			 * This function prints context information and message to the output file
			 */
			template <typename... argTypes>
			void initAndLog(context_function_t loggerContextConstRef, argTypes... args);

			/**
			 * @brief Function: void initializeLogging(const logger::Context & otherContext = logger::Context::getDefaultContext())
			 *
			 * \param otherContext: context to copy
			 *
			 * This function initialize the log
			 */
			void initializeLogging(const logger::Context & otherContext = logger::Context::getDefaultContext());

			/**
			 * @brief Function: void initializeLogging(context_function_t otherLoggerContextConstRef)
			 *
			 * \param otherLoggerContextConstRef: pointer to a function that returns a constant reference to the context
			 *
			 * This function initialize the log
			 */
			void initializeLogging(context_function_t otherLoggerContextConstRef);

			/**
			 * @brief Function: bool isLogAllowed() const
			 *
			 * \return a boolean to state whether print is allowed
			 *
			 * This function states if a logger can print a log or not
			 */
			bool isLogAllowed() const;

			/**
			 * @brief Function: const logger::state_e & getState() const
			 *
			 * \return the state of the logger
			 *
			 * This function returns the state of the logger
			 */
			const logger::state_e & getState() const;

			/**
			 * @brief Function: void append(firstType headArg, otherTypes ... otherArgs)
			 *
			 * \param headArg: argument to concatenate to the output stream
			 * \param otherArgs: following arguments to concatenate to the output stream
			 *
			 * This function appends text to the output stream from a template parameter pack
			 * It is required that the operator<< of std::ostream is overloaded with all types passed to the template parameter pack
			 */
			template <typename firstType, typename... otherTypes>
			void append(firstType headArg, otherTypes ... otherArgs);

			/**
			 * @brief Function: void append(lastType arg)
			 *
			 * \param arg: argument to concatenate to the output stream
			 *
			 * This function appends text to the output stream from a template parameter pack
			 * It is required that the operator<< of std::ostream is overloaded with all types passed to the template parameter pack
			 */
			template <typename lastType>
			void append(lastType arg);

			/**
			 * @brief Function: logger::Logger & operator<< (logger::Logger & log, const type & arg)
			 *
			 * \param log: logger to update
			 * \param arg: argument to append to the log message
			 *
			 * This function appends the argument to the log message
			 */
			template <typename type>
			friend logger::Logger & operator<< (logger::Logger & log, const type & arg);

			/**
			 * @brief Function: logger::Logger & operator+ (logger::Logger & log, const type & arg)
			 *
			 * \param log: logger to update
			 * \param arg: argument to append to the log message
			 *
			 * This function appends the argument to the log message
			 */
			template <typename type>
			friend logger::Logger & operator+ (logger::Logger & log, const type & arg);

		protected:

		private:

			constexpr static std::ios_base::openmode openMode = (std::ios::ate | std::ios::app | std::ios::out);

			/**
			 * @brief logger context
			 *
			 */
			logger::Context context;

			/**
			 * @brief output file name
			 *
			 */
			std::string ofilename;

			/**
			 * @brief Output stream ofile
			 *
			 */
			std::ofstream ofile;

			/**
			 * @brief verbosity of info messages
			 *
			 */
			logger::info_level_e verbosity;

			/**
			 * @brief type of messages
			 *
			 */
			logger::msg_type_e type;

			/**
			 * @brief mutex to handle concurrent access to logfile
			 *
			 */
			std::mutex logMutex;

			/**
			 * @brief logger state
			 *
			 */
			logger::state_e state;

			/**
			 * @brief Function: bool isValidNextState(const logger::state_e & nextState) const
			 *
			 * \param nextState: state to transition to
			 *
			 * \return a boolean to state whether the transition from the current state to the one provided as argument is valid
			 *
			 * This function verify if the transition from the current state to the one provided as argument is valid
			 */
			bool isValidNextState(const logger::state_e & nextState) const;

			/**
			 * @brief Function: bool setState(const logger::state_e nextState)
			 *
			 * \param nextState: state to transition to
			 *
			 * \return a boolean to state whether the transition was successful or not
			 *
			 * This function transitions the logger to the current provided as argument if it is allowed to do so
			 */
			bool setState(const logger::state_e nextState);

			/**
			 * @brief Function: void copyContextData(const logger::Context & otherContext)
			 *
			 * \param otherContext: context to copy
			 *
			 * This function copies a context into the one of this logger
			 */
			void copyContextData(const logger::Context & otherContext);

			/**
			 * @brief Function: void createHeader()
			 *
			 * This function creates the header of the print
			 */
			void createHeader();

			/**
			 * @brief Function: void endLogging()
			 *
			 * This function ends logging
			 */
			void endLogging();

			/**
			 * @brief Function: void openOFile()
			 *
			 * This function opens the output file
			 */
			void openOFile();

			/**
			 * @brief Function: void closeOFile()
			 *
			 * This function closes the output file
			 */
			void closeOFile();
	};

}

template <typename... argTypes>
void logger::Logger::initAndLog(const logger::Context & messageContext, argTypes... args) {
	this->initializeLogging(messageContext);

	std::string message = std::string();
	logging::makeMsg(message, args...);

	*this << message;
}

template <typename... argTypes>
void logger::Logger::initAndLog(logger::Logger::context_function_t loggerContextConstRef, argTypes... args) {
	this->initAndLog(loggerContextConstRef(), args...);
}

template <typename lastType>
void logger::Logger::append(lastType arg) {
	EXCEPTION_ACTION_COND((this->state != logger::state_e::LOGGING_MESSAGE), throw, "Function " << __func__ << " can only be executed if the logger is in state logger::state_e::LOGGING_MESSAGE. Current state is " << this->state);
	*this << arg;
}

template <typename firstType, typename... otherTypes>
void logger::Logger::append(firstType headArg, otherTypes ... otherArgs) {
	EXCEPTION_ACTION_COND((this->state != logger::state_e::LOGGING_MESSAGE), throw, "Function " << __func__ << " can only be executed if the logger is in state logger::state_e::LOGGING_MESSAGE. Current state is " << this->state);
	*this << headArg;
	this->append(otherArgs...);
}

namespace logger {
	template <typename type>
	logger::Logger & operator<< (logger::Logger & log, const type & arg) {
		if (log.isLogAllowed() == true) {
			log.logMutex.lock();
			log.openOFile();
			log.ofile << arg;
			log.logMutex.unlock();
		}
		return log;
	}

	template <typename type>
	logger::Logger & operator+ (logger::Logger & log, const type & arg) {
		if (log.isLogAllowed() == true) {
			log.logMutex.lock();
			log.openOFile();
			log.ofile << arg;
			log.logMutex.unlock();
		}
		return log;
	}
}

/** @} */ // End of LoggerGroup group

#endif // LOGGER_H
