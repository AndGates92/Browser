/**
 * @copyright
 * @file context.cpp
 * @author Andrea Gianarda
 * @date 30th October 2020
 * @brief Logger context functions
 */

#include <string>

#include "app/settings/global.h"
#include "app/shared/setters_getters.h"
#include "app/utility/cpp/cpp_operator.h"
#include "app/utility/logger/macros.h"
#include "app/utility/logger/config.h"
#include "app/utility/logger/logger.h"

// Categories
LOGGING_CONTEXT(loggerOverall, logger.overall, TYPE_LEVEL, INFO_VERBOSITY)

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, app::logger::Logger::context_function_t loggerContextConstRef, const app::logger::info_level_e loggerInfoVerbosity) : app::logger::Logger(loggerType, contextFile, line, function, loggerContextConstRef, loggerInfoVerbosity, app::settings::Global::getLogFilePath()) {

}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, app::logger::Logger::context_function_t loggerContextConstRef, const app::logger::info_level_e loggerInfoVerbosity, const std::string ologfilename) : app::logger::Logger(loggerType, contextFile, line, function, loggerContextConstRef(), loggerInfoVerbosity, ologfilename) {

}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const app::logger::Context loggerContext, const app::logger::info_level_e loggerInfoVerbosity) : app::logger::Logger(loggerType, contextFile, line, function, loggerContext, loggerInfoVerbosity, app::settings::Global::getLogFilePath()) {

}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const app::logger::Context loggerContext, const app::logger::info_level_e loggerInfoVerbosity, const std::string ologfilename) : app::logger::Logger(loggerType, contextFile, line, function, loggerInfoVerbosity, ologfilename) {
	this->initializeLogging(loggerContext);
}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const app::logger::info_level_e loggerInfoVerbosity) : app::logger::Logger(loggerType, contextFile, line, function, loggerInfoVerbosity, app::settings::Global::getLogFilePath()) {

}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const app::logger::info_level_e loggerInfoVerbosity, const std::string ologfilename) : context(app::logger::Config::getInstance()->getDefaultContextName(), contextFile, line, function, app::logger::Config::getInstance()->getDefaultType(), app::logger::Config::getInstance()->getDefaultVerbosity()), ofile(ologfilename, app::logger::Logger::openMode), infoVerbosity(loggerInfoVerbosity), type(loggerType), state(app::logger::state_e::CONSTRUCTED) {

}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function) : app::logger::Logger(loggerType, contextFile, line, function, app::settings::Global::getLogFilePath()) {

}

app::logger::Logger::Logger(const app::logger::msg_type_e loggerType, const std::string contextFile, const int line, const std::string function, const std::string ologfilename) : app::logger::Logger(loggerType, contextFile, line, function, app::logger::Config::getInstance()->getDefaultVerbosity(), ologfilename) {

}

app::logger::Logger::~Logger() {
	this->endLogging();
	this->setState(app::logger::state_e::TERMINATING);
	// Close ofile when destroying the logger
	this->closeOFile();

	if (this->type == app::logger::msg_type_e::FATAL) {
		std::terminate();
	}
}

void app::logger::Logger::copyContextData(const app::logger::Context & otherContext) {
	EXCEPTION_ACTION_COND((this->state != app::logger::state_e::CONSTRUCTED), throw, "Function " << __func__ << " can only be executed if the logger is in state app::logger::state_e::CONSTRUCTED. Current state is " << this->state);
	this->context.setName(otherContext.getName());
	this->context.setType(otherContext.getType());
	this->context.setInfoVerbosity(otherContext.getInfoVerbosity());
	const std::string & currentCtxtLogFilename = this->context.getLogFilename();
	// Copy log filename from context only if no filename was passed to the logger at the time of construction
	if ((currentCtxtLogFilename.empty() == true) || (currentCtxtLogFilename.compare(app::settings::Global::getLogFilePath()) == 0)) {
		this->context.setLogFilename(otherContext.getLogFilename());
	}
	EXCEPTION_ACTION_COND((this->getLogFilename().empty() == true), throw, "Log filename was set to an empty string");
	this->setState(app::logger::state_e::INITIALIZED);
}

void app::logger::Logger::initializeLogging(const app::logger::Context & messageContext) {
	this->copyContextData(messageContext);
	this->createHeader();
}

void app::logger::Logger::initializeLogging(app::logger::Logger::context_function_t otherLoggerContextConstRef) {
	this->initializeLogging(otherLoggerContextConstRef());
}

void app::logger::Logger::createHeader() {
	EXCEPTION_ACTION_COND((this->state != app::logger::state_e::INITIALIZED), throw, "Function " << __func__ << " can only be executed if the logger is in state app::logger::state_e::INITIALIZED. Current state is " << this->state);
	std::string header = std::string();
	header = header + "[" + app::shared::getDateTime().toStdString() + "] ";
	header = header + app::shared::qEnumToQString(this->type, true).toStdString();

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

	this->setState(app::logger::state_e::WRITING_HEADER);
	*this << header << " ";
	this->setState(app::logger::state_e::LOGGING_MESSAGE);
}

void app::logger::Logger::endLogging() {
	if ((this->isLogAllowed() == true) && (this->ofile.is_open() == true)) {
		this->logMutex.lock();
		// Append endl at the end of the message
		this->ofile << std::endl;
		this->logMutex.unlock();
	}
	this->setState(app::logger::state_e::LOGGING_ENDED);
}

void app::logger::Logger::openOFile() {
	if (this->ofile.is_open() == false) {
		EXCEPTION_ACTION_COND((this->getLogFilename().empty() == true), throw, "Unable to open file with empty name");
		if (this->getLogFilename().empty() == true) {
			this->ofile.open(app::settings::Global::getLogFilePath(), app::logger::Logger::openMode);
			this->context.setLogFilename(app::settings::Global::getLogFilePath());
		} else {
			this->ofile.open(this->getLogFilename(), app::logger::Logger::openMode);
		}
		if ((this->ofile.rdstate() & std::ostream::failbit) != 0) {
			EXCEPTION_ACTION(throw, "Unable to open file " << this->getLogFilename());
		}
	}
}

void app::logger::Logger::closeOFile() {
	if (this->ofile.is_open() == true) {
		this->logMutex.lock();
		this->ofile.close();
		this->logMutex.unlock();
	}
}

bool app::logger::Logger::isLogAllowed() const {
	bool allowed = ((this->state == app::logger::state_e::WRITING_HEADER) || (this->state == app::logger::state_e::LOGGING_MESSAGE));
	if (this->type <= this->context.getType()) {
		// For info messages, verbosity also must be checked
		if (this->type == app::logger::msg_type_e::INFO) {
			// if verbosity of the context is higher than the requested verbosity
			allowed &= (this->infoVerbosity <= this->context.getInfoVerbosity());
		}
	}
	return allowed;
}

bool app::logger::Logger::isValidNextState(const app::logger::state_e & nextState) const {
	bool valid = false;

	switch (nextState) {
		case app::logger::state_e::INITIALIZED:
			valid = (this->state == app::logger::state_e::CONSTRUCTED);
			break;
		case app::logger::state_e::WRITING_HEADER:
			valid = (this->state == app::logger::state_e::INITIALIZED);
			break;
		case app::logger::state_e::LOGGING_MESSAGE:
			valid = (this->state == app::logger::state_e::WRITING_HEADER);
			break;
		case app::logger::state_e::LOGGING_ENDED:
			valid = (this->state == app::logger::state_e::LOGGING_MESSAGE);
			break;
		case app::logger::state_e::TERMINATING:
			valid = (this->state == app::logger::state_e::LOGGING_ENDED);
			break;
		default:
			EXCEPTION_ACTION(throw, "Unable to handle transition from state " << this->state << " to state " << nextState);
			break;
	}

	return valid;
}

CONST_GETTER(app::logger::Logger::getState, app::logger::state_e &, this->state)

bool app::logger::Logger::setState(const app::logger::state_e nextState) {
	const bool success = this->isValidNextState(nextState);
	if (success == true) {
		this->state = nextState;
	}
	return success;
}

CONST_GETTER(app::logger::Logger::getLogFilename, std::string &, this->context.getLogFilename())
