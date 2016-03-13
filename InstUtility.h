/*
 * InstUtility.h
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#ifndef INSTUTILITY_H_
#define INSTUTILITY_H_

#include <sstream>
#include <string>

namespace LB {

// enum class for instruction type
// R-type, I-type, J-type, Specialized, Undefined(ex. error)
enum class InstType : unsigned {
    R, I, J, S, Undef
};

template<typename Tp>
std::string toString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << val;
    return oss.str();
}

// if has number, use decimal
template<typename Tp>
std::string toDecString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << val;
    return oss.str();
}

// if has number, use hex-decimal
template<typename Tp>
std::string toHexString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << std::showbase << std::hex << val;
    return oss.str();
}

// get bits from range [l, r)
// ex. getBitsInRange(0xC, 0, 3) returns 0x4
// 0xC = 0b1100 returns 0b100
// zero based
unsigned getBitsInRange(const unsigned& src, const int& l, const int& r);

} /* namespace LB */

#endif /* INSTUTILITY_H_ */
