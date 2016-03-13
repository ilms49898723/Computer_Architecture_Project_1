/*
 * InstSimulator.h
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#ifndef INSTSIMULATOR_H_
#define INSTSIMULATOR_H_

#include "InstDecode.h"
#include "InstMemory.h"
#include <vector>
#include "InstDataStr.h"

namespace LB {

class InstSimulator {
public:
    InstSimulator();
    virtual ~InstSimulator();
    void loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc);
    void loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp);

private:
    InstMemory mem;
    std::vector<InstDataStr> instSet;
};

} /* namespace LB */

#endif /* INSTSIMULATOR_H_ */
