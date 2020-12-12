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

					/**
					 * @brief Function: const typename app::base::json::Action<Data>::action_data_t & getActions() const
					 *
					 * \return the map of actions
					 *
					 * This functions returns the map of actions
					 */
					const typename app::base::json::Action<Data>::action_data_t & getActions() const;

					/**
					 * @brief Function: const std::unique_ptr<Data> & getInvalidData() const
					 *
					 * \return the invalid data pointer returned by functions if no data is found
					 *
					 * This functions returns the invalid data pointer returned by functions if no data is found
					 */
					const std::unique_ptr<Data> & getInvalidData() const;

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
					 * @brief Function: const QStringList & getActionJsonFiles() const
					 *
					 * \return the list of parsed JSON files
					 *
					 * This functions returns the list of parsed JSON files
					 */
					const QStringList & getActionJsonFiles() const;

					/**
					 * @brief Function: const QString getActionJsonFilesAsString() const
					 *
					 * \return a string with the list of parsed JSON files
					 *
					 * This functions returns a string listing the parsed JSON files
					 */
					const QString getActionJsonFilesAsString() const;


				protected:
					/**
					 * @brief Function: explicit Action()
					 *
					 * Default Json Action class constructor
					 */
					explicit Action();

					/**
					 * @brief Function: virtual ~Action()
					 *
					 * Json Action class destructor
					 */
					virtual ~Action();

					/**
					 * @brief map of commands and information
					 * key is the action in the JSON file
					 * value is the class storing information about the action
					 *
					 */
					action_data_t actionData;

					/**
					 * @brief Function: enableFunction<FuncRet> appendActionData(const QStringList & jsonFiles)
					 *
					 * \param jsonFiles: list of JSON file names
					 *
					 * This function append to the action data map with the content from the json files
					 */
					template<typename FuncRet = void>
					enableFunction<FuncRet> appendActionData(const QStringList & jsonFiles);

					/**
					 * @brief Function: enableFunction<FuncRet> appendActionData(const QString & filename)
					 *
					 * \param filename: JSON file name to append
					 *
					 * This function append to the action data map with the content of a JSON file
					 */
					template<typename FuncRet = void>
					enableFunction<FuncRet> appendActionData(const QString & filename);

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

				private:

					/**
					 * @brief list of JSON filenames that were parsed
					 *
					 */
					QStringList actionJsonFiles;

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
app::base::json::Action<Data>::Action() : actionData(app::base::json::Action<Data>::action_data_t()), actionJsonFiles(QStringList()), invalidData(nullptr) {

}

template<class Data>
app::base::json::Action<Data>::~Action() {
	LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Json Action class destructor");
}

template<class Data>
template<typename FuncRet>
typename app::base::json::Action<Data>::template enableFunction<FuncRet> app::base::json::Action<Data>::appendActionData(const QStringList & jsonFiles) {

	EXCEPTION_ACTION_COND((jsonFiles.isEmpty() == true), throw, "Provided an empty JSON file list to function " << __func__);

	for (const auto & filename : jsonFiles) {
		this->appendActionData(filename);
	}

}

template<class Data>
template<typename FuncRet>
typename app::base::json::Action<Data>::template enableFunction<FuncRet> app::base::json::Action<Data>::appendActionData(const QString & filename) {

	EXCEPTION_ACTION_COND((filename.isEmpty() == true), throw, "Provided an empty JSON file name to function " << __func__);

	app::utility::json::Parser commands(filename, QIODevice::ReadOnly);
	const std::list<std::string> keys = app::utility::qStringListToStdList(commands.getJsonKeys());

	if (keys.empty() == false) {
		// Iterate over keys in JSON file
		std::for_each(keys.cbegin(), keys.cend(), [&] (const std::string & key) {
			// Create JSON data
			std::unique_ptr<Data> newData = std::make_unique<Data>(key);
			const app::base::json::Data::parameter_t & dataParameters = newData->getParameters();
			std::for_each(dataParameters.cbegin(), dataParameters.cend(), [&] (const std::string & param) {
				const QString paramValue = commands.findKeyValue(QString::fromStdString(key), QString::fromStdString(param));
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

			LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Appending data for key " << it->first << ": " << *(it->second));

			if (this->actionJsonFiles.contains(filename) == false) {
				LOG_INFO(app::logger::info_level_e::ZERO, jsonActionOverall,  "Adding " << filename << " to the list of action JSON files");
				this->actionJsonFiles.append(filename);
			} else {
				LOG_WARNING(jsonActionOverall,  "File " << filename << " has already been added to the list of JSON files");
			}

		});
	};

}

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

template<class Data>
CONST_GETTER(app::base::json::Action<Data>::getInvalidData, std::unique_ptr<Data> &, this->invalidData)

template<class Data>
CONST_GETTER(app::base::json::Action<Data>::getActions, typename app::base::json::Action<Data>::action_data_t &, this->actionData)

template<class Data>
CONST_GETTER(app::base::json::Action<Data>::getActionJsonFiles, QStringList &, this->actionJsonFiles)

template<class Data>
const QString app::base::json::Action<Data>::getActionJsonFilesAsString() const {
	QString jsonFilePrint = QString();
	if (this->actionJsonFiles.empty() == true) {
		jsonFilePrint.append("no input JSON file");
	} else {
		jsonFilePrint.append(" JSON file");
		if (this->actionJsonFiles.size() == 1) {
			jsonFilePrint.append(": ");
		} else {
			// Append s to make plural as the file list has more than 1 element
			jsonFilePrint.append("s: ");
		}

		for (const auto & filename : this->actionJsonFiles) {
			if (filename.compare(this->actionJsonFiles.constFirst(), Qt::CaseSensitive) != 0) {
				jsonFilePrint.append(", ");
			}
			jsonFilePrint.append(filename);
		}
	}

	return jsonFilePrint;
}

#endif // JSON_ACTION_H
