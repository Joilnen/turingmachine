#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

/**
 * joilnen leite
 */

#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>
#include "Core.h"
#include "json.hpp"

using json = nlohmann::json;
 
struct TempData;

class TuringMachine {
    int  current_id = 0;
    bool ntype[5];
    std::stringstream  buffer;
    json maquinaConfig;

    TuringMachine() { ntype[0] = ntype[1] = ntype[2] = ntype[3] = ntype[4] = true; }
    void MyShowMenuFile();

    public:
        void operator =(const TuringMachine &) = delete;
        virtual ~TuringMachine() {  }
        static TuringMachine &getInstance() {
            static TuringMachine d;
            return d;
        }
        void roda(Core &core);
        void init(const char *fileName = "maquina.json");
        void config(Core &core);
        void mostraConfig(Core &core);
};

#endif

