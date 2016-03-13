/*
 * InstSimulator.cpp
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#include "InstSimulator.h"

LB::InstSimulator::InstSimulator() {
    instSet.clear();
    mem.init();
}

LB::InstSimulator::~InstSimulator() {
}

void LB::InstSimulator::loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc) {
    mem.setPc(pc);
    for (unsigned i = 0; i < len; ++i) {
        instSet.push_back(LB::InstDecode::decodeInst(src[i]));
    }
}

// sp -> $29 == $(0x1D)
void LB::InstSimulator::loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp) {
    mem.setValueOfAddr(0x1DU, sp, LB::InstMemLength::WORD);
    for (unsigned i = 0; i < len; ++i) {
        mem.setValueOfAddr(i, src[i], LB::InstMemLength::WORD);
    }
}
