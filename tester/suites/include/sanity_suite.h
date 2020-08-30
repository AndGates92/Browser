#ifndef SANITY_SUITE_H
#define SANITY_SUITE_H
/**
 * @copyright
 * @file sanity_suite.h
 * @author Andrea Gianarda
 * @date 15th September 2020
 * @brief Sanity suite header file
 */

// Qt libraries
// Required by qInfo
#include <QtCore/QtDebug>

#include <memory>

#include "constructor_macros.h"
#include "printable_object.h"
#include "base_suite.h"

/** @defgroup SanitySuiteGroup Sanity suite Group
 *  Sanity suite functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(sanitySuiteOverall)

namespace sanity_suite {

	/**
	 * @brief SanitySuite class
	 *
	 */
	class SanitySuite : public base_suite::BaseSuite {

		public:
			/**
			 * @brief Function: explicit SanitySuite(const std::shared_ptr<base_factory::BaseFactory> testFactory, const base_suite::BaseSuite::tests_container_t & testList = base_suite::BaseSuite::tests_container_t())
			 *
			 * \param testFactory: test factory
			 * \param testList: initial collection of tests
			 *
			 * Sanity suite constructor
			 */
			explicit SanitySuite(const std::shared_ptr<base_factory::BaseFactory> testFactory, const base_suite::BaseSuite::tests_container_t & testList = base_suite::BaseSuite::tests_container_t());

			/**
			 * @brief Function: virtual ~SanitySuite()
			 *
			 * Sanity suite destructor
			 */
			virtual ~SanitySuite();

			/**
			 * @brief Function: virtual void populate() override
			 *
			 * This function populates the suite
			 */
			virtual void populate() override;

		protected:

		private:
			// Move and copy constructor
			/**
			 * @brief Disable move and copy constructors and operator= overloading for class SanitySuite
			 *
			 */
			DISABLE_COPY_MOVE(SanitySuite)

	};

}
/** @} */ // End of SanitySuiteGroup group

#endif // SANITY_SUITE_H
