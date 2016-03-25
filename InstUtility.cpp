/*
 * InstUtility.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstUtility.h"

unsigned LB::getBitsInRange(const unsigned& src, const int& l, const int& r) {
    unsigned mask = 0;
    for (int i = l; i < r; ++i) {
        mask |= (1 << i);
    }
    return (src & mask) >> l;
}
