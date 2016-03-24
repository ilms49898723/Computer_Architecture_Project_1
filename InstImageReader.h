/*
 * InstImageReader.h
 *
 *  Created on: 2016/03/24
 *      Author: LittleBird
 */

#ifndef INSTIMAGEREADER_H_
#define INSTIMAGEREADER_H_

#include <cstdio>
#include <cstdlib>

namespace LB {

// read iimage.bin, dimage.bin using C I/O
class InstImageReader {
public:
    static unsigned readImageI(FILE* iimage, unsigned* dst, unsigned* pc);
    static unsigned readImageD(FILE* dimage, unsigned* dst, unsigned* sp);

private:
    static unsigned char readByteFromBin(FILE* fin);
    static unsigned readWordFromBin(FILE* fin);
};

} /* namespace LB */

#endif /* INSTIMAGEREADER_H_ */
