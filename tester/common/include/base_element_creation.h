#ifndef BASE_ELEMENT_CREATION_H
#define BASE_ELEMENT_CREATION_H
/**
 * @copyright
 * @file base_element_creation.h
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Base element creation header file
 */

#include <memory>

/** @defgroup BaseElementCreationGroup Base Element Creation Group
 *  Base element creation functions and classes
 *  @{
 */

namespace base_element_creation {

	/**
	 * @brief BaseElementCreation class
	 *
	 */
	class BaseElementCreation {

		public:
			/**
			 * @brief Function: static std::shared_ptr<derivedType> create(ConstructorArgs && ... args)
			 *
			 * \param args: constructor arguments
			 *
			 * This function creates an object with a variable number of argumnets
			 */
			template<typename derivedType, typename ... ConstructorArgs>
			static std::shared_ptr<derivedType> create(ConstructorArgs && ... args);

			/**
			 * @brief Function: explicit BaseElementCreation()
			 *
			 * Base element creation constructor
			 */
			explicit BaseElementCreation();

			/**
			 * @brief Function: virtual ~BaseElementCreation()
			 *
			 * Base element creation destructor
			 */
			virtual ~BaseElementCreation();

			/**
			 * @brief Function: virtual void postProcessCreation()
			 *
			 * This function run tasks that follows the object creation
			 */
			virtual void postProcessCreation() = 0;
	};

}
/** @} */ // End of BaseElementCreationGroup group

template<typename derivedType, typename ... ConstructorArgs>
std::shared_ptr<derivedType> base_element_creation::BaseElementCreation::create(ConstructorArgs && ... args) {
	std::shared_ptr<derivedType> obj = std::make_shared<derivedType>(std::forward<ConstructorArgs>(args)...);
	obj->postProcessCreation();
	return obj;
}

#endif // BASE_ELEMENT_CREATION_H
