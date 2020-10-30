/**
 * @copyright
 * @file context.cpp
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Logger context functions
 */

#include <string>

#include "cpp_operator.h"
#include "function_macros.h"
#include "macros.h"
#include "logger.h"

// Categories
LOGGING_CONTEXT(loggerOverall, logger.overall, TYPE_LEVEL, INFO_VERBOSITY)

logger::Logger::Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, logger::Logger::context_function_t loggerContextConstRef, const logger::info_level_e loggerVerbosity, const std::string ologfilename) : logger::Logger(loggerType, contextFile, line, function, loggerContextConstRef(), loggerVerbosity, ologfilename) {

}

logger::Logger::Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const logger::Context loggerContext, const logger::info_level_e loggerVerbosity, const std::string ologfilename) : logger::Logger(loggerType, contextFile, line, function, loggerVerbosity, ologfilename) {
	this->initializeLogging(loggerContext);
}

logger::Logger::Logger(const logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const logger::info_level_e loggerVerbosity, const std::string ologfilename) : context(logger::Config::getDefaultContextName(), contextFile, line, function, logger::Config::getDefaultType(), logger::Config::getDefaultVerbosity()), ofilename(ologfilename), ofile(ologfilename, logger::Logger::openMode), verbosity(loggerVerbosity), type(loggerType), state(logger::state_e::CONSTRUCTED) {

}

logger::Logger::~Logger() {
	this->endLogging();
	this->setState(logger::state_e::TERMINATING);
	// Close ofile when destroying the logger
	this->closeOFile();

	if (this->type == logger::msg_type_e::FATAL) {
		std::terminate();
	}
}

void logger::Logger::copyContextData(const logger::Context & otherContext) {
	EXCEPTION_ACTION_COND((this->state != logger::state_e::CONSTRUCTED), throw, "Function " << __func__ << " can only be executed if the logger is in state logger::state_e::CONSTRUCTED. Current state is " << this->state);
	this->context.setName(otherContext.getName());
	this->context.setType(otherContext.getType());
	this->context.setInfoVerbosity(otherContext.getInfoVerbosity());
	this->setState(logger::state_e::INITIALIZED);
}

void logger::Logger::initializeLogging(const logger::Context & messageContext) {
	this->copyContextData(messageContext);
	this->createHeader();
}

void logger::Logger::initializeLogging(logger::Logger::context_function_t otherLoggerContextConstRef) {
	this->initializeLogging(otherLoggerContextConstRef());
}

void logger::Logger::createHeader() {
	EXCEPTION_ACTION_COND((this->state != logger::state_e::INITIALIZED), throw, "Function " << __func__ << " can only be executed if the logger is in state logger::state_e::INITIALIZED. Current state is " << this->state);
	std::string header = std::string();
	header = header + "[" + logging_functions::getDateTime().toStdString() + "] ";
	header = header + global_qfunctions::qEnumToQString(this->type, true).toStdString();

	// CategoryFunction
	const std::string & contextName = this->context.getName();
	if (contextName.empty() == false) {
		header = header + " [" + contextName + "]";
	}

	// Filename
	const std::string & contextFile = this->context.getFile();
	if (contextFile.empty() == false) {
		header = header + " File " + contextFile;
	}

	// Function
	const std::string & contextFunction = this->context.getFunction();
	if (contextFunction.empty() == false) {
		header = header + " in function " + contextFunction;
	}

	this->setState(logger::state_e::WRITING_HEADER);
	*this << header << " ";
	this->setState(logger::state_e::LOGGING_MESSAGE);
}

void logger::Logger::endLogging() {
	if ((this->isLogAllowed() == true) && (this->ofile.is_open() == true)) {
		this->logMutex.lock();
		// Append endl at the end of the message
		this->ofile << std::endl;
		this->logMutex.unlock();
	}
	this->setState(logger::state_e::LOGGING_ENDED);
}

void logger::Logger::openOFile() {
	if (this->ofile.is_open() == false) {
		if (this->ofilename.empty() == true) {
			this->ofile.open(logger::Config::getDefaultOutputFile(), logger::Logger::openMode);
			this->ofilename = logger::Config::getDefaultOutputFile();
		} else {
			this->ofile.open(this->ofilename, logger::Logger::openMode);
		}
		if ((this->ofile.rdstate() & std::ostream::failbit) != 0) {
			EXCEPTION_ACTION(throw, "Unable to open file " << this->ofilename);
		}
	}
}

void logger::Logger::closeOFile() {
	if (this->ofile.is_open() == true) {
		this->logMutex.lock();
		this->ofile.close();
		this->logMutex.unlock();
	}
}

bool logger::Logger::isLogAllowed() const {
	bool allowed = ((this->state == logger::state_e::WRITING_HEADER) || (this->state == logger::state_e::LOGGING_MESSAGE));
	if (this->type <= this->context.getType()) {
		// For info messages, verbosity also must be checked
		if (this->type == logger::msg_type_e::INFO) {
			// if verbosity of the context is higher than the requested verbosity
			allowed &= (this->verbosity <= this->context.getInfoVerbosity());
		}
	}
	return allowed;
}

bool logger::Logger::isValidNextState(const logger::state_e & nextState) const {
	bool valid = false;

	switch (nextState) {
		case logger::state_e::INITIALIZED:
			valid = (this->state == logger::state_e::CONSTRUCTED);
			break;
		case logger::state_e::WRITING_HEADER:
			valid = (this->state == logger::state_e::INITIALIZED);
			break;
		case logger::state_e::LOGGING_MESSAGE:
			valid = (this->state == logger::state_e::WRITING_HEADER);
			break;
		case logger::state_e::LOGGING_ENDED:
			valid = (this->state == logger::state_e::LOGGING_MESSAGE);
			break;
		case logger::state_e::TERMINATING:
			valid = (this->state == logger::state_e::LOGGING_ENDED);
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to handle transition from state " << this->state << " to state " << nextState);
			break;
	}

	return valid;
}

CONST_GETTER(logger::Logger::getState, logger::state_e &, this->state)

bool logger::Logger::setState(const logger::state_e nextState) {
	const bool success = this->isValidNextState(nextState);
	if (success == true) {
		this->state = nextState;
	}
	return success;
}
