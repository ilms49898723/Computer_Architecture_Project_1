/*
 * InstDecode.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstDecode.h"
#include <cstdio>

LB::InstData LB::InstDecode::decodeHexInst(const unsigned& src) {
    unsigned opCode = (src & 0xFC000000U) >> 26;
    printf("opCode = %x", opCode);
    printf(" = %s\n", LB::InstLookUp::opCodeLookUp(opCode).c_str());
    return LB::InstData();
}

LB::InstData LB::InstDecode::decodeHexInst(const unsigned* src) {
    const unsigned argu = (src[0] << 16) | src[1];
    return LB::InstDecode::decodeHexInst(argu);
}
