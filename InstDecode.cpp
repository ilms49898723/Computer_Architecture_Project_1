/*
 * InstDecode.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstDecode.h"

LB::InstData LB::InstDecode::decodeHexInst(const unsigned& src) {
    unsigned opCode;
    unsigned rs, rt, rd;
    unsigned c;
    unsigned funct;
    std::string opCodeStr;
    std::string rsStr, rtStr, rdStr;
    std::string cStr;
    std::string functStr;
    opCode = LB::InstDecode::getBitsInRange(src, 26, 32);
    opCodeStr = LB::InstLookUp::opCodeLookUp(opCode);
    if (opCodeStr == "undef") {
        return LB::InstData();
    }
    else if (opCode == 0x0U) {
        funct = LB::InstDecode::getBitsInRange(src, 0, 6);
        rs = LB::InstDecode::getBitsInRange(src, 21, 26);
        rt = LB::InstDecode::getBitsInRange(src, 16, 21);
        rd = LB::InstDecode::getBitsInRange(src, 11, 16);
        c = LB::InstDecode::getBitsInRange(src, 6, 11);
        rsStr = LB::InstLookUp::registerLookUp(rs);
        rtStr = LB::InstLookUp::registerLookUp(rt);
        rdStr = LB::InstLookUp::registerLookUp(rd);
        cStr = LB::toHexString(c);
        functStr = LB::InstLookUp::functLookUp(funct);
        InstData ret;
        ret.setType(LB::InstType::R);
        ret.setOpCode(opCodeStr);
        ret.setRs(rsStr);
        ret.setRt(rtStr);
        ret.setRd(rdStr);
        ret.setC(cStr);
        ret.setFunct(functStr);
        return ret;
    }
    else if (opCode == 0x02U || opCode == 0x03U) {
        c = LB::InstDecode::getBitsInRange(src, 0, 26);
        cStr = LB::toHexString(c);
        InstData ret;
        ret.setType(LB::InstType::J);
        ret.setOpCode(opCodeStr);
        ret.setC(cStr);
        return ret;
    }
    else if (opCode == 0x3FU) {
        opCodeStr = LB::InstLookUp::opCodeLookUp(opCode);
        InstData ret;
        ret.setType(LB::InstType::S);
        ret.setOpCode(opCodeStr);
        return ret;
    }
    else {
        rs = LB::InstDecode::getBitsInRange(src, 21, 26);
        rt = LB::InstDecode::getBitsInRange(src, 16, 21);
        c = LB::InstDecode::getBitsInRange(src, 0, 16);
        rsStr = LB::InstLookUp::registerLookUp(rs);
        rtStr = LB::InstLookUp::registerLookUp(rt);
        cStr = LB::toHexString(c);
        InstData ret;
        ret.setType(LB::InstType::I);
        ret.setOpCode(opCodeStr);
        ret.setRs(rsStr);
        ret.setRt(rtStr);
        ret.setC(cStr);
        return ret;
    }
}

LB::InstData LB::InstDecode::decodeHexInst(const unsigned* src) {
    const unsigned argu = (src[0] << 16) | src[1];
    return LB::InstDecode::decodeHexInst(argu);
}

unsigned LB::InstDecode::getBitsInRange(const unsigned& src, const int& l, const int& r) {
    unsigned mask = 0;
    for (int i = l; i < r; ++i) {
        mask |= (1 << i);
    }
    return (src & mask) >> l;
}
