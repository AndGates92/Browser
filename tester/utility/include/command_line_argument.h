#ifndef COMMAND_LINE_ARGUMENT_H
#define COMMAND_LINE_ARGUMENT_H
/**
 * @copyright
 * @file command_line_argument.h
 * @author Andrea Gianarda
 * @date 17th September 2020
 * @brief Command line argument header file
 */

#include <memory>
#include <string>
#include <vector>

#include "json_data.h"

/** @defgroup CommandLineArgumentGroup Command Line Argument Group
 *  Command line argument functions and classes
 *  @{
 */

namespace command_line_parser {
	class CommandLineParser;
}

namespace command_line_argument {

	namespace {
		/**
		 * @brief default action parameters which are the keys of the JSON file
		 *
		 */
		static const std::vector<std::string> keyNames{"Key", "Name", "ShortCmd", "LongCmd", "DefaultValue", "NumberArguments", "Help"};
	}

	/**
	 * @brief CommandLineArgument class
	 *
	 */
	class CommandLineArgument : public json_data::JsonData {
		friend command_line_parser::CommandLineParser;

		public:
			/**
			 * @brief Function: static std::shared_ptr<command_line_argument::CommandLineArgument> makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const std::string & shortCmdKeyValue, const std::string & longCmdKeyValue, const std::string & defaultValueKeyValue, const int & numberOfArgumentsKeyValue, const std::string & helpKeyValue)
			 *
			 * \param jsonKey: key in the json file
			 * \param nameKeyValue: name of the argument
			 * \param shortCmdKeyValue: short command the user has to type to trigger the argument
			 * \param longCmdKeyValue: long command the user has to type to trigger the argument
			 * \param defaultValueKeyValue: default value of the argument
			 * \param numberOfArgumentsKeyValue: default value of the argument
			 * \param longCmdKeyValue: long command the user has to type to trigger the argument
			 * \param helpKeyValue: help of the argument
			 *
			 * this function constructs a new instance of class CommandLineArgument
			 */
			static std::shared_ptr<command_line_argument::CommandLineArgument> makeJsonData(const std::string & jsonKey, const std::string & nameKeyValue, const std::string & shortCmdKeyValue, const std::string & longCmdKeyValue, const std::string & defaultValueKeyValue, const int & numberOfArgumentsKeyValue, const std::string & helpKeyValue);

			/**
			 * @brief Function: CommandLineArgument(const std::string & jsonKey, const std::string & nameKeyValue = std::string(), const std::string & shortCmdKeyValue = std::string(), const std::string & longCmdKeyValue = std::string(), const std::string & defaultValueKeyValue = std::string(), const int & numberOfArgumentsKeyValue = -1, const std::string & helpKeyValue = std::string())
			 *
			 * \param jsonKey: key in the json file
			 * \param nameKeyValue: name of the argument
			 * \param shortCmdKeyValue: short command the user has to type to trigger the argument
			 * \param longCmdKeyValue: long command the user has to type to trigger the argument
			 * \param defaultValueKeyValue: default value of the argument
			 * \param numberOfArgumentsKeyValue: default value of the argument
			 * \param longCmdKeyValue: long command the user has to type to trigger the argument
			 * \param helpKeyValue: help of the argument
			 *
			 * Main Window json data constructor
			 */
			explicit CommandLineArgument(const std::string & jsonKey, const std::string & nameKeyValue = std::string(), const std::string & shortCmdKeyValue = std::string(), const std::string & longCmdKeyValue = std::string(), const std::string & defaultValueKeyValue = std::string(), const int & numberOfArgumentsKeyValue = -1, const std::string & helpKeyValue = std::string());

			// Move and copy constructor
			/**
			 * @brief Function: CommandLineArgument(const command_line_argument::CommandLineArgument & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main Window json data copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			CommandLineArgument(const command_line_argument::CommandLineArgument & rhs);

			/**
			 * @brief Function: CommandLineArgument::CommandLineArgument(command_line_argument::CommandLineArgument && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main Window json data move constructor
			 */
			explicit CommandLineArgument(command_line_argument::CommandLineArgument && rhs);

			/**
			 * @brief Function: virtual ~CommandLineArgument()
			 *
			 * Main Window json data structure destructor
			 */
			virtual ~CommandLineArgument();

			// Move and copy assignment operators
			/**
			 * @brief Function: CommandLineArgument & operator=(const command_line_argument::CommandLineArgument & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Main Window json data copy assignment operator
			 */
			CommandLineArgument & operator=(const command_line_argument::CommandLineArgument & rhs);

			/**
			 * @brief Function: CommandLineArgument & operator=(command_line_argument::CommandLineArgument && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Main Window json data move assignment operator
			 */
			CommandLineArgument & operator=(command_line_argument::CommandLineArgument && rhs);

			/**
			 * @brief Function: bool operator==(const command_line_argument::CommandLineArgument & rhs)
			 *
			 * \param rhs: right side class to compare
			 *
			 * Main Window json data operator == overloading
			 */
			bool operator==(const command_line_argument::CommandLineArgument & rhs);

			/**
			 * @brief Function: bool operator!=(const command_line_argument::CommandLineArgument & rhs)
			 *
			 * \param lhs: left side class to compare
			 * \param rhs: right side class to compare
			 *
			 * Main Window json data operator != overloading
			 */
			bool operator!=(const command_line_argument::CommandLineArgument & rhs);

			/**
			 * @brief Function: virtual const std::string print() const override
			 *
			 * \return main window json data converted to std::string
			 *
			 * This functions prints main window json data info to std::string
			 */
			virtual const std::string print() const override;

			/**
			 * @brief Function: const std::string & getKey() const
			 *
			 * \return key under which the JSON object for this argument is
			 *
			 * This functions returns the key under which the JSON object for this argument is
			 */
			const std::string & getKey() const;

			/**
			 * @brief Function: const std::string & getName() const
			 *
			 * \return name of the argument
			 *
			 * This functions returns the name of the argument
			 */
			const std::string & getName() const;

			/**
			 * @brief Function: const std::string & getShortCmd() const
			 *
			 * \return short command of the argument
			 *
			 * This functions returns the short command of the argument
			 */
			const std::string & getShortCmd() const;

			/**
			 * @brief Function: const std::string & getLongCmd() const
			 *
			 * \return long command of the argument
			 *
			 * This functions returns the long command of the argument
			 */
			const std::string & getLongCmd() const;

			/**
			 * @brief Function: const std::string & getDefaultValue() const
			 *
			 * \return default value of the argument
			 *
			 * This functions returns the default value of the argument
			 */
			const std::string & getDefaultValue() const;

			/**
			 * @brief Function: const int & getNumberOfArguments() const
			 *
			 * \return number of arguments
			 *
			 * This functions returns the number of arguments
			 */
			const int & getNumberOfArguments() const;

			/**
			 * @brief Function: const std::string & getHelp() const
			 *
			 * \return help of the argument
			 *
			 * This functions returns the help of the argument
			 */
			const std::string & getHelp() const;

			/**
			 * @brief Function: virtual bool isSameFieldValue(const std::string & name, const void * value) const override
			 *
			 * \param name: name of the name of the member as a string
			 * \param value: value of the member
			 *
			 * \return if field value matches value
			 *
			 * This functions compares the input value with the member of CommandLineArgument by accessing it through its name
			 */
			virtual bool isSameFieldValue(const std::string & name, const void * value) const override;

		private:
			/**
			 * @brief key under which the JSON object is
			 *
			 */
			std::string key;

			/**
			 * @brief name of the argument
			 *
			 */
			std::string name;

			/**
			 * @brief short command of the argument
			 *
			 */
			std::string shortCmd;

			/**
			 * @brief long command of the argument
			 *
			 */
			std::string longCmd;

			/**
			 * @brief default value of the argument
			 *
			 */
			std::string defaultValue;

			/**
			 * @brief number of arguments
			 *
			 */
			int numberOfArguments;

			/**
			 * @brief help of the argument
			 *
			 */
			std::string help;

			/**
			 * @brief Function: virtual void setValueFromMemberName(const std::string & name, const void * value) override
			 *
			 * \param name: name of the member as a string
			 * \param value: value to be assigned to the element
			 *
			 * This functions assign a value to a member of CommandLineArgument by accessing it through its name
			 */
			virtual void setValueFromMemberName(const std::string & name, const void * value) override;

			/**
			 * @brief Function: virtual const void * getValueFromMemberName(const std::string & name) const override
			 *
			 * \param name: name of the name of the member as a string
			 *
			 * \return value of the member
			 *
			 * This functions returns the value of a member of CommandLineArgument by accessing it through its name
			 */
			virtual const void * getValueFromMemberName(const std::string & name) const override;

	};

}
/** @} */ // End of CommandLineArgumentGroup group

#endif // COMMAND_LINE_ARGUMENT_H
