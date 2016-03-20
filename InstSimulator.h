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
    InstMemory memory;
    std::vector<InstDataBin> instSet;
    void dumpMemoryInfoPrivate(const int& cycle, FILE* snapshot);
    void simulateTypeR(const InstDataBin& inst, FILE* errorDump);
    void simulateTypeI(const InstDataBin& inst, FILE* errorDump);
    void simulateTypeJ(const InstDataBin& inst, FILE* errorDump);
};

} /* namespace LB */

#endif /* INSTSIMULATOR_H_ */
