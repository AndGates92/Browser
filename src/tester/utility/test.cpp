/**
 * @copyright
 * @file test.cpp
 * @author Andrea Gianarda
 * @date 12th January 2021
 * @brief Test utilities functions
 */

#include "app/shared/exception.h"
#include "tester/utility/test.h"

void tester::utility::checkText(const std::string & text, const tester::shared::text_type_e type) {
	for (const auto & character : text) {
		switch (type) {
			case tester::shared::text_type_e::ALPHANUMERICAL:
				EXCEPTION_ACTION_COND((std::isalnum(character) == true), throw, "Text " + text + " contains a non alphanumerical character " + character);
				break;
			case tester::shared::text_type_e::COMPLEX:
				EXCEPTION_ACTION_COND(((std::isalnum(character) == true) || (std::isspace(character) == true) || (std::ispunct(character) == true)), throw, "Text " + text + " with contains a non alphanumerical character " + character);
				break;
			case tester::shared::text_type_e::URL:
				EXCEPTION_ACTION_COND(((std::isalnum(character) == true) || ((std::ispunct(character) == true) && ((character == '%') || (character == '/') || (character == '.')))), throw, "Text " + text + " with contains a non alphanumerical character " + character);
				break;
			default:
				EXCEPTION_ACTION(throw, std::string("No checks performed on character ") + character + " of the text " + text + " for text type " + type);
				break;
		}
	}
}
