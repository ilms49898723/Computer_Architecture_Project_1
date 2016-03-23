/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.h"

namespace LB {

bool InstMemory::isValidAddress(const unsigned& opCode, const unsigned& addr) {
    if (opCode == 0x23U || opCode == 0x2B) {
        return (addr % 4) == 0;
    }
    else if (opCode == 0x21U || opCode == 0x25U || opCode == 0x29U) {
        return (addr & 1) == 0;
    }
    else {
        return true;
    }
}

bool InstMemory::isValidAddress(const std::string& opCode, const unsigned& addr) {
    if (opCode == "lw" || opCode == "sw") {
        return (addr % 4) == 0;
    }
    else if (opCode == "lh" || opCode == "lhu" || opCode == "sh") {
        return (addr & 1) == 0;
    }
    else {
        return true;
    }
}

InstMemory::InstMemory() {
    initalizePc = pc = 0U;
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
}

InstMemory::InstMemory(const unsigned& initPc) {
    initalizePc = pc = initPc;
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
}

InstMemory::~InstMemory() {
}

void InstMemory::init(const unsigned& initPc) {
    pc = initPc;
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
}

unsigned InstMemory::getRegValueOfAddr(const unsigned& addr, const InstMemLen& type) {
    if (type == InstMemLen::WORD) {
        return reg[addr];
    }
    else if (type == InstMemLen::HALFWORD) {
        return reg[addr] & 0x0000FFFFU;
    }
    else {
        return reg[addr] & 0x000000FFU;
    }
}

void InstMemory::setRegValueOfAddr(const unsigned& addr, const unsigned& val, const InstMemLen& type) {
    if (type == InstMemLen::WORD) {
        reg[addr] = val;
    }
    else if (type == InstMemLen::HALFWORD) {
        reg[addr] = val & 0x0000FFFFU;
    }
    else {
        reg[addr] = val & 0x000000FFU;
    }
}

unsigned InstMemory::getMemValueOfAddr(const unsigned& addr, const InstMemLen& type) {
    if (type == InstMemLen::WORD) {
        return (mem[addr] << 24) | (mem[addr + 1] << 16) | (mem[addr + 2] << 8) | mem[addr + 3];
    }
    else if (type == InstMemLen::HALFWORD) {
        return (mem[addr] << 8) | (mem[addr + 1]);
    }
    else {
        return mem[addr];
    }
}

void InstMemory::setMemValueOfAddr(const unsigned& addr, const unsigned& val, const InstMemLen& type) {
    if (type == InstMemLen::WORD) {
        mem[addr] = static_cast<unsigned char>((val >> 24) & 0xFFU);
        mem[addr + 1] = static_cast<unsigned char>((val >> 16) & 0xFFU);
        mem[addr + 2] = static_cast<unsigned char>((val >> 8) & 0xFFU);
        mem[addr + 3] = static_cast<unsigned char>(val & 0xFFU);
    }
    else if (type == InstMemLen::HALFWORD) {
        mem[addr] = static_cast<unsigned char>((val >> 8) & 0xFFU);
        mem[addr + 1] = static_cast<unsigned char>(val & 0xFFU);
    }
    else {
        mem[addr] = static_cast<unsigned char>(val & 0xFFU);
    }
}

unsigned InstMemory::getPc() {
    return pc;
}

void InstMemory::setPc(const unsigned& val) {
    pc = val;
}

unsigned InstMemory::getInitPc() {
    return initalizePc;
}

void InstMemory::setInitlizePc(const unsigned& val) {
    initalizePc = val;
}

} /* namespace LB */
