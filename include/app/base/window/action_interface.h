#ifndef WINDOW_ACTION_INTERFACE_H
#define WINDOW_ACTION_INTERFACE_H
/**
 * @copyright
 * @file action_interface.h
 * @author Andrea Gianarda
 * @date 10th June 2020
 * @brief Window Action Interface header file
*/

/** @defgroup WindowGroup Window Doxygen Group
 *  Window functions and classes
 *  @{
 */

namespace app {

	namespace base {

		namespace window {

			/**
			 * @brief Interface class
			 *
			 */
			class ActionInterface {

				public:

				protected:

					/**
					 * @brief Function: virtual ~ActionInterface()
					 *
					 * Action interface destructor
					 */
					virtual ~ActionInterface() = default;

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

	}

}
/** @} */ // End of WindowGroup group

#endif // WINDOW_ACTION_INTERFACE_H
