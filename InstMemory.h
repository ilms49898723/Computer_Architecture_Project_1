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
#include "InstEnum.h"

namespace lb {

// 1024 bytes memory + 32 registers + pc
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
    void init(const unsigned& initPc = 0u);
    // get reg value at addr
    unsigned getRegValue(const unsigned& addr, const InstMemLen& type) const;
    // set reg value to addr
    void setRegValue(const unsigned& addr, const unsigned& val, const InstMemLen& type);
    // get memory value at addr, return as unsigned
    unsigned getMemValue(const unsigned& addr, const InstMemLen& type) const;
    // set memory value at addr, parameter all passed as unsigned
    void setMemValue(const unsigned& addr, const unsigned& val, const InstMemLen& type);
    // get pc
    unsigned getPc() const;
    // set pc
    void setPc(const unsigned& val);
    // get initializePc
    unsigned getInitPc() const;
    // set initializePc
    void setInitialPc(const unsigned& val);

private:
    unsigned char mem[1024];
    unsigned reg[32];
    unsigned pc;
    unsigned initialPc;
};

} /* namespace lb */

#endif /* INSTMEMORY_H_ */
