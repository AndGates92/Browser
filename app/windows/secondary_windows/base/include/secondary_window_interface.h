#ifndef SECONDARY_WINDOW_INTERFACE_H
#define SECONDARY_WINDOW_INTERFACE_H
/**
 * @copyright
 * @file secondary_window_interface.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Secondary Window Interface header file
*/

/** @defgroup SecondaryWindowInterfaceGroup Secondary Window Interface Doxygen Group
 *  Secondary Window Interface functions and classes
 *  @{
 */

namespace secondary_window_interface {

	/**
	 * @brief SecondaryWindowInterface class
	 *
	 */
	class SecondaryWindowInterface {

		public:

		protected:

			/**
			 * @brief Function: virtual ~SecondaryWindowInterface()
			 *
			 * File handling widgets destructor
			 */
			virtual ~SecondaryWindowInterface() = default;

			/**
			 * @brief Function: virtual void apply()
			 *
			 * This function is the slot of the apply action
			 */
			virtual void apply() = 0;

			/**
			 * @brief Function: virtual void cancel()
			 *
			 * This function is the slot of the cancel action
			 */
			virtual void cancel() = 0;

			/**
			 * @brief Function: virtual void close()
			 *
			 * This function closes the popup
			 */
			virtual void close() = 0;

			/**
			 * @brief Function: virtual void connectSignals()
			 *
			 * This function connects signals and slots between main window elements from the derived class
			 */
			virtual void connectSignals() = 0;

		private:

	};

}
/** @} */ // End of SecondaryWindowInterfaceGroup group

#endif // SECONDARY_WINDOW_INTERFACE_H
