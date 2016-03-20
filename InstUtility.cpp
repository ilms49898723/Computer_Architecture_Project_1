/*
 * InstUtility.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstUtility.h"

int LB::toSigned(const unsigned& src, const LB::InstMemLen& type) {
    if (type == LB::InstMemLen::WORD) {
        return static_cast<int>(src);
    }
    else if (type == LB::InstMemLen::HALFWORD) {
        int var = static_cast<int>(src << 16);
        int ret = var >> 16;
        return ret;
    }
    else {
        int var = static_cast<int>(src << 24);
        int ret = var >> 24;
        return ret;
    }
}

unsigned LB::toUnsigned(const int& src) {
    return static_cast<unsigned>(src);
}

unsigned LB::getBitsInRange(const unsigned& src, const int& l, const int& r) {
    return (src << (32 - r)) >> (l + (32 - r));
}
