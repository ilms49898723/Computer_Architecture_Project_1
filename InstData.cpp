/*
 * InstData.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstData.h"

LB::InstData::InstData() {
    type = InstType::Undef;
    opCode = rs = rt = rd = c = funct = std::string();
}

LB::InstData::~InstData() {
}

LB::InstType LB::InstData::getAll(std::string* dst) {
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

std::string LB::InstData::getOpCode() {
    return opCode;
}

std::string LB::InstData::getRs() {
    if (type == InstType::J || type == InstType::S) {
        return std::string();
    }
    return rs;
}

std::string LB::InstData::getRt() {
    if (type == InstType::J || type == InstType::S) {
        return std::string();
    }
    return rt;
}

std::string LB::InstData::getRd() {
    if (type != InstType::R) {
        return std::string();
    }
    return rd;
}

std::string LB::InstData::getC() {
    return c;
}

std::string LB::InstData::getFunct() {
    if (type != InstType::R) {
        return std::string();
    }
    return funct;
}

void LB::InstData::setType(const InstType& val) {
    type = val;
}

void LB::InstData::setOpCode(const std::string& val) {
    opCode = val;
}

void LB::InstData::setRs(const std::string& val) {
    rs = val;
}

void LB::InstData::setRt(const std::string& val) {
    rt = val;
}

void LB::InstData::setRd(const std::string& val) {
    rd = val;
}

void LB::InstData::setC(const std::string& val) {
    c = val;
}

void LB::InstData::setFunct(const std::string& val) {
    funct = val;
}

std::string LB::InstData::toString() {
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
