/*
 * InstLookUp.h
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#ifndef INSTLOOKUP_H_
#define INSTLOOKUP_H_

#include <string>
#include "InstUtility.h"

namespace LB {

class InstLookUp {
public:
    static std::string opCodeLookUp(const unsigned& src);
    static std::string functLookUp(const unsigned& src);
    static std::string registerLookUp(const unsigned& src);

private:
    const static std::string opCodeLookUpTable[];
    const static std::string functLookUpTable[];
    const static std::string registerLookUpTable[];
};

} /* namespace LB */

#endif /* INSTLOOKUP_H_ */
