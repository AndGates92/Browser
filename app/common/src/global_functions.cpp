/**
 * @copyright
 * @file global_functions.cpp
 * @author Andrea Gianarda
 * @date 31st of March 2020
 * @brief Global function definition
 */

#include <fstream>
#include <sstream>
#include <string>

#include "common/include/global_functions.h"

LOGGING_CONTEXT(readFileOverall, readFile.overall, TYPE_LEVEL, INFO_VERBOSITY)

std::string global_functions::readFile(const std::string & filename) {

	EXCEPTION_ACTION_COND((filename.empty() == true), throw, "Provided an empty filename therefore it is not possible to open it and read its content");
	std::ifstream ifile;

	// Sets exception mask - i.e. for which state flags an exception is thrown
	ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

	std::string content;

	try {

		ifile.open(filename, std::ifstream::in);
		ifile.seekg(0, std::ios_base::end);
		std::streampos fileLength = ifile.tellg();

		ifile.seekg(0, std::ios_base::beg);

		long unsigned int charCount = 0;
		const char delimChar = '\n';

		while(!ifile.eof()) {
			std::string line;
			std::getline(ifile, line, delimChar);
			// Delimiter character is discarded by std::getline
			line.push_back(delimChar);
			content.append(line);
			charCount += line.length();
			const double percentageCount = (static_cast<double>(charCount) * 100.0) / static_cast<double>(fileLength);
			LOG_INFO(logger::info_level_e::ZERO, readFileOverall,  "Character counted " << charCount << " out of " << fileLength << " that is " << percentageCount << "%");
		}
	} catch (const std::ifstream::failure & e) {
		if (ifile.is_open()) {
			ifile.close();
		}
		if (ifile.eof()) {
			LOG_INFO(logger::info_level_e::ZERO, readFileOverall,  "Finished reading content from file " << filename.c_str());
		} else {
			// Convert std::error_code print to std::string so that it can be printed
			const std::error_code errorCode(e.code());
			std::ostringstream errorCodeOut(std::ostringstream::ate);
			// flush() method returns a non-const reference to std::ostream
			errorCodeOut.flush() << errorCode;
			const std::string errorCodeStr(errorCodeOut.str());
			EXCEPTION_ACTION(throw, "Unable to open or read content from file " << filename.c_str() << ".\nMessage: " << e.what() << ".\nError code: " << errorCodeStr.c_str());
		}
	}

	return content;
}

std::vector<std::string> global_functions::splitStringByDelimiter(const std::string & str, const std::string & delim) {

	std::size_t currentPosition = 0;
	std::size_t nextPosition = 0;
	std::vector<std::string> subStrs;

	do {
		nextPosition = str.find_first_of(delim, currentPosition);
		subStrs.push_back(str.substr(currentPosition, (nextPosition - currentPosition)));
		currentPosition = nextPosition + 1;
	} while (nextPosition != std::string::npos);

	return subStrs;
}
