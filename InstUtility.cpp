/*
 * InstUtility.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstUtility.h"

unsigned LB::getBitsInRange(const unsigned& src, const int& l, const int& r) {
    return (src << (32 - r)) >> (l + (32 - r));
}
