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
};

}

#endif /* INSTDECODE_H_ */
