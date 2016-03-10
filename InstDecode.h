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
#include "InstUtility.h"

namespace LB {

class InstDecode {
public:
    // Decode hex-decimal format instruction set to readable string
    // All static functions
    // return type InstData defined in "InstData.h"

    // decode instruction set with format like 0x7FFFFFFF
    static InstData decodeHexInst(const unsigned& src);
    // decode instruction set with format like 0x7FFF 0xFFFF
    // argument array passed by pointer
    // will be merged and call decodeHexInst(const unsigned &src);
    static InstData decodeHexInst(const unsigned* src);
};

} /* namespace LB */

#endif /* INSTDECODE_H_ */
