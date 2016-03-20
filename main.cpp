/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include "InstSimulator.h"

inline unsigned readWord();
inline unsigned readWordFromBin(FILE* fin);

int main(int argc, char **argv) {
    unsigned pc, len;
    pc = readWord();
    len = readWord();
    unsigned insts[11100];
    printf("len = %u\n", len);
    for (unsigned i = 0; i < len; ++i) {
        insts[i] = readWord();
    }
    unsigned dim[11100];
    unsigned dlen;
    unsigned sp;
    sp = readWord();
    dlen  = readWord();
    for (unsigned i = 0; i < dlen; ++i) {
        dim[i] = readWord();
    }
    LB::InstSimulator simulator;
    simulator.loadImageI(insts, len, pc);
    simulator.loadImageD(dim, dlen, sp);
    simulator.simulate(stdout, stderr);
    return 0;
}

inline unsigned readWord() {
    unsigned a, b;
    scanf("%x%x", &a, &b);
    return (a << 16) | b;
}

inline unsigned readWordFromBin(FILE *fin) {
    unsigned char input[4];
    fread(input, sizeof(char), 4, fin);
    return (input[0] << 24) | (input[1] << 16) | (input[2] << 8) | (input[3]);
}
