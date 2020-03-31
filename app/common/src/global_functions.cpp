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

std::string global_functions::readFile(const std::string & filename) {

	std::ifstream ifile;

	// Sets exception mask - i.e. for which state flags an exception is thrown
	ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string content;

	try {

		ifile.open(filename, std::ifstream::in);

		const char delimChar = '\n';

		while(!ifile.eof()) {
			std::string line;
			std::getline(ifile, line, delimChar);
			// Delimiter character is discarded by std::getline
			line.push_back(delimChar);
			content.append(line);
		}
	} catch (const std::ifstream::failure & e) {
		// Convert std::error_code print to std::string so that it can be printed
		const std::error_code errorCode(e.code());
		std::ostringstream errorCodeOut(std::ostringstream::ate);
		// flush() method returns a non-const reference to std::ostream
		errorCodeOut.flush() << errorCode;
		const std::string errorCodeStr(errorCodeOut.str());
		QEXCEPTION_ACTION(throw, "Caught exception std::ifstream::failure while opening or reading content from file " << filename.c_str() << ".\n Message: " << e.what() << ".\n Error code: " << errorCodeStr.c_str());
	}

	return content;
}
