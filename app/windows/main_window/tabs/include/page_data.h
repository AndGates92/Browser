#ifndef MAIN_WINDOW_PAGE_DATA_H
#define MAIN_WINDOW_PAGE_DATA_H
/**
 * @copyright
 * @file page_data.h
 * @author Andrea Gianarda
 * @date 29th of March 2020
 * @brief Main Window Page Data header file
*/

#include <memory>

#include "windows/main_window/common/include/shared_types.h"
#include "utility/log/include/printable_object.h"

/** @defgroup MainWindowGroup Main Window Doxygen Group
 *  Main Window functions and classes
 *  @{
 */
namespace app {

	namespace main_window {

		namespace tab {

			class WebEnginePage;

			/**
			 * @brief PageData class
			 *
			 */
			class PageData final : public app::printable_object::PrintableObject {
				friend class app::main_window::tab::WebEnginePage;

				public:

					/**
					 * @brief Function: static std::shared_ptr<app::main_window::tab::PageData> makePageData(const app::main_window::page_type_e & type, const std::string & src, const void * data)
					 *
					 * \param type: type of the page
					 * \param src: source of the page
					 * \param data: extra data
					 *
					 * this function constructs a new instance of class PageData
					 */
					static std::shared_ptr<app::main_window::tab::PageData> makePageData(const app::main_window::page_type_e & type, const std::string & src, const void * data);

					/**
					 * @brief Function: PageData(const app::main_window::page_type_e & pageType, const std::string & src, const void * pageData = nullptr)
					 *
					 * \param pageType: type of the page
					 * \param src: source of the content of the page
					 * \param data: extra data
					 *
					 * page data constructor
					 */
					explicit PageData(const app::main_window::page_type_e & pageType, const std::string & src, const void * pageData = nullptr);

					// Move and copy constructor
					/**
					 * @brief Function: PageData(const app::main_window::tab::PageData & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * page data copy constructor
					 * Do not set it as explicit as copy-initialization is allowed
					 */
					PageData(const app::main_window::tab::PageData & rhs);

					/**
					 * @brief Function: PageData::PageData(app::main_window::tab::PageData && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * page data move constructor
					 */
					explicit PageData(app::main_window::tab::PageData && rhs);

					// Move and copy assignment operators
					/**
					 * @brief Function: PageData & operator=(const app::main_window::tab::PageData & rhs)
					 *
					 * \param rhs: class to copy
					 *
					 * page data copy assignment operator
					 */
					PageData & operator=(const app::main_window::tab::PageData & rhs);

					/**
					 * @brief Function: PageData & operator=(app::main_window::tab::PageData && rhs)
					 *
					 * \param rhs: class to move
					 *
					 * page data move assignment operator
					 */
					PageData & operator=(app::main_window::tab::PageData && rhs);

					/**
					 * @brief Function: virtual ~PageData()
					 *
					 * page data structure destructor
					 */
					virtual ~PageData();

					/**
					 * @brief Function: friend bool operator==(const app::main_window::tab::PageData & rhs)
					 *
					 * \param lhs: left side class to compare
					 * \param rhs: right side class to compare
					 *
					 * page data operator == overloading
					 */
					friend bool operator==(const app::main_window::tab::PageData & lhs, const app::main_window::tab::PageData & rhs);

					/**
					 * @brief Function: friend bool operator!=(const app::main_window::tab::PageData & lhs, const app::main_window::tab::PageData & rhs)
					 *
					 * \param lhs: left side class to compare
					 * \param rhs: right side class to compare
					 *
					 * page data operator != overloading
					 */
					friend bool operator!=(const app::main_window::tab::PageData & lhs, const app::main_window::tab::PageData & rhs);

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
					app::main_window::page_type_e type;

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
					 * @brief Function: const app::main_window::page_type_e & getType() const
					 *
					 * \return type field of a page data object
					 *
					 * This functions returns the type field of a page data object
					 */
					const app::main_window::page_type_e & getType() const;

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
					 * @brief Function: void setType(const app::main_window::page_type_e & value)
					 *
					 * \param value: new type
					 *
					 * This functions sets the type field of a page page data object
					 */
					void setType(const app::main_window::page_type_e & value);

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

	}

}
/** @} */ // End of MainWindowGroup group

#endif // MAIN_WINDOW_PAGE_DATA_H
