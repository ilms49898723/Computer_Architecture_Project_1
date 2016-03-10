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

namespace LB {

enum class InstMemLength {
    WORD, HALFWORD, BYTE
};

// 32 registers + pc
class InstMemory {
public:
    InstMemory();
    InstMemory(const unsigned& initPc);
    virtual ~InstMemory();
    // initialize with pc(default = 0)
    void init(const unsigned& initPc = 0U);
    //check whether the address is valid (or misaligned)
    bool isValidAddress(const unsigned& opCode, const unsigned& c);
    bool isValidAddress(const std::string& opCode, const unsigned& c);
    // get reg value at addr
    unsigned getValueOfAddr(const unsigned& addr, const InstMemLength& type);
    // get pc
    unsigned getPc();
    // save reg value to addr
    void setValueOfAddr(const unsigned& addr, const unsigned& val, const InstMemLength& type);
    // set pc
    void setPc(const unsigned& val);

private:
    unsigned reg[32];
    unsigned pc;
};

} /* namespace LB */

#endif /* INSTMEMORY_H_ */
