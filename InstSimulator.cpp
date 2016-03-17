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

void LB::InstSimulator::init() {
    instSet.clear();
    mem.init();
}

void LB::InstSimulator::loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc) {
    mem.setPc(pc);
    for (unsigned i = 0; i < len; ++i) {
        instSet.push_back(LB::InstDecode::decodeInstBin(src[i]));
    }
}

void LB::InstSimulator::loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp) {
    // sp -> $29 == $(0x1D)
    mem.setValueOfAddr(0x1DU, sp, LB::InstMemLength::WORD);
    for (unsigned i = 0; i < len; ++i) {
        mem.setValueOfAddr(i, src[i], LB::InstMemLength::WORD);
    }
}

void LB::InstSimulator::simulate(FILE* snapshot, FILE* errorDump) {
    int currentInstIdx = 0;
    int cycle = 0;
    while (instSet[currentInstIdx].getOpCode() != 0x3FU) {
        InstDataBin& current = instSet[currentInstIdx];
        if (current.getType() == LB::InstType::R) {
            simulateTypeR(current, errorDump);
        }
        else if (current.getType() == LB::InstType::I) {
            simulateTypeI(current, errorDump);
        }
        else if (current.getType() == LB::InstType::J) {
            simulateTypeJ(current, errorDump);
        }
        ++cycle;
        dumpMemInfoPrivate(cycle, snapshot);
    }
}

void LB::InstSimulator::dumpMemInfoPrivate(const int& cycle, FILE* snapshot) {
    fprintf(snapshot, "cycle %d\n", cycle);
    for (int i = 0; i < 32; ++i) {
        fprintf(snapshot, "%02d: %#08X\n", i, mem.getValueOfAddr(i, LB::InstMemLength::WORD));
    }
    fprintf(snapshot, "\n\n");
}

void LB::InstSimulator::simulateTypeR(const InstDataBin& inst, FILE* errorDump) {
    switch (inst.getFunct()) {
        case 0x20U: {
            // add, rd = rs + rt, has of
            int rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs + rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x21U: {
            // addu, rd = rs + rt
            unsigned rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs + rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x22U: {
            // sub, rd = rs - rt
            int rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs - rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x24U: {
            // and, rd = rs & rt
            unsigned rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs & rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x25U: {
            // or, rd = rs | rt
            unsigned rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs | rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x26U: {
            // xor, rd = rs ^ rt
            unsigned rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs ^ rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x27U: {
            // nor, rd = ~(rs | rt)
            unsigned rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = ~(rs | rt);
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x28U: {
            // nand, rd = ~(rs & rt)
            unsigned rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = ~(rs & rt);
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x2AU: {
            // slt, rd = (rs < rt)
            int rs, rt, rd;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs < rt;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x00U: {
            // sll, rd = rt << c
            unsigned rd, rt, c;
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            c = mem.getValueOfAddr(inst.getC(), LB::InstMemLength::WORD);
            rd = rt << c;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x02U: {
            // srl, rd = rt >> c
            unsigned rd, rt, c;
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            c = mem.getValueOfAddr(inst.getC(), LB::InstMemLength::WORD);
            rd = rt >> c;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x03U: {
            // sra, rd = rt >> c(with sign bit)
            int rd, rt, c;
            rt = mem.getValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            c = mem.getValueOfAddr(inst.getC(), LB::InstMemLength::WORD);
            rd = rt << c;
            mem.setValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x08U: {
            // jr, pc = rs
            unsigned rs;
            rs = mem.getValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            mem.setPc(rs);
            break;
        }
        default: {
            // nop
            break;
        }
    }
}

void LB::InstSimulator::simulateTypeI(const InstDataBin& inst, FILE* errorDump) {
}

void LB::InstSimulator::simulateTypeJ(const InstDataBin& inst, FILE* errorDump) {
}
