#ifndef CORE_H
#define CORE_H

#include <algorithm>
#include <memory>
#include "Fita.h"
#include "Transicao.h"
#include "Cabeca.h"

class Core {
    Fita<char> fita;
    vector<char> alfabeto;
    Transicao transicao;
    vector<char>::iterator cabeca;

    Core() { Core(0x01); }
    Core(char si) : fita(si) { fita.impSimbIni(); }

    public:
        static Core &getInstance(const char ci = 0x01) {
            static Core c(ci);
            return c;
        }
         
        ~Core() { }
        Transicao &pegaTransicao() { return transicao; }
        Fita<char> &pegaFita() { return fita; }
        void adicionaAlfabeto(vector<char> &&a) { alfabeto = a; transicao.setaAlfabeto(alfabeto); }
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
                if (a.first.first > transicao.pegaMaximoEstado() || 
                    a.second.first > transicao.pegaMaximoEstado())
                    return false;
            }

            return true;
        }
        void setaMaximoEstado(unsigned int i) { transicao.setaMaximoEstado(i); }
        void setaEstadoInicial(unsigned int i) { transicao.setaEstadoInicial(i); }
        void setaEstadosFinais(std::initializer_list<unsigned int> il) { transicao.setaEstadosFinais(il); }
        void run() {
            if (!checaConsistenciaComAlfabeto())
                return;
            cabeca = std::begin(fita);
            cout << "* mt vai rodar soh n sei como ainda\n";
        }
};

#endif


