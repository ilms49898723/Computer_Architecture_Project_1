/*
 * InstDataBin.cpp
 *
 *  Created on: 2016/03/13
 *      Author: LittleBird
 */

#include "InstDataBin.h"

LB::InstDataBin::InstDataBin() {
    type = LB::InstType::Undef;
    opCode = rs = rt = rd = c = funct = 0U;
}

LB::InstDataBin::~InstDataBin() {
}

LB::InstType LB::InstDataBin::getType() const {
    return type;
}

unsigned LB::InstDataBin::getOpCode() const {
    return opCode;
}

unsigned LB::InstDataBin::getRs() const {
    return rs;
}

unsigned LB::InstDataBin::getRt() const {
    return rt;
}

unsigned LB::InstDataBin::getRd() const {
    return rd;
}

unsigned LB::InstDataBin::getC() const {
    return c;
}

unsigned LB::InstDataBin::getFunct() const {
    return funct;
}

void LB::InstDataBin::setType(const InstType& val) {
    type = val;
}

void LB::InstDataBin::setOpCode(const unsigned& val) {
    opCode = val;
}

void LB::InstDataBin::setRs(const unsigned& val) {
    rs = val;
}

void LB::InstDataBin::setRt(const unsigned& val) {
    rt = val;
}

void LB::InstDataBin::setRd(const unsigned& val) {
    rd = val;
}

void LB::InstDataBin::setC(const unsigned& val) {
    c = val;
}

void LB::InstDataBin::setFunct(const unsigned& val) {
    funct = val;
}
