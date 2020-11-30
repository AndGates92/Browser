#ifndef CPP_OPERATOR_H
#define CPP_OPERATOR_H
/**
 * @copyright
 * @file cpp_operator.h
 * @author Andrea Gianarda
 * @date 02nd November 2020
 * @brief C++ operator header file
 */

#include <string>
#include <iostream>

#include <QtCore/QString>
#include <QtCore/QSize>
#include <QtCore/QRect>
#include <QtCore/QDataStream>
#include <QtCore/QByteArray>

/** @defgroup CppOperatorGroup C++ Operator Group
 *  C++ operator functions and classes
 *  @{
 */

/**
 * @brief Function: std::ostream & operator<<(std::ostream & stream, const std::string & str)
 *
 * \param stream: stream to append the string to
 * \param str: string to print
 *
 * operator << overloading between std::ostream and std::string
 */
std::ostream & operator<<(std::ostream & stream, const std::string & str);

/**
 * @brief Function: std::ostream & operator<<(std::ostream & stream, const QString & str)
 *
 * \param stream: stream to append the string to
 * \param str: string to print
 *
 * operator << overloading between std::ostream and QString
 */
std::ostream & operator<<(std::ostream & stream, const QString & str);

/**
 * Structure that list needed types that overload operator<< between QDataStream and the type itself
 *
 */
template<class type>
struct CanBePrintedToQDataStream {
	enum {
		value = std::is_base_of<QSize, type>::value || std::is_base_of<QRect, type>::value || std::is_base_of<QPoint, type>::value || std::is_base_of<QKeySequence, type>::value || std::is_base_of<QStringList, type>::value
	};
};

/**
 * @brief Function: std::ostream & operator<<(std::ostream & stream, const QSize & size)
 *
 * \param stream: stream to append the string to
 * \param size: size to print
 *
 * operator << overloading between std::ostream and QSize
 */
template<class type, typename std::enable_if<CanBePrintedToQDataStream<type>::value, void>::type* = nullptr>
std::ostream & operator<<(std::ostream & stream, const type & obj) {
	QByteArray array = QByteArray();
	QDataStream dataStream(array);
	dataStream << obj;
	stream << array.constData();
	return stream;
}

/** @} */ // End of CppOperator group

#endif // CPP_OPERATOR_H
