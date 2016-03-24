/*
 * InstErrorDetector.cpp
 *
 *  Created on: 2016/03/23
 *      Author: LittleBird
 */

#include "InstErrorDetector.h"

namespace LB {

bool InstErrorDetector::isRegWritable(const unsigned& reg) {
    return reg != 0U;
}

bool InstErrorDetector::isOverflowed(const int& src0, const int& src1, const InstOpType& op) {
    int a = src0;
    int b = src1;
    if (op == InstOpType::SUB) {
        b *= (-1);
    }
    int result = a + b;
    int signA = (a >= 0) ? 1 : -1;
    int signB = (b >= 0) ? 1 : -1;
    int signR = (result >= 0) ? 1 : -1;
    if (signA * signB < 0) {
        return false;
    }
    return signA * signR < 0;
}

bool InstErrorDetector::isValidMemoryAddr(const unsigned& addr) {
    return addr >= 0U && addr < 1024U;
}

bool InstErrorDetector::isAlignedAddr(const unsigned& addr, const InstMemLen& type) {
    if (type == InstMemLen::WORD) {
        return (addr % 4) == 0;
    }
    else if (type == InstMemLen::HALFWORD) {
        return (addr & 1) == 0;
    }
    else {
        return true;
    }
}

} /* namespace LB */
