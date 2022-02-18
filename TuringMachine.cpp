#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "TuringMachine.h"
#include "TuringMachine.h"
#include "Core.h"
#include "TempData.h"

void TuringMachine::initCore()
{
    /**
     * lembrar que core eh criado com simbolo inicial 0x01 por
     * padrao usar getInstance('x') para mudar
     */
    /****
    auto core = Core::getInstance();
    //! vector<char> alfa {'a', 'b', 'c', ' ', 'x'}; 
    core.adicionaAlfabeto({'a', 'b', 'c', ' ', 'x', 0x01});
    core.setaMaximoEstado(5);
    core.setaEstadosFinais({4});
    core.pegaTransicao()[{5, 'b'}] = {4, 'a'};
    // core.pegaTransicao()[{0, 'b'}] = {0, mE};
    core.pegaTransicao()[{0, 0x01}] = {5, mD};
    core.pegaFita().adiciona('b');
    core.pegaFita().adiciona('b');
    std::cout << "Numero de transicoes " << core.pegaTransicao().size() << std::endl;
    std::cout << "Numero de dados na fita " << core.pegaFita().size() << std::endl;
    std::cout << "Conscistente " <<  std::boolalpha << core.checaConsistencia() << std::endl;
    std::cout << "Estado atual antes do run " <<  core.pegaEstadoAtual() << std::endl;
    std::cout << "Aceita ? " << std::boolalpha << core.run() << std::endl;
    std::cout << "Estado final depois do run " <<  core.pegaEstadoAtual() << std::endl;
    ****/
}

void TuringMachine::runCore(Core &core)
{

    //! 0 eh o estado inicial padrao
    core.adicionaAlfabeto({'c', 0x01});
    core.setaMaximoEstado(3);
    core.setaEstadosAceitos({3});
    core.pegaTransicao().limpa();
    core.pegaTransicao()[{0, 'c'}] = {1, 'c'};
    core.pegaTransicao()[{1, 'c'}] = {2, 'c'};
    core.pegaTransicao()[{2, 'c'}] = {3, mD};
    core.pegaFita().limpa();
    core.pegaFita().adiciona('c');
    core.pegaFita().adiciona('c');
    core.pegaFita().adiciona('c');
    core.pegaFita().adiciona('c');
    core.pegaFita().adiciona('c');
    core.pegaFita().adiciona('c');
    std::cout << "Numero de transicoes " << core.pegaTransicao().size() << std::endl;
    std::cout << "Numero de dados na fita " << core.pegaFita().size() << std::endl;
    std::cout << "Conscistente " <<  std::boolalpha << core.checaConsistencia() << std::endl;

    core.run();
}

void TuringMachine::init()
{
    ifstream ifs;
    string line;
    json j;
    ifs.open("maquina.json");
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
            cerr << "* maquina.json inconsistente\n";
        }
    }
    else
        cerr << "* erro ao abrir arquivo maquina.json\n"; 
}

void TuringMachine::mostraConfig(Core &core)
{
    cout << "* fita\n";
    auto v = core.pegaFita();
    for (auto &a : v)
        cout << a << endl;

    cout << "* alfabeto\n";
    auto alfa = core.pegaAlfabeto();
    for (auto &a : alfa)
        cout << a << endl;

    for (auto &a : core.pegaTransicao())
        cout << a.first.first << " " << a.first.second << " ==> " 
             << a.second.first << " " << a.second.second <<  endl;

}

void TuringMachine::config(Core &core)
{
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
    // seta alfabeto
    for_each (begin(maquinaConfig["alfabeto"]), end(maquinaConfig["alfabeto"]), [&v](auto &a) {
        // cout << typeid(a).name() << endl;
        string s = a;
        v.push_back(s.c_str()[0]);
    }); 
    core.adicionaAlfabeto(move(v));

    // seta transicoes
    for_each(begin(maquinaConfig["transicoes"]), end(maquinaConfig["transicoes"]), [&core](auto &a) {
        pair<unsigned int, char> p0, p1;
        unsigned int i = a["de"][0];
        std::string c = a["de"][1];
        p0 = {i, c.c_str()[0]};
        i = a["para"][0];
        c = a["para"][1];
        p1 = {i, c.c_str()[0]};

        string m = a["move"];
        cout << "(" << p0.first << ", " << p0.second << ")" << "=>"
             << "(" << p1.first << ", " << p1.second << ")" << " " << m << endl;
        if (m == "E")
            core.adicionaMove(Move::E);
        else if (m == "D")
            core.adicionaMove(Move::D);
        core.pegaTransicao()[p0] = p1;
    });

    // seta simbolo branco
    string s = maquinaConfig["simbolo_branco"];
    core.setaSimboloBranco(s.c_str()[0]);

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
}


