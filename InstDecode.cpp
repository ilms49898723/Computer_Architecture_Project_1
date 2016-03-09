/*
 * InstDecode.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstDecode.h"
#include <cstdio>

namespace LB {

InstData InstDecode::decodeHexInst(const unsigned& src) {
    unsigned opCode = (src & 0xFC000000u) >> 26;
    printf("opCode = %x\n", opCode);
    return InstData();
}

InstData InstDecode::decodeHexInst(const unsigned* src) {
    const unsigned argu = (src[0] << 16) | src[1];
    return InstDecode::decodeHexInst(argu);
}

} /* namespace LB */
