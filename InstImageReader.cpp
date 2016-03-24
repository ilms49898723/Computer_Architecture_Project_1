/*
 * InstImageReader.cpp
 *
 *  Created on: 2016/03/24
 *      Author: LittleBird
 */

#include "InstImageReader.h"

namespace LB {

unsigned InstImageReader::readImageI(FILE* iimage, unsigned char* dst, unsigned* pc) {
    unsigned readPc = readWordFromBin(iimage);
    unsigned len = readWordFromBin(iimage);
    unsigned wordRead = 0;
    *pc = readPc;
    for (wordRead = 0; wordRead < len; ++wordRead) {
        dst[wordRead] = readWordFromBin(iimage);
    }
    return wordRead;
}

unsigned InstImageReader::readImageD(FILE* dimage, unsigned char* dst, unsigned* sp) {
    unsigned readSp = readWordFromBin(dimage);
    unsigned len = readWordFromBin(dimage);
    unsigned wordRead = 0;
    *sp = readSp;
    for (wordRead = 0; wordRead < len; ++wordRead) {
        dst[wordRead] = readWordFromBin(dimage);
    }
    return wordRead;
}

unsigned char InstImageReader::readByteFromBin(FILE* fin) {
    unsigned char input;
    fread(&input, sizeof(unsigned char), 1, fin);
    return input;
}

unsigned InstImageReader::readWordFromBin(FILE* fin) {
    unsigned char input[4];
    fread(input, sizeof(unsigned char), 4, fin);
    return (input[0] << 24) | (input[1] << 16) | (input[2] << 8) | (input[3]);
}

} /* namespace LB */
