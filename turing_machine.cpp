#include "imgui.h"
#include "imnodes.h"
#include "turing_machine.h"
#include "Core.h"

extern unsigned int Width, Height;
/**
 * from stackoverflow (zwol)
 **/
unsigned char TuringMachine::hexval(unsigned char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    else if ('a' <= c && c <= 'f')
        return c - 'a' + 10;
    else if ('A' <= c && c <= 'F')
        return c - 'A' + 10;
    else abort();
}

void TuringMachine::hex2ascii(const std::string& in, std::string& out)
{
    out.clear();
    out.reserve(in.length() / 2);
    for (std::string::const_iterator p = in.begin(); p != in.end(); p++) {
       unsigned char c = hexval(*p);
       p++;
       if (p == in.end()) break; // incomplete last digit - should report error
       c = (c << 4) + hexval(*p); // + takes precedence over <<
       out.push_back(c);
    }
}

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0') 

void TuringMachine::BinaryTable(const char *hexList) {
    unsigned int tableNline = 4;
    unsigned int tableHeight = 80;
    ImGui::BeginChild("ChildR1", ImVec2(ImGui::GetWindowWidth(), tableHeight), true);
    if (ImGui::BeginTable("table_context_menu06", tableNline)) {
        // ImGui::TableSetupColumn("Coluna 0");
        // ImGui::TableSetupColumn("Coluna 1");
        // ImGui::TableSetupColumn("Coluna 2");
        // ImGui::TableSetupColumn("Coluna 3");

        // ImGui::TableHeadersRow();
        int s = strlen(hexList);
        int count = 0;
        for (int row = 0; row < s / tableNline + (int)(s % tableNline); row++) {                        
            ImGui::TableNextRow();
            for (int column = 0; column < tableNline; column++) {
                if(count >= s) break;
                ImGui::TableSetColumnIndex(column);
                ImGui::Text(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(*(hexList + row * tableNline + column)));
                count++;
            }
        }
        ImGui::EndTable();
    }
    ImGui::EndChild();
}

void TuringMachine::IPTable() {

    enum ContentsType { CT_Text, CT_FillButton };
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    static bool display_headers = false;
    static int contents_type = CT_Text;

    ImGui::Text("Tabela IP(m)");
    if (ImGui::BeginTable("table_context_menu05", 8, flags))
    {
        // Display headers so we can inspect their interaction with borders.
        // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
        int tableData[][8] = {
            {58, 50, 42, 34, 26, 18, 10, 2}, 
            {60, 52, 44, 36, 28, 20, 12, 4},
            {62, 54, 46, 38, 30, 22, 14, 6},
            {64, 56, 48, 40, 32, 24, 16, 8},
            {57, 49, 41, 33, 25, 17, 9 , 1},
            {59, 51, 43, 35, 27, 19, 11, 3},
            {61, 53, 45, 37, 29, 21, 13, 5},
            {63, 55, 47, 39, 31, 23, 15, 7}
        };

        for (int row = 0; row < 8; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 8; column++)
            {
                ImGui::TableSetColumnIndex(column);
                char buf[32];
                sprintf(buf, "%d", tableData[row][column]);
                if (contents_type == CT_Text)
                    ImGui::TextUnformatted(buf);
                else if (contents_type)
                    ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
            }
        }
        ImGui::EndTable();
    }
}

void TuringMachine::PC1() {

    enum ContentsType { CT_Text, CT_FillButton };
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    static bool display_headers = false;
    static int contents_type = CT_Text;

    ImGui::Text("Tabela PC-1(k)");
    if (ImGui::BeginTable("table_context_menu04", 8, flags))
    {
        // Display headers so we can inspect their interaction with borders.
        // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
        int tableData[][8] = {
            {57, 49, 41, 33, 25, 17, 9, 1},
            {58, 50, 42, 34, 26, 18, 10, 2},
            {59, 51, 43, 35, 27, 19, 11, 3},
            {60, 52, 44, 36, 63, 55, 47, 39},
            {31, 23, 15, 7, 62, 54, 46, 38},
            {30, 22, 14, 6, 61, 53, 45, 37},
            {29, 21, 13, 5, 28, 20, 12, 4}
        };

        for (int row = 0; row < 7; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 8; column++)
            {
                ImGui::TableSetColumnIndex(column);
                char buf[32];
                sprintf(buf, "%d", tableData[row][column]);
                if (contents_type == CT_Text)
                    ImGui::TextUnformatted(buf);
                else if (contents_type)
                    ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
            }
        }
        ImGui::EndTable();
    }
}

void TuringMachine::PC2() {
    enum ContentsType { CT_Text, CT_FillButton };
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    static bool display_headers = false;
    static int contents_type = CT_Text;

    ImGui::Text("Tabela PC-2(k)");
    if (ImGui::BeginTable("table_context_menu03", 8, flags))
    {
        // Display headers so we can inspect their interaction with borders.
        // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
        int tableData[][8] = {
            {14, 17, 11, 24,  1,  5,  3, 28},
            {15, 6 , 21, 10, 23, 19, 12, 4},
            {26, 8 , 16, 7 , 27, 20, 13, 2},
            {41, 52, 31, 37, 47, 55, 30, 40},
            {51, 45, 33, 48, 44, 49, 39, 56},
            {34, 53, 46, 42, 50, 36, 29, 32}
        };

        for (int row = 0; row < 6; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 8; column++)
            {
                ImGui::TableSetColumnIndex(column);
                char buf[32];
                sprintf(buf, "%d", tableData[row][column]);
                if (contents_type == CT_Text)
                    ImGui::TextUnformatted(buf);
                else if (contents_type)
                    ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
            }
        }
        ImGui::EndTable();
    }

}

void TuringMachine::BinaryAfterIPTable() {



}

void TuringMachine::InputCipherKey() {
    unsigned int tableNline = 4;
    unsigned int tableHeight = 80;
    static char inputValue[128] {""};
    ImGui::InputTextWithHint("i-hex chave (k)", "entre com hexadecimais", inputValue, IM_ARRAYSIZE(inputValue), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
    ImGui::BeginChild("ChildR2", ImVec2(ImGui::GetWindowWidth(), tableHeight), true);
    if (ImGui::BeginTable("table_context_menu", tableNline)) {
        // ImGui::TableSetupColumn("Coluna 0");
        // ImGui::TableSetupColumn("Coluna 1");
        // ImGui::TableSetupColumn("Coluna 2");
        // ImGui::TableSetupColumn("Coluna 3");
        // ImGui::TableHeadersRow();

        int s = strlen(inputValue);
        int count = 0;
        for (int row = 0; row < s / tableNline + (int)(s % tableNline); row++) {   
            ImGui::TableNextRow();
            for (int column = 0; column < tableNline; column++) {
                if(count >= s) break;
                ImGui::TableSetColumnIndex(column);
                ImGui::Text(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(*(inputValue + row * tableNline + column)));
                count++;
            }
        }
        ImGui::EndTable();
    }
    ImGui::EndChild();
}

void TuringMachine::Transform1() {
    unsigned int tableNline = 4;
    unsigned int tableWidth = ImGui::GetWindowWidth()/2 - 22;
    unsigned int tableHeight = 80;

    ImGui::BeginChild("ChildR3", ImVec2(ImGui::GetWindowWidth()/2 - 22, 200));
        ImGui::Text("Transform 1(k)");
        ImGui::BeginChild("ChildR9", ImVec2(tableWidth / 2 - 4, tableHeight), true);
            ImGui::Text("LS1");
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("ChildR10", ImVec2(tableWidth / 2 - 4, tableHeight), true);
            ImGui::Text("LS1");
        ImGui::EndChild();
        ImGui::BeginChild("ChildR12", ImVec2(tableWidth / 2 - 4, tableHeight), true);
            ImGui::Text("C1");
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("ChildR13", ImVec2(tableWidth / 2 - 4, tableHeight), true);
            ImGui::Text("D1");
        ImGui::EndChild();
    ImGui::EndChild();
}

void TuringMachine::OutBinaryFromIP() {
    unsigned int tableNline = 4;
    unsigned int tableWidth = ImGui::GetWindowWidth()/2 - 22;
    unsigned int tableHeight = 80;

    ImGui::Text("o-IP(m)");
    ImGui::BeginChild("ChildR4", ImVec2(tableWidth, tableHeight), true);
    if (ImGui::BeginTable("table_context_menu02", tableNline)) {
        // ImGui::TableSetupColumn("Coluna 0");
        // ImGui::TableSetupColumn("Coluna 1");
        // ImGui::TableSetupColumn("Coluna 2");
        // ImGui::TableSetupColumn("Coluna 3");

        // ImGui::TableHeadersRow();
        int s = 12;
        int count = 0;
        for (int row = 0; row < s / tableNline + (int)(s % tableNline); row++) {                        
            ImGui::TableNextRow();
            for (int column = 0; column < tableNline; column++) {
                if(count >= s) break;
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%s", "00001111");
                count++;
            }
        }
        ImGui::EndTable();
        ImGui::EndChild();
    }
    ImGui::BeginChild("ChildR18", ImVec2(tableWidth / 2 - 4, tableHeight), true);
        ImGui::Text("L0");
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("ChildR19", ImVec2(tableWidth / 2 - 4, tableHeight), true);
        ImGui::Text("R0");
    ImGui::EndChild();
}

void TuringMachine::OutBinaryFromPC1() {
    unsigned int tableNline = 4;
    unsigned int tableWidth = ImGui::GetWindowWidth()/2 - 22;
    unsigned int tableHeight = 80;

    ImGui::Text("o-PC-1(k)");
    ImGui::BeginChild("ChildR6", ImVec2(tableWidth, tableHeight), true);
    if (ImGui::BeginTable("table_context_menu01", tableNline)) {
        // ImGui::TableSetupColumn("Coluna 0");
        // ImGui::TableSetupColumn("Coluna 1");
        // ImGui::TableSetupColumn("Coluna 2");
        // ImGui::TableSetupColumn("Coluna 3");

        // ImGui::TableHeadersRow();
        int s = 12;
        int count = 0;
        for (int row = 0; row < s / tableNline + (int)(s % tableNline); row++) {                        
            ImGui::TableNextRow();
            for (int column = 0; column < tableNline; column++) {
                if(count >= s) break;
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%s", "00001111");
                count++;
            }
        }
        ImGui::EndTable();
    }
    ImGui::EndChild();

    ImGui::BeginChild("ChildR7", ImVec2(tableWidth / 2 - 4, tableHeight), true);
        ImGui::Text("C0");
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("ChildR8", ImVec2(tableWidth / 2 - 4, tableHeight), true);
        ImGui::Text("D0");
    ImGui::EndChild();
}

void TuringMachine::K1() {
    unsigned int tableNline = 4;
    unsigned int tableWidth = ImGui::GetWindowWidth()/2 - 22;
    unsigned int tableHeight = 80;

    ImGui::Text("k1");
    ImGui::BeginChild("ChildR16", ImVec2(ImGui::GetWindowWidth(), tableHeight), true);
    if (ImGui::BeginTable("table_context_menu07", tableNline)) {
        // ImGui::TableSetupColumn("Coluna 0");
        // ImGui::TableSetupColumn("Coluna 1");
        // ImGui::TableSetupColumn("Coluna 2");
        // ImGui::TableSetupColumn("Coluna 3");

        // ImGui::TableHeadersRow();
        int s = 12;
        int count = 0;
        for (int row = 0; row < s / tableNline + (int)(s % tableNline); row++) {                        
            ImGui::TableNextRow();
            for (int column = 0; column < tableNline; column++) {
                if(count >= s) break;
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%s", "00001111");
                count++;
            }
        }
        ImGui::EndTable();
        ImGui::EndChild();
    }

}

void TuringMachine::FuncaoF() {
    enum ContentsType { CT_Text, CT_FillButton };
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    static bool display_headers = false;
    static int contents_type = CT_Text;

    ImGui::Text("Expansão E");
    if (ImGui::BeginTable("table_context_menu08", 6, flags))
    {
        // Display headers so we can inspect their interaction with borders.
        // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
        int tableData[][6] = {
            {32,  1, 2 , 3 , 4 , 5},
            {4 ,  5, 6 , 7 , 8 , 9},
            {8 ,  9, 10, 11, 12, 13},
            {12, 13, 14, 15, 16, 17},
            {16, 17, 18, 19, 20, 21},
            {20, 21, 22, 23, 24, 25},
            {24, 25, 26, 27, 28, 29},
            {28, 29, 30, 31, 32, 1}
        };

        for (int row = 0; row < 8; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 6; column++)
            {
                ImGui::TableSetColumnIndex(column);
                char buf[32];
                sprintf(buf, "%d", tableData[row][column]);
                if (contents_type == CT_Text)
                    ImGui::TextUnformatted(buf);
                else if (contents_type)
                    ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
            }
        }
        ImGui::EndTable();
    }
        
    ImGui::Text("s-boxs");
    ImGui::BeginChild("ChildR18", ImVec2(ImGui::GetWindowWidth() - 85, 35), true);
        ImGui::Button("S1");
        ImGui::SameLine();
        ImGui::Button("S2");
        ImGui::SameLine();
        ImGui::Button("S3");
        ImGui::SameLine();
        ImGui::Button("S4");
        ImGui::SameLine();
        ImGui::Button("S5");
        ImGui::SameLine();
        ImGui::Button("S6");
        ImGui::SameLine();
        ImGui::Button("S7");
        ImGui::SameLine();
        ImGui::Button("S8");
    ImGui::EndChild();
}

void TuringMachine::RoundOutput() {
    unsigned int tableNline1 = 4;
    unsigned int tableWidth1 = ImGui::GetWindowWidth()/4 - 10;
    unsigned int tableHeight1 = 64;

    ImGui::BeginChild("ChildR20", ImVec2(tableWidth1, tableHeight1));
        ImGui::Text("R1 = L0 ^ f");
        ImGui::Text("L1 = R0");
        ImGui::Text("L1R1");
    ImGui::EndChild();

    unsigned int tableNline = 3;
    unsigned int tableWidth = ImGui::GetWindowWidth() - 72;
    unsigned int tableHeight = 82;

    ImGui::SameLine();
    ImGui::BeginChild("ChildR021", ImVec2(tableWidth - 55, tableHeight), true);
    if (ImGui::BeginTable("table_context_menu09", tableNline)) {
        // ImGui::TableSetupColumn("Coluna 0");
        // ImGui::TableSetupColumn("Coluna 1");
        // ImGui::TableSetupColumn("Coluna 2");
        // ImGui::TableSetupColumn("Coluna 3");

        // ImGui::TableHeadersRow();
        int s = 24;
        int count = 0;
        for (int row = 0; row < s / tableNline + (int)(s % tableNline); row++) {                        
            ImGui::TableNextRow();
            for (int column = 0; column < tableNline; column++) {
                if(count >= s) break;
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%s", "00001111");
                count++;
            }
        }
        ImGui::EndTable();
        ImGui::EndChild();
    }
}

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
    core.pegaTransicao()[{5, 'b'}] = {4, 'x'};
    core.pegaTransicao()[{0, 'b'}] = {5, mD};
    core.pegaTransicao()[{0, 0x01}] = {0, mD};
    core.pegaFita().adiciona('b');
    core.pegaFita().adiciona('b');
    std::cout << "Numero de transicoes " << core.pegaTransicao().size() << std::endl;
    std::cout << "Numero de dados na fita " << core.pegaFita().size() << std::endl;
    std::cout << "Conscistente " <<  std::boolalpha << core.checaConsistencia() << std::endl;

    core.run();
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
    static char inputValue[128] {""};
    static char textValue[128] {""};
    std::string inS, outS;
    // ImGui::SetNextWindowSize(ImVec2(810, 600));
    ImGui::SetNextWindowSize(ImVec2(1250, 620));
    ImGui::SetNextWindowPos(ImVec2(50, Height / 2 - ImGui::GetWindowHeight() / 1.1));
    ImGui::Begin("Papadimitriou - joilnen e larissa", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    const int hardcoded_node_0 = 0;
    const int hardcoded_node_1 = 1;
    const int output_attr_id = 0;
    const int input_attr_id = 1;

    bool b {true};
    ImGui::ShowDemoWindow(&b);
    static float value = 0.5f;
    if (ImGui::BeginPopupContextItem("my popup"))
    {
        TuringMachine::MyShowMenuFile();
        ImGui::EndPopup();
    }
    ImGui::OpenPopupOnItemClick("my popup", ImGuiPopupFlags_MouseButtonRight);
    if (ImGui::GetIO().MouseClicked[1])
        ImGui::OpenPopup("my popup");


    ImNodes::BeginNodeEditor();
        ImNodes::BeginNode(hardcoded_node_0);
            ImGui::Dummy(ImVec2(0.0f, 0.0f));
            ImGui::Text("Interessante");
            ImGui::Button("B0");
            ImNodes::BeginOutputAttribute(output_attr_id);
                ImGui::Text("output pin");
            ImNodes::EndOutputAttribute();
        ImNodes::EndNode();

        ImNodes::BeginNode(hardcoded_node_1);
            ImGui::Dummy(ImVec2(0.0f, 0.0f));
            ImGui::Text("Interessante");
            ImGui::Button("B1");
            ImNodes::BeginInputAttribute(input_attr_id);
                ImGui::Text("input pin");
            ImNodes::EndOutputAttribute();
        ImNodes::EndNode();

        ImNodes::Link(0, 0, 1);
        ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);
    ImNodes::EndNodeEditor();

    ImGui::End();
}


