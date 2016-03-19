/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.h"

LB::InstMemory::InstMemory() {
    initalizePc = pc = 0U;
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
}

LB::InstMemory::InstMemory(const unsigned& initPc) {
    initalizePc = pc = initPc;
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
}

LB::InstMemory::~InstMemory() {
}

void LB::InstMemory::init(const unsigned& initPc) {
    pc = initPc;
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
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

unsigned LB::InstMemory::getRegValueOfAddr(const unsigned& addr, const LB::InstMemLength& type) {
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

void LB::InstMemory::setRegValueOfAddr(const unsigned& addr, const unsigned& val, const LB::InstMemLength& type) {
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

unsigned LB::InstMemory::getMemValueOfAddr(const unsigned& addr, const InstMemLength& type) {
    if (type == LB::InstMemLength::WORD) {
        return (mem[addr] << 24) | (mem[addr + 1] << 16) | (mem[addr + 2] << 8) | mem[addr + 3];
    }
    else if (type == LB::InstMemLength::HALFWORD) {
        return (mem[addr] << 8) | (mem[addr + 1]);
    }
    else {
        return mem[addr];
    }
}

void LB::InstMemory::setMemValueOfAddr(const unsigned& addr, const unsigned& val, const InstMemLength& type) {
    if (type == LB::InstMemLength::WORD) {
        mem[addr] = static_cast<unsigned char>((val >> 24) & 0xFFU);
        mem[addr + 1] = static_cast<unsigned char>((val >> 16) & 0xFFU);
        mem[addr + 2] = static_cast<unsigned char>((val >> 8) & 0xFFU);
        mem[addr + 3] = static_cast<unsigned char>(val & 0xFFU);
    }
    else if (type == LB::InstMemLength::HALFWORD) {
        mem[addr] = static_cast<unsigned char>((val >> 8) & 0xFFU);
        mem[addr + 1] = static_cast<unsigned char>(val & 0xFFU);
    }
    else {
        mem[addr] = static_cast<unsigned char>(val & 0xFFU);
    }
}

unsigned LB::InstMemory::getPc() {
    return pc;
}

void LB::InstMemory::setPc(const unsigned& val) {
    pc = val;
}

unsigned LB::InstMemory::getInitPc() {
    return initalizePc;
}
