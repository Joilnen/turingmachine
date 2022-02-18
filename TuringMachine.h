#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <string>
#include <sstream>
#include <map>

#include "idata.h"
#ifdef EMSCRIPTEN
    #include <SDL_scancode.h>
#else
    #include <SDL2/SDL_scancode.h>
#endif
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
        void initCore();
        void runCore(Core &core);
        void init();
        void config(Core &core);
        void mostraConfig(Core &core);
};

#endif

