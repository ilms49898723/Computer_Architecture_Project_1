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
    mem.setRegValueOfAddr(0x1DU, sp, LB::InstMemLength::WORD);
    for (unsigned i = 0; i < len; ++i) {
        mem.setRegValueOfAddr(i, src[i], LB::InstMemLength::WORD);
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
        dumpMemoryInfoPrivate(cycle, snapshot);
    }
}

void LB::InstSimulator::dumpMemoryInfoPrivate(const int& cycle, FILE* snapshot) {
    fprintf(snapshot, "cycle %d\n", cycle);
    for (int i = 0; i < 32; ++i) {
        fprintf(snapshot, "%02d: %#08X\n", i, mem.getRegValueOfAddr(i, LB::InstMemLength::WORD));
    }
    fprintf(snapshot, "\n\n");
}

void LB::InstSimulator::simulateTypeR(const InstDataBin& inst, FILE* errorDump) {
    switch (inst.getFunct()) {
        case 0x20U: {
            // add, rd = rs + rt, has of
            int rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs + rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x21U: {
            // addu, rd = rs + rt
            unsigned rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs + rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x22U: {
            // sub, rd = rs - rt
            int rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs - rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x24U: {
            // and, rd = rs & rt
            unsigned rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs & rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x25U: {
            // or, rd = rs | rt
            unsigned rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs | rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x26U: {
            // xor, rd = rs ^ rt
            unsigned rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs ^ rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x27U: {
            // nor, rd = ~(rs | rt)
            unsigned rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = ~(rs | rt);
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x28U: {
            // nand, rd = ~(rs & rt)
            unsigned rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = ~(rs & rt);
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x2AU: {
            // slt, rd = (rs < rt)
            int rs, rt, rd;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            rd = rs < rt;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x00U: {
            // sll, rd = rt << c
            unsigned rd, rt, c;
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            c = mem.getRegValueOfAddr(inst.getC(), LB::InstMemLength::WORD);
            rd = rt << c;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x02U: {
            // srl, rd = rt >> c
            unsigned rd, rt, c;
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            c = mem.getRegValueOfAddr(inst.getC(), LB::InstMemLength::WORD);
            rd = rt >> c;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x03U: {
            // sra, rd = rt >> c(with sign bit)
            int rd, rt, c;
            rt = mem.getRegValueOfAddr(inst.getRt(), LB::InstMemLength::WORD);
            c = mem.getRegValueOfAddr(inst.getC(), LB::InstMemLength::WORD);
            rd = rt << c;
            mem.setRegValueOfAddr(inst.getRd(), rd, LB::InstMemLength::WORD);
            break;
        }
        case 0x08U: {
            // jr, pc = rs
            unsigned rs;
            rs = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD);
            mem.setPc(rs);
            break;
        }
        default: {
            // nop
            break;
        }
    }
    mem.setPc(mem.getPc() + 4);
}

void LB::InstSimulator::simulateTypeI(const InstDataBin& inst, FILE* errorDump) {
    switch(inst.getOpCode()) {
        case 0x08U: {
            // addi
            // TODO: overflow detect not completed!!!
            unsigned rt;
            rt = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD) + inst.getC();
            mem.setRegValueOfAddr(inst.getRt(), rt, LB::InstMemLength::WORD);
            break;
        }
        case 0x09U: {
            // addiu
            unsigned rt;
            rt = mem.getRegValueOfAddr(inst.getRs(), LB::InstMemLength::WORD) + inst.getC();
            mem.setRegValueOfAddr(inst.getRt(), rt, LB::InstMemLength::WORD);
            break;
        }
        case 0x23U: {
            // lw
            unsigned rt;
            rt = mem.getRegValueOfAddr(inst.getRs() + inst.getC(),LB::InstMemLength::WORD);
            mem.setRegValueOfAddr(inst.getRt(), rt, LB::InstMemLength::WORD);
            break;
        }
        case 0x21U: {
            // lh
            // FIXME: MEMORY MAY HAVE BUGS!!!
            unsigned rt;
            rt = mem.getRegValueOfAddr(inst.getRs() + inst.getC(),LB::InstMemLength::HALFWORD);
            mem.setRegValueOfAddr(inst.getRt(), rt, LB::InstMemLength::WORD);
            break;
        }
        case 0x25U: {
            // lhu
            // FIXME: MEMORY MAY HAVE BUGS!!!
            unsigned rt;
            rt = mem.getRegValueOfAddr(inst.getRs() + inst.getC(),LB::InstMemLength::HALFWORD);
            mem.setRegValueOfAddr(inst.getRt(), rt, LB::InstMemLength::WORD);
            break;
        }
        case 0x20U: {
            break;
        }
    }
}

void LB::InstSimulator::simulateTypeJ(const InstDataBin& inst, FILE* errorDump) {
}
