/*
 * InstSimulator.cpp
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#include "InstSimulator.h"

namespace LB {

InstSimulator::InstSimulator() {
    instSet.clear();
    memory.init();
}

InstSimulator::~InstSimulator() {
}

void InstSimulator::init() {
    instSet.clear();
    memory.init();
}

void InstSimulator::loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc) {
    memory.setPc(pc);
    memory.setInitlizePc(pc);
    for (unsigned i = 0; i < len; ++i) {
        instSet.push_back(InstDecode::decodeInstBin(src[i]));
    }
}

void InstSimulator::loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp) {
    // sp -> $29
    memory.setRegValueOfAddr(29, sp, InstMemLen::WORD);
    for (unsigned i = 0; i < len; ++i) {
        memory.setMemValueOfAddr(i * 4, src[i], InstMemLen::WORD);
    }
}

void InstSimulator::simulate(FILE* snapshot, FILE* errorDump) {
    int currentInstIdx = (memory.getPc() - memory.getInitPc()) >> 2;
    int cycle = 0;
    {
        // initial state dump
        dumpMemoryInfoPrivate(cycle, snapshot);
        ++cycle;
    }
    while (instSet[currentInstIdx].getOpCode() != 0x3FU) {
        InstDataBin& current = instSet[currentInstIdx];
        if (current.getType() == InstType::R) {
            simulateTypeR(current, errorDump);
        }
        else if (current.getType() == InstType::I) {
            simulateTypeI(current, errorDump);
        }
        else if (current.getType() == InstType::J) {
            simulateTypeJ(current, errorDump);
        }
        dumpMemoryInfoPrivate(cycle, snapshot);
        currentInstIdx = (memory.getPc() - memory.getInitPc()) >> 2;
        ++cycle;
    }
}

void InstSimulator::dumpMemoryInfoPrivate(const int& cycle, FILE* snapshot) {
    fprintf(snapshot, "cycle %d\n", cycle);
    for (int i = 0; i < 32; ++i) {
        fprintf(snapshot, "$%02d: 0x%08X\n", i, memory.getRegValueOfAddr(i, InstMemLen::WORD));
    }
    fprintf(snapshot, "PC: 0x%08X\n", memory.getPc());
    fprintf(snapshot, "\n\n");
}

void InstSimulator::simulateTypeR(const InstDataBin& inst, FILE* errorDump) {
    switch (inst.getFunct()) {
        case 0x20U: {
            // add, rd = rs + rt
            int rs, rt;
            unsigned rd;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            rt = toSigned(memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD));
            rd = toUnsigned(rs + rt);
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x21U: {
            // addu, rd = rs + rt
            unsigned rs, rt, rd;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            rd = rs + rt;
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x22U: {
            // sub, rd = rs - rt
            int rs, rt;
            unsigned rd;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            rt = toSigned(memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD));
            rd = toUnsigned(rs - rt);
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x24U: {
            // and, rd = rs & rt
            unsigned rs, rt, rd;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            rd = rs & rt;
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x25U: {
            // or, rd = rs | rt
            unsigned rs, rt, rd;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            rd = rs | rt;
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x26U: {
            // xor, rd = rs ^ rt
            unsigned rs, rt, rd;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            rd = rs ^ rt;
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x27U: {
            // nor, rd = ~(rs | rt)
            unsigned rs, rt, rd;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            rd = ~(rs | rt);
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x28U: {
            // nand, rd = ~(rs & rt)
            unsigned rs, rt, rd;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            rd = ~(rs & rt);
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x2AU: {
            // slt, rd = (rs < rt)
            int rs, rt;
            unsigned rd;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            rt = toSigned(memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD));
            rd = toUnsigned(rs < rt);
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x00U: {
            // sll, rd = rt << c
            unsigned rd, rt, c;
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            c = inst.getC();
            rd = rt << c;
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x02U: {
            // srl, rd = rt >> c
            unsigned rd, rt, c;
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            c = inst.getC();
            rd = rt >> c;
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x03U: {
            // sra, rd = rt >> c(with sign bit)
            int rt, c;
            unsigned rd;
            rt = toSigned(memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD));
            c = toSigned(inst.getC());
            rd = toUnsigned(rt >> c);
            memory.setRegValueOfAddr(inst.getRd(), rd, InstMemLen::WORD);
            break;
        }
        case 0x08U: {
            // jr, pc = rs
            unsigned rs;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            memory.setPc(rs);
            // new pc has already been set, return, not break
            return;
        }
        default: {
            // undefined operation
            break;
        }
    }
    memory.setPc(memory.getPc() + 4);
}

void InstSimulator::simulateTypeI(const InstDataBin& inst, FILE* errorDump) {
    switch(inst.getOpCode()) {
        case 0x08U: {
            // addi, rt = rs + c
            int rs, c;
            unsigned rt;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            rt = toUnsigned(rs + c);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x09U: {
            // addiu, rt = rs + c(unsigned)
            unsigned rt, rs, c;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            c = toSigned(inst.getC(), 16);
            rt = rs + c;
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x23U: {
            // lw, rt = mem[rs + c], 4 bytes
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getMemValueOfAddr(addr, InstMemLen::WORD);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x21U: {
            // lh, rt = mem[rs + c], 2 bytes, signed
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getMemValueOfAddr(addr, InstMemLen::HALFWORD);
            rt = toSigned(rt, InstMemLen::HALFWORD);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x25U: {
            // lhu, rt = mem[rs + c], 2 bytes, unsigned
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getMemValueOfAddr(addr, InstMemLen::HALFWORD);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x20U: {
            // lb, rt = mem[rs + c], 1 byte, signed
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getMemValueOfAddr(addr, InstMemLen::BYTE);
            rt = toSigned(rt, InstMemLen::BYTE);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x24U: {
            // lbu, rt = mem[rs + c], 1 byte, unsigned
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getMemValueOfAddr(addr, InstMemLen::BYTE);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x2BU: {
            // sw, mem[rs + c] = rt, 4 bytes
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            memory.setMemValueOfAddr(addr, rt, InstMemLen::WORD);
            break;
        }
        case 0x29U: {
            // sh, mem[rs + c] = rt, 2 bytes
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            memory.setMemValueOfAddr(addr, rt, InstMemLen::HALFWORD);
            break;
        }
        case 0x28U: {
            // sb
            int rs, c;
            unsigned rt;
            unsigned addr;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            addr = toUnsigned(rs + c);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            memory.setMemValueOfAddr(addr, rt, InstMemLen::BYTE);
            break;
        }
        case 0x0FU: {
            // lui, rt = c << 16
            unsigned rt;
            rt = inst.getC() << 16;
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x0CU: {
            // andi, rt = rs & c
            unsigned rt, rs, c;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            c = inst.getC();
            rt = rs & c;
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x0DU: {
            // ori, rt = rs | c
            unsigned rt, rs, c;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            c = inst.getC();
            rt = rs | c;
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x0EU: {
            // nori, rt = ~(rs | c)
            unsigned rt, rs, c;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            c = inst.getC();
            rt = ~(rs | c);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x0AU: {
            // slti, rt = (rs < c(signed))
            int rs, c;
            unsigned rt;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            rt = toUnsigned(rs < c);
            memory.setRegValueOfAddr(inst.getRt(), rt, InstMemLen::WORD);
            break;
        }
        case 0x04U: {
            // beq, if (rs == rt), go to (pc + 4 + 4 * c(signed))
            unsigned rs, rt;
            int c;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            c = toSigned(inst.getC(), 16);
            unsigned result = toSigned(rs) == toSigned(rt);
            if (result == 1U) {
                memory.setPc(memory.getPc() + 4 + 4 * c);
                return;
            }
            break;
        }
        case 0x05U: {
            // bne, if (rs != rt), go to (pc + 4 + 4 * c(signed))
            unsigned rs, rt;
            int c;
            rs = memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD);
            rt = memory.getRegValueOfAddr(inst.getRt(), InstMemLen::WORD);
            c = toSigned(inst.getC(), 16);
            unsigned result = toSigned(rs) != toSigned(rt);
            if (result == 1U) {
                memory.setPc(memory.getPc() + 4 + 4 * c);
                return;
            }
            break;
        }
        case 0x07U: {
            // bgtz, if (rs > 0), go to (pc + 4 + 4 * c(signed))
            int rs;
            int c;
            rs = toSigned(memory.getRegValueOfAddr(inst.getRs(), InstMemLen::WORD));
            c = toSigned(inst.getC(), 16);
            unsigned rt = toUnsigned(rs > 0);
            if (rt == 1U) {
                memory.setPc(memory.getPc() + 4 + 4 * c);
                return;
            }
            break;
        }
        default: {
            // undefined operation
            break;
        }
    }
    memory.setPc(memory.getPc() + 4);
}

void InstSimulator::simulateTypeJ(const InstDataBin& inst, FILE* errorDump) {
    switch (inst.getOpCode()) {
        case 0x02: {
            // j, pc = (pc + 4)[31:28] | 4 * c(unsigned)
            unsigned c = inst.getC();
            unsigned pc = (getBitsInRange(memory.getPc() + 4, 28, 32) << 28) | (c << 2);
            memory.setPc(pc);
            break;
        }
        case 0x03: {
            // jal, $31 = pc + 4
            //      pc = (pc + 4)[31:28] | 4 * c(unsigned)
            memory.setRegValueOfAddr(31, memory.getPc() + 4, InstMemLen::WORD);
            unsigned c = inst.getC();
            unsigned pc = (getBitsInRange(memory.getPc() + 4, 28, 32) << 28) | (c << 2);
            memory.setPc(pc);
            break;
        }
    }
}

} /* namespace LB */
