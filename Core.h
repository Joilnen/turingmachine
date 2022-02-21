#ifndef CORE_H
#define CORE_H

#include <algorithm>
#include <memory>
#include <iostream>
#include "jcurses.h"
#include "Fita.h"
#include "Transicao.h"
#include "Cabeca.h"

using namespace std;

class Core {
    Fita<char> fita;
    vector<char> alfabeto;
    vector<char> alfabetoMaquina;
    Transicao transicao;
    vector<char>::iterator cabeca;
    unsigned int estado;
    char simboloBranco;

    Core() {  }

    bool para()
    {
        return false;
    }

    public:
        static Core &getInstance() {
            static Core c;
            return c;
        }
        // Core(Core const&) = delete;
        void operator=(Core const&) = delete;
         
        void setaSimboloInicial(const char c) { fita[0] = c; }
        char pegaSimboloInicial() { return fita[0]; }
        void setaSimboloBranco(const char c) { simboloBranco = c; }
        const char &pegaSimboloBranco() { return simboloBranco; }
        Transicao &pegaTransicao() { return transicao; }
        Fita<char> &pegaFita() { return fita; }
        void adicionaAlfabeto(vector<char> &&a) {
            alfabeto = a;
            alfabetoMaquina = a;
            alfabetoMaquina.push_back(simboloBranco);
            alfabetoMaquina.push_back(fita[0]);
            transicao.setaAlfabeto(alfabeto);
        }
        vector<char> &pegaAlfabeto() { return alfabeto; }
        bool checaConsistencia() {
            // cout << "))) Fita\n";
            // for (auto &a : fita)
            //     cout << a << endl;
            // cout << "))) Alfabeto da Maquina\n";
            // for (auto &a : alfabetoMaquina)
            //     cout << a << endl;
            //! checa se fita esta no alfabeto
            for (auto &a : fita)
            {
                if (std::find(std::begin(alfabetoMaquina), std::end(alfabetoMaquina), a) == std::end(alfabetoMaquina))
                    return false;
            }

            //! checa transicoes
            for (auto &a : transicao)
            {
                //! transicao (de onde vem) contem apenas simbolos do alfabeto ?
                if (std::find(std::begin(alfabetoMaquina), std::end(alfabetoMaquina), a.first.second) == std::end(alfabetoMaquina))
                    return false;
                //! transicao (pra onde vai) contem apenas simolos do alfabeto ?
                if (std::find(std::begin(alfabetoMaquina), std::end(alfabetoMaquina), get<1>(a.second)) == std::end(alfabetoMaquina))
                        return false;
                //! se estado estah dentro dos limites e se nao parte de estado final
                if (a.first.first < 0 || a.first.first > transicao.pegaMaximoEstado())
                        return false;
                //
                //! se estado estah dentro dos limites e se nao parte de estado final
                if (get<0>(a.second) < 0 || get<0>(a.second) > transicao.pegaMaximoEstado())
                        return false;
            }

            return true;
        }
        unsigned int pegaEstadoAtual() { return estado; }
        void setaMaximoEstado(unsigned int i) { transicao.setaMaximoEstado(i); }
        unsigned int  pegaMaximoEstado() { return transicao.pegaMaximoEstado(); }
        void setaEstadoInicial(unsigned int i) { transicao.setaEstadoInicial(i); }
        void setaEstadosAceitos(std::initializer_list<unsigned int> il) { transicao.setaEstadosAceitos(il); }
        vector<unsigned int> &pegaEstadosAceitos() { return transicao.pegaEstadosAceitos(); }
        void setaEstadosAceitos(const vector<unsigned int> &il) { transicao.setaEstadosAceitos(il); }
        void setaEstadosRejeitados(std::initializer_list<unsigned int> il) { transicao.setaEstadosRejeitados(il); }
        void setaEstadosRejeitados(const vector<unsigned int> &il) { transicao.setaEstadosRejeitados(il); }
        vector<unsigned int> &pegaEstadosRejeitados() { return transicao.pegaEstadosRejeitados(); }
        void adicionaMove(Move m) { transicao.adicionaMove(m); }
        vector<Move> &pegaListaMove() { return transicao.pegaListaMove(); }

        bool roda() {
            int lFita = 10, cFita, cStart, lStart, cCabeca;
            lStart = lFita;
            cStart = cFita = 40 - fita.size() / 2 + 1;

            if (!checaConsistencia())
                return false;

            if (estado)
                return false;

            cabeca = begin(fita);
            // cout << "Valor cabeca\n";
            // for (auto a = cabeca; a != end(fita); ++a) {
            //     cout << static_cast<int>(*a) << " "
            //          << *a << " ";
            // }
            // cout << "\n";

            cFita = cCabeca = cStart;
            while (cabeca != std::end(fita))
            {
                auto r { transicao.processa(cabeca, estado) };
                LTELA;
                for (auto &a : fita)
                   TAPEFORMAT_0(lFita, cFita++, a);
                TAPEFORMAT_1(lStart, cCabeca, *cabeca);
                if (!r) {
                    // cout << "\n* pos na fita\n";
                    // for_each(begin(fita), cabeca + 1, [](auto &a) { cout << a; });
                    // cout << endl;
                    if (transicao.estado_final(estado) > 0) {
                        INFO_ACEITA("ACEITA");
                        return true;
                    }
                    else {
                        INFO_REJEITA("REJEITA");
                        return false;
                    }
                }
                estado = get<0>(*r);
                *cabeca = get<1>(*r);

                if (transicao.estado_final(estado) > 0) {
                    // cout << "* pos na fita\n";
                    // for_each(begin(fita), cabeca+1, [](auto &a) { cout << a; });
                    // cout << endl;
                    INFO_ACEITA("ACEITA");
                    return true;
                }
                if (get<2>(*r) == Move::D) { ++cabeca; ++cCabeca; }
                if (get<2>(*r) == Move::E) { --cabeca; --cCabeca; }

                // cout << "rfirst " << get<0>(*r) << " rsecond " << static_cast<int>(get<1>(*r)) << endl;
                // cout << "*cabeca " << static_cast<int>(*cabeca)  << endl;

                cFita = cStart;
                CMR1;
            }

            cout << "* mt vai rodar soh n sei como ainda\n";

            return false;
        }
};

#endif


