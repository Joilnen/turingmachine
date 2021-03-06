#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <string>
#include "idata.h"

class TuringMachine {

    TuringMachine() {  }
    unsigned char hexval(unsigned char c);
    void hex2ascii(const std::string& in, std::string& out);
    void BinaryTable(const char *hexList);
    void IPTable();
    void BinaryAfterIPTable();
    void InputCipherKey();
    void PC1();
    void PC2();
    void Transform1();
    void OutBinaryFromIP();
    void OutBinaryFromPC1();
    void K1();
    void FuncaoF();
    void RoundOutput();

    public:
        void operator =(const TuringMachine &) = delete;
        virtual ~TuringMachine() {  }
        static TuringMachine &GetInstance() {
            static TuringMachine d;
            return d;
        }
        void InputCleanBox();
};

#endif

