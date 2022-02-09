#ifndef FITA_H
#define FITA_H

#include <iostream>
#include <vector>

#include "Cabeca.h"
#include "Transicao.h"

template <typename T> 
class Fita : public std::vector<T> {
    T inicio;
    Cabeca<char> cabeca;
    public:
        Fita(): inicio{0x01} {  }
        Fita(T a): inicio(a) {  }
        ~Fita() { }
        void impSimbIni() {
            if (inicio == 0x01)
                std::cout << "SOH - start of heading simbolo" << std::endl;
        }
        void adiciona(char c) {
            this->push_back(c);
        }
};

#endif


