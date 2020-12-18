#ifndef SINGLETON_H
#define SINGLETON_H
/**
 * @copyright
 * @file singleton.h
 * @author Andrea Gianarda
 * @date 12th November 2020
 * @brief Singleton header file
 */

/** @defgroup SingletonGroup Singleton Group
 *  Singleton functions and classes
 *  @{
 */
namespace app {

	namespace utility {

		/**
		 * @brief Singleton class
		 *
		 */
		template<typename derivedType>
		class Singleton {

			public:
				/**
				 * @brief Function: static derivedType * getInstance()
				 *
				 * This function run tasks that follows the object creation
				 */
				static derivedType * getInstance();

				/**
				 * @brief Function: virtual ~Singleton()
				 *
				 * Singleton destructor
				 */
				virtual ~Singleton();

			protected:

				/**
				 * @brief Function: explicit Singleton()
				 *
				 * Singleton constructor
				 */
				explicit Singleton();

			private:

				/**
				 * @brief singleton instance
				 *
				 */
				static derivedType * instance;

		};

	}

}
/** @} */ // End of SingletonGroup group

template<typename derivedType>
derivedType * app::utility::Singleton<derivedType>::instance = nullptr;

template<typename derivedType>
derivedType * app::utility::Singleton<derivedType>::getInstance() {
	if (instance == nullptr) {
		instance = new derivedType();
	}

	return instance;
}

template<typename derivedType>
app::utility::Singleton<derivedType>::Singleton() {

}

template<typename derivedType>
app::utility::Singleton<derivedType>::~Singleton() {

}

#endif // SINGLETON_H
