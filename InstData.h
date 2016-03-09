/*
 * InstData.h
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#ifndef INSTDATA_H_
#define INSTDATA_H_

#include <string>

// Data structure to store readable Instruction set using "String"
// Use get() function to Access Private Members(read only)

// enum class for instruction type
// R-type, I-type, J-type, Specialized, Undefined(ex. error)
enum class InstType : unsigned {
    R, I, J, S, Undef
};

class InstData {
public:
    InstData();
    virtual ~InstData();
    InstType getAll(std::string *dst);
    std::string getOpCode();
    std::string getRs();
    std::string getRt();
    std::string getRd();
    std::string getC();
    std::string getFunct();
    void setType(const InstType& val);
    void setOpCode(const std::string& val);
    void setRs(const std::string &val);
    void setRt(const std::string &val);
    void setRd(const std::string &val);
    void setC(const std::string &val);
    void setFunct(const std::string &val);
private:
    InstType type;
    std::string opCode;
    std::string rs;
    std::string rt;
    std::string rd;
    std::string c;
    std::string funct;
};

#endif /* INSTDATA_H_ */
