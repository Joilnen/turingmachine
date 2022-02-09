#ifndef CORE_H
#define CORE_H

#include <algorithm>
#include "Fita.h"
#include "Transicao.h"
#include "Cabeca.h"

class Core {
    Fita<char> fita;
    vector<char> alfabeto;
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
        void adicionaAlfabeto(vector<char> &a) { alfabeto = a; }
        bool checaConsistenciaComAlfabeto() {
            for (auto &a : fita)
            {
                if (std::find(std::begin(alfabeto), std::end(alfabeto), a) == std::end(alfabeto))
                    return false;
            }

            for (auto &a : transicao)
            {
                if (std::find(std::begin(alfabeto), std::end(alfabeto), a.first.second)
                        == std::end(alfabeto))
                    return false;
                if (std::find(std::begin(alfabeto), std::end(alfabeto), a.second.second)
                        == std::end(alfabeto))
                    return false;
            }

            return true;
        }
};

#endif


