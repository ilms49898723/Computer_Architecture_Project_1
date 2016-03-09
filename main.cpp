/*
 * main.cpp
 *
 *  Created on: 2016/03/08
 *      Author: LittleBird
 */

#include <cstdio>
#include "InstDecode.h"
#include "InstData.h"

int main(int argc, char **argv) {
    unsigned x[2];
    while (scanf("%x%x", &x[0], &x[1]) == 2) {
        LB::InstData ret;
        ret = LB::InstDecode::decodeHexInst(x);
        printf("%s\n", ret.toString().c_str());
    }
    return 0;
}
