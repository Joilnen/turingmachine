#ifndef FITA_H
#define FITA_H

#include <iostream>
#include <vector>

#include "Cabeca.h"
#include "Transicao.h"

template <typename T> 
class Fita : public std::vector<T> {
    T simbInicial;
    public:
        Fita(): simbInicial{0x01} { this->push_back(simbInicial); }
        Fita(T a): simbInicial(a) { this->push_back(simbInicial); }
        ~Fita() { }
        void impSimbIni() {
            if (simbInicial == 0x01)
                std::cout << "SOH - start of heading simbolo" << std::endl;
        }
        void adiciona(char c) {
            this->push_back(c);
        }
        T &pegaSimbInicial() { return simbInicial; }
};

#endif


