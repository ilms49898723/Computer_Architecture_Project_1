/*
 * InstDecode.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstDecode.h"

LB::InstDataStr LB::InstDecode::decodeInstStr(const unsigned& src) {
    unsigned opCode;
    unsigned rs, rt, rd;
    unsigned c;
    unsigned funct;
    std::string opCodeStr;
    std::string rsStr, rtStr, rdStr;
    std::string cStr;
    std::string functStr;
    opCode = LB::getBitsInRange(src, 26, 32);
    opCodeStr = LB::InstLookUp::opCodeLookUp(opCode);
    if (opCodeStr == "undef") {
        return LB::InstDataStr();
    }
    else if (opCode == 0x0U) {
        funct = LB::getBitsInRange(src, 0, 6);
        rs = LB::getBitsInRange(src, 21, 26);
        rt = LB::getBitsInRange(src, 16, 21);
        rd = LB::getBitsInRange(src, 11, 16);
        c = LB::getBitsInRange(src, 6, 11);
        rsStr = LB::InstLookUp::registerLookUpNumber(rs);
        rtStr = LB::InstLookUp::registerLookUpNumber(rt);
        rdStr = LB::InstLookUp::registerLookUpNumber(rd);
        cStr = LB::toHexString(c);
        functStr = LB::InstLookUp::functLookUp(funct);
        InstDataStr ret;
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
        c = LB::getBitsInRange(src, 0, 26);
        cStr = LB::toHexString(c);
        InstDataStr ret;
        ret.setType(LB::InstType::J);
        ret.setOpCode(opCodeStr);
        ret.setC(cStr);
        return ret;
    }
    else if (opCode == 0x3FU) {
        opCodeStr = LB::InstLookUp::opCodeLookUp(opCode);
        InstDataStr ret;
        ret.setType(LB::InstType::S);
        ret.setOpCode(opCodeStr);
        return ret;
    }
    else {
        rs = LB::getBitsInRange(src, 21, 26);
        rt = LB::getBitsInRange(src, 16, 21);
        c = LB::getBitsInRange(src, 0, 16);
        rsStr = LB::InstLookUp::registerLookUpNumber(rs);
        rtStr = LB::InstLookUp::registerLookUpNumber(rt);
        cStr = LB::toHexString(c);
        InstDataStr ret;
        ret.setType(LB::InstType::I);
        ret.setOpCode(opCodeStr);
        ret.setRs(rsStr);
        ret.setRt(rtStr);
        ret.setC(cStr);
        return ret;
    }
}

LB::InstDataStr LB::InstDecode::decodeInstStr(const unsigned* src) {
    const unsigned argu = (src[0] << 16) | src[1];
    return LB::InstDecode::decodeInstStr(argu);
}

LB::InstDataBin LB::InstDecode::decodeInstBin(const unsigned & src) {
    unsigned opCode;
    unsigned rs, rt, rd;
    unsigned c;
    unsigned funct;
    std::string opCodeStr;
    opCode = LB::getBitsInRange(src, 26, 32);
    opCodeStr = LB::InstLookUp::opCodeLookUp(opCode);
    if (opCodeStr == "undef") {
        return LB::InstDataBin();
    }
    else if (opCode == 0x0U) {
        funct = LB::getBitsInRange(src, 0, 6);
        rs = LB::getBitsInRange(src, 21, 26);
        rt = LB::getBitsInRange(src, 16, 21);
        rd = LB::getBitsInRange(src, 11, 16);
        c = LB::getBitsInRange(src, 6, 11);
        InstDataBin ret;
        ret.setType(LB::InstType::R);
        ret.setOpCode(opCode);
        ret.setRs(rs);
        ret.setRt(rt);
        ret.setRd(rd);
        ret.setC(c);
        ret.setFunct(funct);
        return ret;
    }
    else if (opCode == 0x02U || opCode == 0x03U) {
        c = LB::getBitsInRange(src, 0, 26);
        InstDataBin ret;
        ret.setType(LB::InstType::J);
        ret.setOpCode(opCode);
        ret.setC(c);
        return ret;
    }
    else if (opCode == 0x3FU) {
        opCodeStr = LB::InstLookUp::opCodeLookUp(opCode);
        InstDataBin ret;
        ret.setType(LB::InstType::S);
        ret.setOpCode(opCode);
        return ret;
    }
    else {
        rs = LB::getBitsInRange(src, 21, 26);
        rt = LB::getBitsInRange(src, 16, 21);
        c = LB::getBitsInRange(src, 0, 16);
        InstDataBin ret;
        ret.setType(LB::InstType::I);
        ret.setOpCode(opCode);
        ret.setRs(rs);
        ret.setRt(rt);
        ret.setC(c);
        return ret;
    }
}

LB::InstDataBin LB::InstDecode::decodeInstBin(const unsigned* src) {
    const unsigned argu = (src[0] << 16) | src[1];
    return LB::InstDecode::decodeInstBin(argu);
}
