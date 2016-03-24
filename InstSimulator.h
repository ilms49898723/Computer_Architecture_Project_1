/*
 * InstSimulator.h
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#ifndef INSTSIMULATOR_H_
#define INSTSIMULATOR_H_

#include <cstdio>
#include <cstdlib>
#include <vector>
#include "InstDecode.h"
#include "InstMemory.h"
#include "InstDataStr.h"
#include "InstErrorDetector.h"

namespace LB {

class InstSimulator {
public:
    InstSimulator();
    virtual ~InstSimulator();
    void init();
    void loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc);
    void loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp);
    void simulate(FILE* snapshot, FILE* errorDump);

private:
    bool isAlive;
    int cycle;
    FILE* snapshot;
    FILE* errorDump;
    InstMemory memory;
    std::vector<InstDataBin> instSet;
    void dumpMemoryInfoPrivate(const int& cycle);
    void simulateTypeR(const InstDataBin& inst);
    void simulateTypeI(const InstDataBin& inst);
    void simulateTypeJ(const InstDataBin& inst);
    void checkInst(const InstDataBin& inst);
    InstAction detectRegWriteZero(const unsigned& addr);
    InstAction detectNumberOverflow(const int& a, const int& b, const InstOpType& op);
    InstAction detectMemAddrOverflow(const unsigned& addr);
    InstAction detectDataMisaligned(const unsigned& addr, const InstMemLen& type);
};

} /* namespace LB */

#endif /* INSTSIMULATOR_H_ */
