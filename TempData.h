#ifndef TEMPDATA_H
#define TEMPDATA_H

struct TempData {
    Fita<char> fita;
    vector<char> alfabeto;
    Transicao transicao;
    unsigned int estado;
    char simbIncial;
    vector<unsigned int> estados;
    vector<unsigned int> finais;
};

#endif
