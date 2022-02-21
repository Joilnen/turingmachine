#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "TuringMachine.h"
#include "TuringMachine.h"
#include "Core.h"
#include "jcurses.h"

void TuringMachine::init(const char *fileName)
{
    LTELA;
    ifstream ifs;
    string line;
    json j;
    ifs.open(fileName);
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            cout << line << '\n';
            buffer << line << '\n';
        }
        ifs.close();
        try {
            maquinaConfig = json::parse(buffer.str());
        }
        catch (...)
        {
            cerr << "* " << fileName << " inconsistente\n";
            exit(-2);
        }
    }
    else { cerr << "* erro ao abrir arquivo maquina.json\n"; exit(-1); }
    CMR1;
}

void TuringMachine::mostraConfig(Core &core)
{
    LTELA;
    cout << "** f:" << __func__ << endl;
    cout << "* fita\n";
    auto v = core.pegaFita();
    for (auto &a : v)
        cout << a << endl;

    cout << "\n* alfabeto\n";
    auto alfa = core.pegaAlfabeto();
    for (auto &a : alfa)
        cout << a << endl;

    cout << "\n* simb branco\n";
    cout << core.pegaSimboloBranco() << endl;

    cout << "\n* simb incial\n";
    cout << core.pegaSimboloInicial() << endl;

    cout << "\n* transicao\n";
    for (auto &a : core.pegaTransicao()) {
        cout << a.first.first << " " << a.first.second << " ==> " 
             << get<0>(a.second) << " " << get<1>(a.second) << " ";
        if (get<2>(a.second) == Move::E)
            cout << "E\n";
        else
            cout << "D\n";
    }

    cout << "\n* maximo estado\n";
    cout << core.pegaMaximoEstado() << endl;

    cout << "\n* estado atual\n";
    cout << core.pegaEstadoAtual() << endl;

    cout << "\n* estados aceitos\n";
    for (auto &a : core.pegaEstadosAceitos())
        cout << a << endl;

    cout << "\n* estados rejeitados\n";
    for (auto &a : core.pegaEstadosRejeitados())
        cout << a << endl;

    cout << "\n* lista move\n";
    for (auto &a : core.pegaListaMove()) {
        if (a == Move::E)
            cout << "E" << endl;
        else if (a == Move::D)
            cout << "D" << endl;
    }
    CMR1;
}

void TuringMachine::config(Core &core)
{
    LTELA;
    cout << "** f:" << __func__ << endl;
    cout << "Contem trancicoes " <<  boolalpha << maquinaConfig.contains("transicoes") << endl;
    cout << "Contem fita " <<  boolalpha << maquinaConfig.contains("fita") << endl;

    vector<char> v;
    for_each (begin(maquinaConfig["fita"]), end(maquinaConfig["fita"]), [&core](auto &a) {
        // cout << typeid(a).name() << endl;
        string s = a;
        core.pegaFita().push_back(s.c_str()[0]);
    }); 
    cout << "Mostra Fita\n";
    for (auto &a : core.pegaFita())
        cout << a << endl;
    //
    // seta simbolo branco
    string s = maquinaConfig["simbolo_branco"];
    core.setaSimboloBranco(s.c_str()[0]);

    // seta simbolo incial
    s = maquinaConfig["simbolo_inicio"];
    core.setaSimboloInicial(s.c_str()[0]);

    // seta alfabeto
    for_each (begin(maquinaConfig["alfabeto"]), end(maquinaConfig["alfabeto"]), [&v](auto &a) {
        // cout << typeid(a).name() << endl;
        string s = a;
        v.push_back(s.c_str()[0]);
    }); 
    core.adicionaAlfabeto(move(v));

    // seta transicoes
    for_each(begin(maquinaConfig["transicoes"]), end(maquinaConfig["transicoes"]), [&core](auto &a) {
        pair<unsigned int, char> p0;
        tuple<unsigned int, char, Move> p1;
        unsigned int i = a["de"][0];
        std::string c = a["de"][1];
        p0 = {i, c.c_str()[0]};
        i = a["para"][0];
        c = a["para"][1];

        string m = a["move"];
        cout << "(" << p0.first << ", " << p0.second << ")" << "=>"
             << "(" << get<0>(p1) << ", " << get<1>(p1) << ", " << m << ")" << endl;
        if (m == "E")
            p1 = {i, c.c_str()[0], Move::E};
        else if (m == "D")
            p1 = {i, c.c_str()[0], Move::D};
        core.pegaTransicao()[p0] = p1;
    });

    // seta maximo estado
    unsigned int i = maquinaConfig["maximo_estado"];
    core.setaMaximoEstado(i);

    // 
    vector<unsigned int> vi;
    for_each(begin(maquinaConfig["estados_aceitos"]), end(maquinaConfig["estados_aceitos"]), [&vi](auto &a) {
        vi.push_back(a);
    });
    core.setaEstadosAceitos(move(vi));

    vi.clear();
    for_each(begin(maquinaConfig["estados_rejeitados"]), end(maquinaConfig["estados_rejeitados"]), [&vi](auto &a) {
        vi.push_back(a);
    });
    core.setaEstadosRejeitados(move(vi));
    CMR1;
}

void TuringMachine::roda(Core &core)
{
    LTELA;
    cout << "** f:" << __func__ << endl;
    std::cout << "Numero de transicoes " << core.pegaTransicao().size() << std::endl;
    std::cout << "Numero de dados na fita " << core.pegaFita().size() << std::endl;
    std::cout << "Consistente " <<  std::boolalpha << core.checaConsistencia() << std::endl;

    core.roda();
    CMR1;
}


