/*
 * InstData.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstData.h"

InstData::InstData() {
    type = InstType::Undef;
    opCode = rs = rt = rd = c = funct = std::string();
}

InstData::~InstData() {
}

InstType InstData::getAll(std::string* dst) {
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

std::string InstData::getOpCode() {
    return opCode;
}

std::string InstData::getRs() {
    if (type == InstType::J || type == InstType::S) {
        return std::string();
    }
    return rs;
}

std::string InstData::getRt() {
    if (type == InstType::J || type == InstType::S) {
        return std::string();
    }
    return rt;
}

std::string InstData::getRd() {
    if (type != InstType::R) {
        return std::string();
    }
    return rd;
}

std::string InstData::getC() {
    return c;
}

std::string InstData::getFunct() {
    if (type != InstType::R) {
        return std::string();
    }
    return funct;
}

void InstData::setType(const InstType& val) {
    type = val;
}

void InstData::setOpCode(const std::string& val) {
    opCode = val;
}

void InstData::setRs(const std::string& val) {
    rs = val;
}

void InstData::setRt(const std::string& val) {
    rt = val;
}

void InstData::setRd(const std::string& val) {
    rd = val;
}

void InstData::setC(const std::string& val) {
    c = val;
}

void InstData::setFunct(const std::string& val) {
    funct = val;
}
