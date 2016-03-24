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
    // load iimage, dimage
    unsigned ilen, dlen;
    unsigned pc, sp;
    unsigned inst[2048], memory[2048];
    ilen = LB::InstImageReader::readImageI("iimage.bin", inst, &pc);
    dlen = LB::InstImageReader::readImageD("dimage.bin", memory, &sp);
    // simulate
    FILE *snapshot, *error;
    snapshot = fopen("userSnapShot.rpt", "w");
    error = fopen("userErrorDump.rpt", "w");
    if (!snapshot || !error) {
        return 0;
    }
    LB::InstSimulator simulator;
    simulator.loadImageI(inst, ilen, pc);
    simulator.loadImageD(memory, dlen, sp);
    simulator.simulate(snapshot, error);
    fclose(snapshot);
    fclose(error);
    return 0;
}
