#ifndef JSON_DATA_H
#define JSON_DATA_H
/**
 * @copyright
 * @file json_data.h
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief Json Data header file
*/

#include <set>

#include "global_classes.h"
#include "printable_object.h"

/** @defgroup JsonDataGroup Json Data Doxygen Group
 *  Json data functions and classes
 *  @{
 */

namespace json_data {

	/**
	 * @brief JsonData class
	 *
	 */
	class JsonData : public printable_object::PrintableObject {
		public:
			/**
			 * @brief parameter type
			 *
			 */
			typedef std::set<std::string, global_classes::StringCompare> parameter_t;

			/**
			 * @brief Function: virtual const parameter_t & getParameters() const final
			 *
			 * \return the list of parameters to be looked for in the JSON file
			 *
			 * This functions returns the list of parameters to be looked for in the JSON file
			 */
			virtual const parameter_t & getParameters() const final;

		protected:
			/**
			 * @brief Function: explicit JsonData(const parameter_t & jsonParameters = parameter_t())
			 *
			 * json data constructor
			 */
			explicit JsonData(const parameter_t & jsonParameters = parameter_t());

			// Move and copy constructor
			/**
			 * @brief Function: JsonData(const json_data::JsonData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Json data copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			JsonData(const json_data::JsonData & rhs);

			/**
			 * @brief Function: JsonData::JsonData(json_data::JsonData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Json data move constructor
			 */
			explicit JsonData(json_data::JsonData && rhs);

			/**
			 * @brief Function: virtual ~JsonData()
			 *
			 * json data structure destructor
			 */
			virtual ~JsonData();

			// Move and copy assignment operators
			/**
			 * @brief Function: JsonData & operator=(const json_data::JsonData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * Json data copy assignment operator
			 */
			JsonData & operator=(const json_data::JsonData & rhs);

			/**
			 * @brief Function: JsonData & operator=(json_data::JsonData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * Json data move assignment operator
			 */
			JsonData & operator=(json_data::JsonData && rhs);

			/**
			 * @brief Function: virtual const std::string print() const override
			 *
			 * \return json data converted to std::string
			 *
			 * This functions prints json data info to std::string
			 */
			virtual const std::string print() const override;

			/**
			 * @brief Function: void addParameter(const std::string & name)
			 *
			 * \param name: name of the member as a string
			 *
			 * This functions adds a member to the list of parameters
			 */
			virtual void addParameter(const std::string & name) final;

			/**
			 * @brief Function: virtual void setValueFromMemberName(const std::string & name, const void * value)
			 *
			 * \param name: name of the name of the member as a string
			 * \param value: value to be assigned to the element
			 *
			 * This functions assign a value to a member of JsonData by accessing it through its name
			 */
			virtual void setValueFromMemberName(const std::string & name, const void * value) = 0;

			/**
			 * @brief Function: virtual const void * getValueFromMemberName(const std::string & name) const
			 *
			 * \param name: name of the name of the member as a string
			 *
			 * \return value of the member
			 *
			 * This functions returns the value of a member of JsonData by accessing it through its name
			 */
			virtual const void * getValueFromMemberName(const std::string & name) const = 0;

			/**
			 * @brief Function: virtual bool isSameFieldValue(const std::string & name, const void * value) const
			 *
			 * \param name: name of the name of the member as a string
			 * \param value: value of the member
			 *
			 * \return if field value matches value
			 *
			 * This functions compares the input value with the member of JsonData by accessing it through its name
			 */
			virtual bool isSameFieldValue(const std::string & name, const void * value) const = 0;

			/**
			 * @brief Function: bool operator==(const json_data::JsonData & rhs)
			 *
			 * \param rhs: right side class to compare
			 *
			 * Json data operator == overloading
			 */
			bool operator==(const json_data::JsonData & rhs);

			/**
			 * @brief Function: bool operator!=(const json_data::JsonData & rhs)
			 *
			 * \param rhs: right side class to compare
			 *
			 * Json data operator != overloading
			 */
			bool operator!=(const json_data::JsonData & rhs);

		private:
			/**
			 * @brief action parameters
			 * Using set because:
			 * - values will not be changed
			 * - ensure fast find (order O(log(N)))
			 *
			 */
			parameter_t parameters;

	};

}
/** @} */ // End of JsonDataGroup group

#endif // JSON_DATA_H
