#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <string>
#include <map>

#include "idata.h"
#ifdef EMSCRIPTEN
    #include <SDL_scancode.h>
#else
    #include <SDL2/SDL_scancode.h>
#endif
#include <algorithm>
#include <vector>

enum class NodeTType {ALFA, ESTS, MAQ, FITA, PROG};

struct NodeT
{
    int   id;
    float value;
    NodeTType type;

    NodeT(const int i, const float v, const NodeTType t) : id(i), value(v), type(t) {}
};

struct LinkT
{
    int id;
    int start_attr, end_attr;
};

class TuringMachine {
    ImNodesEditorContext* context = nullptr;
    std::vector<NodeT>     nodes;
    std::vector<LinkT>     links;
    int                   current_id = 0;
    bool                  ntype[5];

    TuringMachine() { ntype[0] = ntype[1] = ntype[2] = ntype[3] = ntype[4] = true; }
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
    void MyShowMenuFile();

    public:
        void operator =(const TuringMachine &) = delete;
        virtual ~TuringMachine() {  }
        static TuringMachine &GetInstance() {
            static TuringMachine d;
            return d;
        }
        void InputCleanBox();
        void initCore();
        void runCore();
};

#endif

