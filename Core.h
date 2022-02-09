#ifndef CORE_H
#define CORE_H

#include "Fita.h"
#include "Transicao.h"
#include "Cabeca.h"

class Core {
    Fita<char> fita;
    Transicao transicao;

    Core() { Core(0x01); }
    Core(char si) : fita(si) { fita.impSimbIni(); }

    public:
        static Core &getInstance() {
            static Core c;
            return c;
        }
         
        ~Core() { }
        Transicao &pegaTransicao() { return transicao; }
        Fita<char> &pegaFita() { return fita; }
};

#endif


