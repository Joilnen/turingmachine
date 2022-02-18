#include <fstream>
#include <sstream>
#include <set>
#include "TuringMachine.h"
#include "TuringMachine.h"
#include "Core.h"
#include "TempData.h"

void TuringMachine::checaConsistencia(TempData &t)
{
    auto core = Core::getInstance();
    //! vector<char> alfa {'a', 'b', 'c', ' ', 'x'}; 
    core.adicionaAlfabeto(move(t.alfabeto));
    core.setaMaximoEstado(t.maximoEstado);
    vector<unsigned int> f;
    // for (auto &a : t.finais) f.push_back(a); 
    // core.setaEstadosFinais(forward(f));
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
}

void TuringMachine::initCore()
{
    /**
     * lembrar que core eh criado com simbolo inicial 0x01 por
     * padrao usar getInstance('x') para mudar
     */
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
}

void TuringMachine::runCore()
{
    Core &core = Core::getInstance();

    //! 0 eh o estado inicial padrao
    core.adicionaAlfabeto({'c', 0x01});
    core.setaMaximoEstado(3);
    core.setaEstadosFinais({3});
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

void TuringMachine::run()
{
    auto core = Core::getInstance();

    cout << "Show " <<  boolalpha << maquinaConfig.contains("transicoes") << endl;
    vector<char> v;
    for_each (begin(maquinaConfig["alfabeto"]), end(maquinaConfig["alfabeto"]), [&v](auto &a) {
        // cout << typeid(a).name() << endl;
        string s = a;
        v.push_back(s.c_str()[0]);
    }); 
    core.adicionaAlfabeto(move(v));

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

}


