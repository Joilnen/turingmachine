#include <sstream>
#include "imgui.h"
#include "turing_machine.h"
#include "Core.h"

extern unsigned int Width, Height;


void TuringMachine::MyShowMenuFile()
{
    ImGui::MenuItem("Maquina de Turing", NULL, false, false);
    if (ImGui::MenuItem("Roda Core")) {
        runCore();
    }
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                // ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}

    ImGui::Separator();
    if (ImGui::BeginMenu("Options"))
    {
        static bool enabled = true;
        ImGui::MenuItem("Enabled", "", &enabled);
        ImGui::BeginChild("child", ImVec2(0, 60), true);
        for (int i = 0; i < 10; i++)
            ImGui::Text("Scrolling Text %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
        ImGui::InputFloat("Input", &f, 0.1f);
        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Colors"))
    {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }

    // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // In a real code-base using it would make senses to use this feature from very different code locations.
    if (ImGui::BeginMenu("Options")) // <-- Append!
    {
        static bool b = true;
        ImGui::Checkbox("SomeOption", &b);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
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

void TuringMachine::InputCleanBox() {
    static char entradaAlfabeto[128] {""};
    static char entradaFita[128] {""};
    static char textValue[128] {""};
    static char simbIncial[2] {""};
    static int maximoEstado {0};
    static int ntransicoes {0};
    static vector<unsigned int> estados;
    static map <pair<unsigned int, char>, pair<unsigned int, char> > transicoes;
    static char simboloDe[8] {""};
    static char simboloPara[8] {""};
    static char estadoDe[8] {""};
    static char estadoPara[8] {""};
    std::string inS, outS;


    // ImGui::SetNextWindowSize(ImVec2(810, 600));
    ImGui::SetNextWindowSize(ImVec2(1250, 620));
    ImGui::SetNextWindowPos(ImVec2(50, Height / 2 - ImGui::GetWindowHeight() / 1.1));
    ImGui::Begin("Papadimitriou - joilnen e larissa", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    const int hardcoded_node_0 = 0;
    const int hardcoded_node_1 = 1;
    const int output_attr_id = 0;
    const int input_attr_id = 1;
    unsigned int count {0};

    bool b {true};
    ImGui::ShowDemoWindow(&b);
    ImGui::InputTextWithHint("fita", "entre com alfanumérico", entradaFita, IM_ARRAYSIZE(entradaFita));
    ImGui::Text("0x01"); ImGui::SameLine(); ImGui::Text("símbolo inicial");
    ImGui::InputTextWithHint("alfabeto", "entre com alfanumérico", entradaAlfabeto, IM_ARRAYSIZE(entradaAlfabeto));
    ImGui::InputInt("estado máximo", &maximoEstado);
    if (maximoEstado < 0)
        maximoEstado = 0;

    if (estados.size() != maximoEstado + 1) {
        estados.clear();
        for (count = 0; count < maximoEstado + 1; ++count)
            estados.push_back(count);
    }

    for_each(begin(estados), end(estados), [](auto &a) {
        stringstream ss;
        ss << "e" << a;
        ImGui::Button(ss.str().c_str()); ImGui::SameLine();
    });
    ImGui::Text("estados");

    if (ntransicoes < 0)
        ntransicoes = 0;

    ImGui::InputText("estado de", estadoDe, IM_ARRAYSIZE(estadoDe)); // ImGui::SameLine();
    ImGui::InputText("símbolo de", simboloDe, IM_ARRAYSIZE(simboloDe));//  ImGui::SameLine();
    ImGui::InputText("estado para", estadoPara, IM_ARRAYSIZE(estadoPara));//  ImGui::SameLine();
    ImGui::InputText("símbolo para", simboloPara, IM_ARRAYSIZE(simboloPara));

    ImGui::InputInt("adiciona transições", &ntransicoes);
    if (transicoes.size() != ntransicoes)
        transicoes[pair<unsigned int, char>(atoi(estadoDe), simboloDe[0])] = pair<unsigned int, char> (atoi(estadoPara), simboloPara[0]);
    for_each(begin(transicoes), end(transicoes), [](auto &a) {
        stringstream ss;
        ss << a.first.first;
        ImGui::Button(ss.str().c_str()); ImGui::SameLine();
        ss.clear(); ss.flush(); ss.str(std::string());
        ss << ":" << a.first.second;
        ImGui::Text(ss.str().c_str()); ImGui::SameLine();
        ss.clear(); ss.flush(); ss.str(std::string());
        ss << a.second.first;
        ImGui::Button(ss.str().c_str()); ImGui::SameLine();
        ss.clear(); ss.flush(); ss.str(std::string());
        ss << ":" << a.second.second;
        ImGui::Text(ss.str().c_str());
    });

    ImGui::Button("Checa Consistência");
    ImGui::Button("Executa");
    /****
    if (ImGui::BeginPopupContextItem("my popup"))
    {
        TuringMachine::MyShowMenuFile();
        ImGui::EndPopup();
    }
    ImGui::OpenPopupOnItemClick("my popup", ImGuiPopupFlags_MouseButtonRight);
    if (ImGui::GetIO().MouseClicked[1])
        ImGui::OpenPopup("my popup");
    ****/

    ImGui::End();
}


