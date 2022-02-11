#ifndef CORE_H
#define CORE_H

#include <algorithm>
#include <memory>
#include "Fita.h"
#include "Transicao.h"
#include "Cabeca.h"

const  char mD {0x02}, mE {0x03};

class Core {
    Fita<char> fita;
    vector<char> alfabeto;
    Transicao transicao;
    vector<char>::iterator cabeca;
    unsigned int estado;

    Core() { Core(0x01); }
    Core(char si) : fita(si), estado{0} { fita.impSimbIni(); }

    bool para()
    {
        return false;
    }

    public:
        static Core &getInstance(const char ci = 0x01) {
            static Core c(ci);
            return c;
        }
        // Core(Core const&) = delete;
        void operator=(Core const&) = delete;
         
        Transicao &pegaTransicao() { return transicao; }
        Fita<char> &pegaFita() { return fita; }
        void adicionaAlfabeto(vector<char> &&a) { alfabeto = a; transicao.setaAlfabeto(alfabeto); }
        bool checaConsistencia() {
            //! checa se fita esta no alfabeto
            for (auto &a : fita)
            {
                if (std::find(std::begin(alfabeto), std::end(alfabeto), a) == std::end(alfabeto))
                    return false;
            }

            //! checa se nao transicao (de para) do estado zero (inicial)
            for (auto &a : transicao)
            {
                if (!a.first.first)
                    break;
                return false;
            }

            //! checa transicoes
            for (auto &a : transicao)
            {
                //! transicao (de onde vem) contem apenas simolos do alfabeto ?
                if (std::find(std::begin(alfabeto), std::end(alfabeto), a.first.second)
                        == std::end(alfabeto))
                    return false;
                //! transicao (pra onde vai) contem apenas simolos do alfabeto ?
                //! excluindo-se comandos de direita e esquerda
                if (a.second.second != mE && a.second.second != mD &&
                    std::find(std::begin(alfabeto), std::end(alfabeto), a.second.second) ==
                    std::end(alfabeto))
                        return false;
                //! se estado estah dentro dos limites e se nao parte de estado final
                if (a.first.first < 0 || a.first.first > transicao.pegaMaximoEstado() || 
                    transicao.eh_final(a.first.first))
                        return false;
            }

            return true;
        }
        void setaMaximoEstado(unsigned int i) { transicao.setaMaximoEstado(i); }
        void setaEstadoInicial(unsigned int i) { transicao.setaEstadoInicial(i); }
        void setaEstadosFinais(std::initializer_list<unsigned int> il) { transicao.setaEstadosFinais(il); }
        bool run() {
            if (!checaConsistencia())
                return false;

            if (estado)
                return false;

            cabeca = std::begin(fita);
            while (cabeca != std::end(fita))
            {
                auto r { transicao.processa(cabeca, estado) };
                if (!r)
                    return false;

                if (transicao.eh_final(estado))
                    return true;

                estado = r->first;
                *cabeca = r->second;

                if (*cabeca == mD) ++cabeca;
                if (*cabeca == mE) --cabeca;
            }

            cout << "* mt vai rodar soh n sei como ainda\n";

            return true;
        }
};

#endif


