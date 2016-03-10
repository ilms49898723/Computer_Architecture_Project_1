/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.h"

LB::InstMemory::InstMemory() {
    pc = 0U;
    memset(reg, 0, sizeof(unsigned) * 32);
}

LB::InstMemory::InstMemory(const unsigned& initPc) {
    pc = initPc;
    memset(reg, 0, sizeof(unsigned) * 32);
}

LB::InstMemory::~InstMemory() {
}

void LB::InstMemory::init(const unsigned & initPc) {
    pc = initPc;
    memset(reg, 0, sizeof(unsigned) * 32);
}

bool LB::InstMemory::isValidAddress(const unsigned& opCode, const unsigned& c) {
    if (opCode == 0x23U || opCode == 0x2B) {
        return (c % 4) == 0;
    }
    else if (opCode == 0x21U || opCode == 0x25U || opCode == 0x29U) {
        return (c & 1) == 0;
    }
    else {
        return true;
    }
}

bool LB::InstMemory::isValidAddress(const std::string& opCode, const unsigned& c) {
    if (opCode == "lw" || opCode == "sw") {
        return (c % 4) == 0;
    }
    else if (opCode == "lh" || opCode == "lhu" || opCode == "sh") {
        return (c & 1) == 0;
    }
    else {
        return true;
    }
}

unsigned LB::InstMemory::getValueOfAddr(const unsigned& addr, const LB::InstMemLength& type) {
    if (type == LB::InstMemLength::WORD) {
        return reg[addr];
    }
    else if (type == LB::InstMemLength::HALFWORD) {
        return reg[addr] & 0x0000FFFFU;
    }
    else {
        return reg[addr] & 0x000000FFU;
    }
}

unsigned LB::InstMemory::getPc() {
    return pc;
}

void LB::InstMemory::setValueOfAddr(const unsigned& addr, const unsigned& val, const LB::InstMemLength& type) {
    if (type == LB::InstMemLength::WORD) {
        reg[addr] = val;
    }
    else if (type == LB::InstMemLength::HALFWORD) {
        reg[addr] = val & 0x0000FFFFU;
    }
    else {
        reg[addr] = val & 0x000000FFU;
    }
}

void LB::InstMemory::setPc(const unsigned& val) {
    pc = val;
}
