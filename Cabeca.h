#ifndef CABECA_H
#define CABECA_H

/**
 * joilnen leite
 */

#include <vector>

template <typename T> 
class Cabeca : public std::vector<T>::iterator {
    bool iniciada {false};
    public:
        Cabeca() : iniciada{true} { }
        ~Cabeca() { }
        bool foiInciada() { return iniciada; }
};

#endif


