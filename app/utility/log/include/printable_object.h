#ifndef PRINTABLE_OBJECT_H
#define PRINTABLE_OBJECT_H
/**
 * @copyright
 * @file printable_object.h
 * @author Andrea Gianarda
 * @date 7th of August 2020
 * @brief Printable Object header file
*/

#include <QtCore/QLoggingCategory>

/** @defgroup PrintableObjectGroup Printable Object Doxygen Group
 *  Printable object functions and classes
 *  @{
 */

Q_DECLARE_LOGGING_CATEGORY(printableObjectOverall)

namespace printable_object {

	/**
	 * @brief PrintableObject class
	 *
	 */
	class PrintableObject {
		public:

			/**
			 * @brief Function: friend QDebug & operator<<(QDebug & os, const printable_object::PrintableObject & object)
			 *
			 * \param os: output stream to append the object to
			 * \param object: object to print
			 *
			 * object operator << overloading with QDebug
			 */
			friend QDebug & operator<<(QDebug & os, const printable_object::PrintableObject & object);

			/**
			 * @brief Function: friend QString & operator<<(QString & str, const printable_object::PrintableObject & object)
			 *
			 * \param str: string to append the object to
			 * \param object: object to print
			 *
			 * object operator << overloading with QString
			 */
			friend QString & operator<<(QString & str, const printable_object::PrintableObject & object);

			/**
			 * @brief Function: friend QTextStream & operator<<(QTextStream & str, const printable_object::PrintableObject & object)
			 *
			 * \param str: string to append the object to
			 * \param object: object to print
			 *
			 * object operator << overloading with QTextStream
			 */
			friend QTextStream & operator<<(QTextStream & str, const printable_object::PrintableObject & object);

			/**
			 * @brief Function: friend std::string operator<<(std::string str, const printable_object::PrintableObject & object)
			 *
			 * \param str: string to append the object to
			 * \param object: object to print
			 *
			 * object operator << overloading with std::string
			 */
			friend std::string operator<<(std::string str, const printable_object::PrintableObject & object);

			/**
			 * @brief Function: friend std::string operator+(std::string str, const printable_object::PrintableObject & object)
			 *
			 * \param str: string to append the object to
			 * \param object: object to print
			 *
			 * object operator + overloading with std::string
			 */
			friend std::string operator+(std::string str, const printable_object::PrintableObject & object);

		protected:
			/**
			 * @brief Function: explicit PrintableObject()
			 *
			 * Printable Object constructor
			 */
			explicit PrintableObject();

			/**
			 * @brief Function: ~PrintableObject()
			 *
			 * Printable Object destructor
			 */
			virtual ~PrintableObject();

			/**
			 * @brief Function: virtual const std::string print() const
			 *
			 * \return object to print converted to std::string
			 *
			 * This functions prints object to print info to std::string
			 */
			virtual const std::string print() const = 0;

			/**
			 * @brief Function: virtual QString qprint() const
			 *
			 * \return object to print converted to QString
			 *
			 * This functions prints object to print to QString
			 */
			virtual const QString qprint() const final;

		private:
	};

}
/** @} */ // End of PrintableObjectGroup group

#endif // PRINTABLE_OBJECT_H
