/*
 * InstDecode.h
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#ifndef INSTDECODE_H_
#define INSTDECODE_H_

#include <string>
#include "InstData.h"
#include "InstLookUp.h"

namespace LB {

// Decode hex-decimal format instruction set to readable string
// All static functions
// return as type InstData defined in "InstData.h"

class InstDecode {
public:
    // decode instruction set with format like 0x7FFFFFFF
    static InstData decodeHexInst(const unsigned &src);
    // decode instruction set with format like 0x7FFF 0xFFFF
    // will be merged and call decodeHexInst(const int &src);
    static InstData decodeHexInst(const unsigned *src);

private:
    // get bits from range [l, r)
    // ex. getBitsInRange(0xC, 0, 3) returns 0x4
    // 0xC = 0b1100 returns 0b100
    // zero based
    static unsigned getBitsInRange(const unsigned& src, const int& l, const int& r);
};

}

#endif /* INSTDECODE_H_ */
