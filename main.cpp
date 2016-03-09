/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include "InstDecode.h"

int main(int argc, char **argv) {
    unsigned x[2];
    scanf("%x%x", &x[0], &x[1]);
    LB::InstDecode::decodeHexInst(x);
    return 0;
}
