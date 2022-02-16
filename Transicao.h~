#ifndef Transicao_H
#define Transicao_H

#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

class Transicao : public 
        map<pair<unsigned int, char>, pair<unsigned int, char> > {
    vector<unsigned int> finais;
    unsigned int inicial, maxEstado;
    vector<char> *alfa;
    public:
        Transicao() { }
        ~Transicao() { }
        void setaEstadoInicial(unsigned int i) { inicial = i; }
        void setaMaximoEstado(unsigned int i) {
            maxEstado = i;
            for(unsigned int i {0}; i < maxEstado + 1; ++i)
                finais.push_back(false);
        }
        unsigned int pegaMaximoEstado() { return maxEstado; }
        void adicionaEstadoFinal(unsigned int i) {
            if (i < maxEstado + 1)
                finais[i] = true;
            else
                cerr << "* estado fora dos limites\n";
        }
        /****
        void operator[] (pair<unsigned int, char> i, pair<unsigned int, char> j, std::greater<char> g)
        {
            if (i.first <= maxEstado && j.first <= maxEstado &&
                std::find(std::begin(*alfa), std::end(*alfa), i.second) != std::end(*alfa) &&
                std::find(std::begin(*alfa), std::end(*alfa), j.second) != std::end(*alfa))
                this->insert({i, j});
            else
                cerr << "* estado ou simbolo fora dos limites\n";
        }
        ****/
        void setaAlfabeto(vector<char> &a) { alfa = &a; }
        void setaEstadosFinais(std::vector<unsigned int> il) { finais = il; }
        void setaEstadosFinais(std::initializer_list<unsigned int> il) {
            finais.clear();
            for (auto &a : il)
                if (a >= 0 && a < maxEstado + 1)
                    finais.push_back(a);
        }

        pair<unsigned int, char> *processa(vector<char>::iterator &c, unsigned int &e)
        {
            for (auto &a : *this)
            {
                std::cout << a.first.first << std::endl;
                if (e == a.first.first && *c == a.first.second)
                    return &a.second;
            }

            return nullptr;
        }

        bool eh_final(unsigned int i)
        {
            return std::find(std::begin(finais), std::end(finais), i) != std::end(finais);
        }
        
        void limpa() {
            this->clear();
        }
};

#endif


