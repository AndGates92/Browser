#ifndef MAIN_WINDOW_PAGE_DATA_H
#define MAIN_WINDOW_PAGE_DATA_H
/**
 * @copyright
 * @file main_window_page_data.h
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Page Data header file
*/

#include <memory>

#include "main_window_shared_types.h"
#include "printable_object.h"

/** @defgroup MainWindowPageDataGroup Main Window Page Data Doxygen Group
 *  Main Window page data functions and classes
 *  @{
 */

namespace main_window_web_engine_page {
	class MainWindowWebEnginePage;
}

namespace main_window_page_data {

	/**
	 * @brief MainWindowPageData class
	 *
	 */
	class MainWindowPageData final : public printable_object::PrintableObject {
		friend class main_window_web_engine_page::MainWindowWebEnginePage;

		public:

			/**
			 * @brief Function: static std::shared_ptr<main_window_page_data::MainWindowPageData> makePageData(const main_window_shared_types::page_type_e & type, const std::string & src, const void * data)
			 *
			 * \param type: type of the page
			 * \param src: source of the page
			 * \param data: extra data
			 *
			 * this function constructs a new instance of class MainWindowPageData
			 */
			static std::shared_ptr<main_window_page_data::MainWindowPageData> makePageData(const main_window_shared_types::page_type_e & type, const std::string & src, const void * data);

			/**
			 * @brief Function: MainWindowPageData(const main_window_shared_types::page_type_e & pageType, const std::string & src, const void * pageData = nullptr)
			 *
			 * \param pageType: type of the page
			 * \param src: source of the content of the page
			 * \param data: extra data
			 *
			 * page data constructor
			 */
			explicit MainWindowPageData(const main_window_shared_types::page_type_e & pageType, const std::string & src, const void * pageData = nullptr);

			// Move and copy constructor
			/**
			 * @brief Function: MainWindowPageData(const main_window_page_data::MainWindowPageData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * page data copy constructor
			 * Do not set it as explicit as copy-initialization is allowed
			 */
			MainWindowPageData(const main_window_page_data::MainWindowPageData & rhs);

			/**
			 * @brief Function: MainWindowPageData::MainWindowPageData(main_window_page_data::MainWindowPageData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * page data move constructor
			 */
			explicit MainWindowPageData(main_window_page_data::MainWindowPageData && rhs);

			// Move and copy assignment operators
			/**
			 * @brief Function: MainWindowPageData & operator=(const main_window_page_data::MainWindowPageData & rhs)
			 *
			 * \param rhs: class to copy
			 *
			 * page data copy assignment operator
			 */
			MainWindowPageData & operator=(const main_window_page_data::MainWindowPageData & rhs);

			/**
			 * @brief Function: MainWindowPageData & operator=(main_window_page_data::MainWindowPageData && rhs)
			 *
			 * \param rhs: class to move
			 *
			 * page data move assignment operator
			 */
			MainWindowPageData & operator=(main_window_page_data::MainWindowPageData && rhs);

			/**
			 * @brief Function: virtual ~MainWindowPageData()
			 *
			 * page data structure destructor
			 */
			virtual ~MainWindowPageData();

			/**
			 * @brief Function: friend bool operator==(const main_window_page_data::MainWindowPageData & rhs)
			 *
			 * \param lhs: left side class to compare
			 * \param rhs: right side class to compare
			 *
			 * page data operator == overloading
			 */
			friend bool operator==(const main_window_page_data::MainWindowPageData & lhs, const main_window_page_data::MainWindowPageData & rhs);

			/**
			 * @brief Function: friend bool operator!=(const main_window_page_data::MainWindowPageData & lhs, const main_window_page_data::MainWindowPageData & rhs)
			 *
			 * \param lhs: left side class to compare
			 * \param rhs: right side class to compare
			 *
			 * page data operator != overloading
			 */
			friend bool operator!=(const main_window_page_data::MainWindowPageData & lhs, const main_window_page_data::MainWindowPageData & rhs);

			/**
			 * @brief Function: virtual const std::string print() const override
			 *
			 * \return page data converted to std::string
			 *
			 * This functions prints page data info to std::string
			 */
			virtual const std::string print() const override;

		protected:

		private:
			/**
			 * @brief page type
			 *
			 */
			main_window_shared_types::page_type_e type;

			/**
			 * @brief source of the content of the page
			 *
			 */
			std::string source;

			/**
			 * @brief data pointer
			 *
			 */
			const void * data;

			/**
			 * @brief Function: const std::string & getSource() const
			 *
			 * \return source field of a page data object
			 *
			 * This functions returns the source field of a page data object
			 */
			const std::string & getSource() const;

			/**
			 * @brief Function: const main_window_shared_types::page_type_e & getType() const
			 *
			 * \return type field of a page data object
			 *
			 * This functions returns the type field of a page data object
			 */
			const main_window_shared_types::page_type_e & getType() const;

			/**
			 * @brief Function: const void * getData() const
			 *
			 * \return data field of a page data object
			 *
			 * This functions returns the data field of a page data object
			 */
			const void * getData() const;

			/**
			 * @brief Function: bool setSource(const std::string & newSource)
			 *
			 * \param newSource: new source of the page
			 *
			 * \return true is the value has changed and false if there have been an error or the value has not changed
			 *
			 * This functions sets the source of a page page data object
			 */
			bool setSource(const std::string & newSource);

			/**
			 * @brief Function: void setType(const main_window_shared_types::page_type_e & value)
			 *
			 * \param value: new type
			 *
			 * This functions sets the type field of a page page data object
			 */
			void setType(const main_window_shared_types::page_type_e & value);

			/**
			 * @brief Function: void setData(const void * value)
			 *
			 * \param value: new data
			 *
			 * This functions sets the data field of a page page data object
			 */
			void setData(const void * value);

	};

}
/** @} */ // End of MainWindowPageDataGroup group

#endif // MAIN_WINDOW_PAGE_DATA_H
