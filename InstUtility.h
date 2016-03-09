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

template<typename Tp>
std::string toString(const Tp val) {
    std::basic_stringstream<char> oss;
    oss << val;
    return oss.str();
}

template<typename Tp>
std::string toDecString(const Tp val) {
    std::basic_stringstream<char> oss;
    oss << val;
    return oss.str();
}

template<typename Tp>
std::string toHexString(const Tp val) {
    std::basic_stringstream<char> oss;
    oss << std::showbase << std::hex << val;
    return oss.str();
}

} /* namespace LB */

#endif /* INSTUTILITY_H_ */
