/*
 * InstData.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstDataStr.h"

LB::InstDataStr::InstDataStr() {
    type = InstType::Undef;
    opCode = rs = rt = rd = c = funct = std::string();
}

LB::InstDataStr::~InstDataStr() {
}

LB::InstType LB::InstDataStr::getAll(std::string* dst) {
    if (!dst) {
        return InstType::Undef;
    }
    if (type == InstType::R) {
        dst[0] = opCode;
        dst[1] = rs;
        dst[2] = rt;
        dst[3] = rd;
        dst[4] = c;
        dst[5] = funct;
    }
    else if (type == InstType::I) {
        dst[0] = opCode;
        dst[1] = rs;
        dst[2] = rt;
        dst[3] = c;
    }
    else if (type == InstType::J) {
        dst[0] = opCode;
        dst[1] = c;
    }
    else {
        dst[0] = opCode;
    }
    return type;
}

std::string LB::InstDataStr::getOpCode() {
    return opCode;
}

std::string LB::InstDataStr::getRs() {
    if (type == InstType::J || type == InstType::S) {
        return std::string();
    }
    return rs;
}

std::string LB::InstDataStr::getRt() {
    if (type == InstType::J || type == InstType::S) {
        return std::string();
    }
    return rt;
}

std::string LB::InstDataStr::getRd() {
    if (type != InstType::R) {
        return std::string();
    }
    return rd;
}

std::string LB::InstDataStr::getC() {
    return c;
}

std::string LB::InstDataStr::getFunct() {
    if (type != InstType::R) {
        return std::string();
    }
    return funct;
}

void LB::InstDataStr::setType(const InstType& val) {
    type = val;
}

void LB::InstDataStr::setOpCode(const std::string& val) {
    opCode = val;
}

void LB::InstDataStr::setRs(const std::string& val) {
    rs = val;
}

void LB::InstDataStr::setRt(const std::string& val) {
    rt = val;
}

void LB::InstDataStr::setRd(const std::string& val) {
    rd = val;
}

void LB::InstDataStr::setC(const std::string& val) {
    c = val;
}

void LB::InstDataStr::setFunct(const std::string& val) {
    funct = val;
}

std::string LB::InstDataStr::toString() {
    if (type == InstType::R) {
        if (funct == "jr") {
            return funct + " $" + rs;
        }
        else if (funct == "sll" || funct == "srl" || funct == "sra") {
            return funct + " $" + rd + ", $" + rt + ", " + c;
        }
        else {
            return funct + " $" + rd + ", $" + rs + ", $" + rt;
        }
    }
    else if (type == InstType::I) {
        if (opCode == "lui") {
            return opCode + " $" + rt + ", " + c;
        }
        else if (opCode == "bgtz") {
            return opCode + " $" + rs + ", " + c;
        }
        else if (opCode == "addi" || opCode == "addiu" || opCode == "lui" ||
                opCode == "andi" || opCode == "ori" || opCode == "nori" ||
                opCode == "slti") {
            return opCode + " $" + rt + ", $" + rs + ", " + c;
        }
        else if (opCode == "beq" || opCode == "bne") {
            return opCode + " $" + rs + ", $" + rt + ", " + c;
        }
        else {
            return opCode + " $" + rt + ", " + c + "($" + rs + ")";
        }
    }
    else if (type == InstType::J) {
        return opCode + " " + c;
    }
    else if (type == InstType::S) {
        return opCode;
    }
    else {
        return "undef";
    }
}
