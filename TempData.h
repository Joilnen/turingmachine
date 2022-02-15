#ifndef TEMPDATA_H
#define TEMPDATA_H

struct TempData {
    Fita<char> fita;
    vector<char> alfabeto;
    Transicao *transicoes;
    unsigned int maximoEstado;
    unsigned int estado;
    char simbIncial;
    vector<unsigned int> *estados;
    set<unsigned int> *finais;
};

#endif
