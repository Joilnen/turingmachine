#ifndef CABECA_H
#define CABECA_H

#include <vector>

template <typename T> 
class Cabeca : public std::vector<T>::iterator {
    bool iniciado {false};
    public:
        Cabeca() { }
        ~Cabeca() { }
        bool foiInciado() { return iniciado; }
};

#endif


