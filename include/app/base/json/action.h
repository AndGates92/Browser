#ifndef JSON_ACTION_H
#define JSON_ACTION_H
/**
 * @copyright
 * @file action.h
 * @author Andrea Gianarda
 * @date 19th of September 2020
 * @brief Json Action class header file
*/

#include <map>
#include <string>
#include <memory>
#include <utility>

// Qt libraries
#include <QtWidgets/QWidget>

#include "app/utility/cpp/qt_types_to_stl.h"
#include "app/utility/qt/qt_operator.h"
#include "app/shared/enums.h"
#include "app/shared/setters_getters.h"
#include "app/utility/logger/macros.h"
#include "app/shared/constructor_macros.h"
#include "app/base/json/data.h"
#include "app/utility/json/parser.h"

/** @defgroup JsonGroup Json Doxygen Group
 *  Json functions and classes
 *  @{
 */

EXPORT_CONTEXT(jsonActionOverall)

namespace app {

	namespace base {

		namespace json {

			/**
			 * @brief Action class
			 *
			 */
			template<class Data>
			class Action {

				template<typename FuncRet>
				using enableFunction = typename std::enable_if<std::is_base_of<app::base::json::Data, Data>::value, FuncRet>::type;

				public:
					/**
					 * @brief action data type
					 *
					 */
					typedef std::map<std::string, std::unique_ptr<Data>> action_data_t;

				protected:
					/**
					 * @brief Function: explicit Action(QString jsonFileName = QString())
					 *
					 * \param jsonFileName: JSON filename
					 *
					 * Json Action class constructor
					 */
					explicit Action(QString jsonFileName = QString());

					/**
					 * @brief Function: virtual ~Action()
					 *
					 * Json Action class destructor
					 */
					virtual ~Action();

					/**
					 * @brief tab commands and information
					 *
					 */
					app::utility::json::Parser commands;

					/**
					 * @brief tab commands and information
					 * key is the action in the JSON file
					 * value is the class storing information about the action
					 *
					 */
					action_data_t actionData;

					/**
					 * @brief Function: virtual void populateActionData() final
					 *
					 * This function populates the action data map with the content from the json data
					 */
					template<typename FuncRet = void>
					enableFunction<FuncRet> populateActionData();

					/**
					 * @brief Function: virtual const std::unique_ptr<Data> & findDataWithFieldValue(const std::string & name, const void * value) const final
					 *
					 * \param name: name of the name of the member as a string
					 * \param value: value of the member
					 *
					 * \return JSON data having a matching field value
					 *
					 * This functions searching a data having a matching field value
					 * This functions returns the first match or nullptr if no match
					 */
					template<typename FuncRet = const std::unique_ptr<Data> &>
					enableFunction<FuncRet> findDataWithFieldValue(const std::string & name, const void * value) const;

					/**
					 * @brief Function: virtual void addItemToActionData(std::unique_ptr<Data> & data, const std::string & key, const std::string & item)
					 *
					 * \param data: data to be updated
					 * \param key: key the tiem belongs to
					 * \param item: item to add
					 *
					 * This functions adds an item linked to the key to the data provided as input
					 */
					virtual void addItemToActionData(std::unique_ptr<Data> & data, const std::string & key, const std::string & item) = 0;

					/**
					 * @brief Function: const std::unique_ptr<Data> & getInvalidData() const
					 *
					 * \return the invalid data pointer returned by functions if no data is found
					 *
					 * This functions returns the invalid data pointer returned by functions if no data is found
					 */
					const std::unique_ptr<Data> & getInvalidData() const;

					/**
					 * @brief Function: const QString & getSourceFileName() const
					 *
					 * \return the name of the JSON source file parsed
					 *
					 * This functions returns the name of the JSON source file parsed
					 */
					const QString & getSourceFileName() const;

				private:

					/**
					 * @brief JSON file name that was parsed
					 *
					 */
					const QString sourceFileName;

					/**
					 * @brief invalid data
					 *
					 */
					const std::unique_ptr<Data> invalidData;

					// Move and copy constructor
					/**
					 * @brief Disable move and copy constructors and operator= overloading for class Action
					 *
					 */
					DISABLE_COPY_MOVE(Action)

			};

		}

	}

}
/** @} */ // End of JsonGroup group

template<class Data>
app::base::json::Action<Data>::Action(QString jsonFileName) : commands(app::utility::json::Parser(jsonFileName, QIODevice::ReadOnly)), actionData(app::base::json::Action<Data>::action_data_t()), sourceFileName(jsonFileName), invalidData(nullptr) {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Json Action classe constructor");
}

template<class Data>
app::base::json::Action<Data>::~Action() {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Json Action class destructor");
}

template<class Data>
template<typename FuncRet>
typename app::base::json::Action<Data>::template enableFunction<FuncRet> app::base::json::Action<Data>::populateActionData() {

	const std::list<std::string> keys = app::utility::qStringListToStdList(this->commands.getJsonKeys());

	if (keys.empty() == false) {
		// Iterate over keys in JSON file
		std::for_each(keys.cbegin(), keys.cend(), [&] (const std::string & key) {
			// Create JSON data
			std::unique_ptr<Data> newData = std::make_unique<Data>(key);
			const app::base::json::Data::parameter_t & dataParameters = newData->getParameters();
			std::for_each(dataParameters.cbegin(), dataParameters.cend(), [&] (const std::string & param) {
				const QString paramValue = this->commands.findKeyValue(QString::fromStdString(key), QString::fromStdString(param));
				const std::string value = paramValue.toStdString();
				this->addItemToActionData(newData, param, value);
			});

			std::pair<std::string, std::unique_ptr<Data>> dataPair;

			dataPair.first = key;
			// Pass ownership to dataPair
			dataPair.second = std::move(newData);

			// insert returns a pair where:
			// - first points to the newly created iterator or the element with the same key
			// - second is true if the insertion is successful, false otherwise
			const auto [it, success] = this->actionData.insert(std::move(dataPair));

			EXCEPTION_ACTION_COND((success == false), throw, "Insertion of element " << *newData << " failed.");

		});
	};

	for (const auto & data : this->actionData)
		LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Data for key " << data.first << " is " << *(data.second));

}

template<class Data>
CONST_GETTER(app::base::json::Action<Data>::getInvalidData, std::unique_ptr<Data> &, this->invalidData)

template<class Data>
CONST_GETTER(app::base::json::Action<Data>::getSourceFileName, QString &, this->sourceFileName)

template<class Data>
template<typename FuncRet>
typename app::base::json::Action<Data>::template enableFunction<FuncRet> app::base::json::Action<Data>::findDataWithFieldValue(const std::string & name, const void * value) const {
	const typename app::base::json::Action<Data>::action_data_t::const_iterator foundData = std::find_if(this->actionData.cbegin(), this->actionData.cend(), [&] (const auto & data) -> bool {
		const std::unique_ptr<Data> & commandData = data.second;
		bool found = commandData->isSameFieldValue(name, value);
		return found;
	});

	if (foundData != this->actionData.cend()) {
		return foundData->second;
	}

	LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Unable to find matching value for field " << name);

	return this->invalidData;
}

#endif // JSON_ACTION_H
