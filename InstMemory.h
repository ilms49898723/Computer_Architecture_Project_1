/*
 * InstMemory.h
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#ifndef INSTMEMORY_H_
#define INSTMEMORY_H_

#include <cstring>
#include <string>
#include "InstUtility.h"

namespace LB {

// 1024 memory + 32 registers + pc
class InstMemory {
public:
    //check whether the address is valid (or misaligned)
    static bool isValidAddress(const unsigned& opCode, const unsigned& addr);
    static bool isValidAddress(const std::string& opCode, const unsigned& addr);

public:
    InstMemory();
    InstMemory(const unsigned& initPc);
    virtual ~InstMemory();
    // initialize with pc(default = 0)
    void init(const unsigned& initPc = 0U);
    // get reg value at addr
    unsigned getRegValueOfAddr(const unsigned& addr, const InstMemLen& type);
    // set reg value to addr
    void setRegValueOfAddr(const unsigned& addr, const unsigned& val, const InstMemLen& type);
    // get memory value at addr, return as unsigned
    unsigned getMemValueOfAddr(const unsigned& addr, const InstMemLen& type);
    // set memory value at addr, parameter all passed as unsigned
    void setMemValueOfAddr(const unsigned& addr, const unsigned& val, const InstMemLen& type);
    // get pc
    unsigned getPc();
    // set pc
    void setPc(const unsigned& val);
    // get initializePc
    unsigned getInitPc();
    // set initializePc
    void setInitlizePc(const unsigned& val);

private:
    unsigned char mem[1024];
    unsigned reg[32];
    unsigned pc;
    unsigned initalizePc;
};

} /* namespace LB */

#endif /* INSTMEMORY_H_ */
