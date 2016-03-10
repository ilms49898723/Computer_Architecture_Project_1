/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include "InstSimulator.h"

unsigned readWord();

int main(int argc, char **argv) {
    unsigned pc, len;
    pc = readWord();
    len = readWord();
    unsigned insts[11100];
    printf("len = %u\n", len);
    for (unsigned i = 0; i < len; ++i) {
        insts[i] = readWord();
    }
    LB::InstSimulator simulator;
    simulator.loadImageI(insts, len, pc);
    return 0;
}

unsigned readWord() {
    unsigned a, b;
    scanf("%x%x", &a, &b);
    return (a << 16) | b;
}
