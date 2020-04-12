/**
 * @copyright
 * @file global_functions.cpp
 * @author Andrea Gianarda
 * @date 31st of Mqrch 2020
 * @brief Global function definition
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "global_functions.h"

Q_LOGGING_CATEGORY(readFileOverall, "readFile.overall", MSG_TYPE_LEVEL)

std::string global_functions::readFile(const std::string & filename) {

	QEXCEPTION_ACTION_COND((filename.empty() == true), throw, "Provided an empty filename therefore it is not possible to open it and read its content");
	std::ifstream ifile;

	// Sets exception mask - i.e. for which state flags an exception is thrown
	ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

	std::string content;

	try {

		ifile.open(filename, std::ifstream::in);
		ifile.seekg(0, std::ios_base::end);
		std::streampos fileLength = ifile.tellg();

		ifile.seekg(0, std::ios_base::beg);

		int charCount = 0;
		const char delimChar = '\n';

		while(!ifile.eof()) {
			std::string line;
			std::getline(ifile, line, delimChar);
			// Delimiter character is discarded by std::getline
			line.push_back(delimChar);
			content.append(line);
			charCount += line.length();
			const float percentageCount = (((float) charCount) * 100.0) / ((float) fileLength);
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, readFileOverall,  "Character counted " << charCount << " out of " << fileLength << " that is " << percentageCount << "%");
		}
	} catch (const std::ifstream::failure & e) {
		if (ifile.is_open()) {
			ifile.close();
		}
		if (ifile.eof()) {
			QINFO_PRINT(global_types::qinfo_level_e::ZERO, readFileOverall,  "Finished reading content from file " << filename.c_str());
		} else {
			// Convert std::error_code print to std::string so that it can be printed
			const std::error_code errorCode(e.code());
			std::ostringstream errorCodeOut(std::ostringstream::ate);
			// flush() method returns a non-const reference to std::ostream
			errorCodeOut.flush() << errorCode;
			const std::string errorCodeStr(errorCodeOut.str());
			QEXCEPTION_ACTION(throw, "Unable to open or read content from file " << filename.c_str() << ".\nMessage: " << e.what() << ".\nError code: " << errorCodeStr.c_str());
		}
	}

	return content;
}
