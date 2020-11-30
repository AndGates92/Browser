#ifndef QT_OPERATOR_H
#define QT_OPERATOR_H
/**
 * @copyright
 * @file qt_operator.h
 * @author Andrea Gianarda
 * @date 24th September 2020
 * @brief Qt operator header file
 */

#include <string>

#include <QtCore/QtDebug>
#include <QtCore/QTextStream>

/** @defgroup QtOperatorGroup Qt Operator Group
 *  Qt operator functions and classes
 *  @{
 */

/**
 * @brief Function: QTextStream & operator<<(QTextStream & stream, const std::string str)
 *
 * \param stream: stream to append the string to
 * \param str: string to print
 *
 * operator << overloading with QTextStream
 */
QTextStream & operator<<(QTextStream & stream, const std::string str);

/**
 * @brief Function: QDebug & operator<<(QDebug & stream, const std::string str)
 *
 * \param stream: output stream to append the string to
 * \param str: string to print
 *
 * operator << overloading with QDebug
 */
QDebug & operator<<(QDebug & stream, const std::string str);

/** @} */ // End of QtOperator group

#endif // QT_OPERATOR_H
