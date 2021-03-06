#ifndef NODE_EDITOR_H
#define NODE_EDITOR_H

#ifdef EMSCRIPTEN
    #include <SDL_scancode.h>
#else
    #include <SDL2/SDL_scancode.h>
#endif
#include <algorithm>
#include <vector>

enum class NodeType {ALFA, ESTS, MAQ, FITA, PROG};

struct Node
{
    int   id;
    float value;
    NodeType type;

    Node(const int i, const float v, const NodeType t) : id(i), value(v), type(t) {}
};

struct Link
{
    int id;
    int start_attr, end_attr;
};

struct Editor
{
    ImNodesEditorContext* context = nullptr;
    std::vector<Node>     nodes;
    std::vector<Link>     links;
    int                   current_id = 0;
    bool                  ntype[5];
    Editor() { ntype[0] = ntype[1] = ntype[2] = ntype[3] = ntype[4] = true; }
};

static inline void show_ests(Node &node)
{
    ImNodes::BeginNode(node.id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("ESTADOS");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(node.id << 16);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("value", &node.value, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(node.id << 24);
    const float text_width = ImGui::CalcTextSize("output").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

static inline void show_alpha(Node &node)
{
    ImNodes::BeginNode(node.id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("ALFABETO");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginStaticAttribute(node.id << 16);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("value", &node.value, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(node.id << 24);
    const float text_width = ImGui::CalcTextSize("output").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("maq");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

static inline void show_maq(Node &node)
{
    ImNodes::BeginNode(node.id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("M??QUINA");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(node.id << 8);
    ImGui::TextUnformatted("prog");
    ImNodes::EndInputAttribute();

    ImNodes::BeginStaticAttribute(node.id << 16);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("value", &node.value, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(node.id << 24);
    const float text_width = ImGui::CalcTextSize("fita").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("fita");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

static inline void show_fita(Node &node)
{
    ImNodes::BeginNode(node.id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("FITA");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(node.id << 8);
    ImGui::TextUnformatted("maq");
    ImNodes::EndInputAttribute();

    ImNodes::BeginStaticAttribute(node.id << 16);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("value", &node.value, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::EndNode();
}

static inline void show_prog(Node &node)
{
    ImNodes::BeginNode(node.id);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted("PROGRAMA????O");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(node.id << 8);
    ImGui::TextUnformatted("alfa/est");
    ImNodes::EndInputAttribute();

    ImNodes::BeginStaticAttribute(node.id << 16);
    ImGui::PushItemWidth(120.0f);
    ImGui::DragFloat("value", &node.value, 0.01f);
    ImGui::PopItemWidth();
    ImNodes::EndStaticAttribute();

    ImNodes::BeginOutputAttribute(node.id << 24);
    const float text_width = ImGui::CalcTextSize("maq").x;
    ImGui::Indent(120.f + ImGui::CalcTextSize("value").x - text_width);
    ImGui::TextUnformatted("maq");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

static inline void AdicionaNode(Editor &editor)
{
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(SDL_SCANCODE_A) &&
        editor.ntype[static_cast<unsigned int>(NodeType::ALFA)])
    {
        const int node_id = ++editor.current_id;
        ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
        editor.nodes.push_back(Node(node_id, 0.f, NodeType::ALFA));
        editor.ntype[static_cast<unsigned int>(NodeType::ALFA)] = true;
    }

    /****
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(SDL_SCANCODE_E) &&
        editor.ntype[static_cast<unsigned int>(NodeType::ESTS)])
    {
        const int node_id = ++editor.current_id;
        ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
        editor.nodes.push_back(Node(node_id, 0.f, NodeType::ESTS));
        editor.ntype[static_cast<unsigned int>(NodeType::ESTS)] = false;
    }

    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(SDL_SCANCODE_M) &&
        editor.ntype[static_cast<unsigned int>(NodeType::MAQ)])
    {
        const int node_id = ++editor.current_id;
        ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
        editor.nodes.push_back(Node(node_id, 0.f, NodeType::MAQ));
        editor.ntype[static_cast<unsigned int>(NodeType::MAQ)] = false;
    }

    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(SDL_SCANCODE_F) &&
        editor.ntype[static_cast<unsigned int>(NodeType::FITA)])
    {
        const int node_id = ++editor.current_id;
        ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
        editor.nodes.push_back(Node(node_id, 0.f, NodeType::FITA));
        editor.ntype[static_cast<unsigned int>(NodeType::FITA)] = false;
    }

    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
        ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(SDL_SCANCODE_P) &&
        editor.ntype[static_cast<unsigned int>(NodeType::PROG)])
    {
        const int node_id = ++editor.current_id;
        ImNodes::SetNodeScreenSpacePos(node_id, ImGui::GetMousePos());
        editor.nodes.push_back(Node(node_id, 0.f, NodeType::PROG));
        editor.ntype[static_cast<unsigned int>(NodeType::PROG)] = false;
    }
    ****/
}

void show_editor(const char* editor_name, Editor& editor)
{
    ImNodes::EditorContextSet(editor.context);

    ImGui::Begin(editor_name);
    ImGui::TextUnformatted("A -- add node");

    ImNodes::BeginNodeEditor();

    AdicionaNode(editor);


    for (Node& node : editor.nodes)
    {
        if (node.type == NodeType::ALFA)
        {
            show_alpha(node);
            editor.ntype[static_cast<unsigned int>(NodeType::ALFA)] = true;
        }
        else if (node.type == NodeType::ESTS)
        {
            editor.ntype[static_cast<unsigned int>(NodeType::ESTS)] = true;
            show_ests(node);
        }
        else if (node.type == NodeType::FITA)
        {
            editor.ntype[static_cast<unsigned int>(NodeType::FITA)] = true;
            show_fita(node);
        }
        else if (node.type == NodeType::PROG)
        {
            editor.ntype[static_cast<unsigned int>(NodeType::PROG)] = true;
            show_prog(node);
        }
        else
        {
            editor.ntype[static_cast<unsigned int>(NodeType::MAQ)] = true;
            show_maq(node);
        }
    }

    for (const Link& link : editor.links)
    {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }

    ImNodes::EndNodeEditor();

    {
        Link link;
        if (ImNodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
            link.id = ++editor.current_id;
            editor.links.push_back(link);
        }
    }

    {
        int link_id;
        if (ImNodes::IsLinkDestroyed(&link_id))
        {
            auto iter = std::find_if(
                editor.links.begin(), editor.links.end(), [link_id](const Link& link) -> bool {
                    return link.id == link_id;
                });
            assert(iter != editor.links.end());
            editor.links.erase(iter);
        }
    }

    ImGui::End();
}

Editor mt;

void NodeEditorInitialize()
{
    mt.context = ImNodes::EditorContextCreate();
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);

    ImNodesIO& io = ImNodes::GetIO();
    io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
}

void NodeEditorShow()
{
    show_editor("mt", mt);
}

void NodeEditorShutdown()
{
    ImNodes::PopAttributeFlag();
    ImNodes::EditorContextFree(mt.context);
}

#endif


