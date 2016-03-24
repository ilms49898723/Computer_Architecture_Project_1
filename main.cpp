/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include <cstdlib>
#include "InstSimulator.h"
#include "InstImageReader.h"

int main(int argc, char **argv) {
    unsigned ilen, dlen;
    unsigned pc, sp;
    unsigned inst[2048], memory[2048];
    ilen = LB::InstImageReader::readImageI("iimage.bin", inst, &pc);
    dlen = LB::InstImageReader::readImageD("dimage.bin", memory, &sp);

    FILE *snapshot, *error;
    snapshot = fopen("userSnapShot.rpt", "w");
    error = fopen("userErrorDump.rpt", "w");
    LB::InstSimulator simulator;
    simulator.loadImageI(inst, ilen, pc);
    simulator.loadImageD(memory, dlen, sp);
    simulator.simulate(snapshot, error);
    fclose(snapshot);
    fclose(error);
//    unsigned pc, len;
//    pc = readWord();
//    len = readWord();
//    unsigned insts[11100];
//    printf("len = %u\n", len);
//    for (unsigned i = 0; i < len; ++i) {
//        insts[i] = readWord();
//    }
//    unsigned dim[11100];
//    unsigned dlen;
//    unsigned sp;
//    sp = readWord();
//    dlen  = readWord();
//    for (unsigned i = 0; i < dlen; ++i) {
//        dim[i] = readWord();
//    }
//    LB::InstSimulator simulator;
//    simulator.loadImageI(insts, len, pc);
//    simulator.loadImageD(dim, dlen, sp);
//    simulator.simulate(stdout, stderr);
    return 0;
}
