#include "TuringMachine.h"
#include "Core.h"

int main(int, char **)
{
    auto core = Core::getInstance();
    TuringMachine::getInstance().init();
    TuringMachine::getInstance().config(core);
    TuringMachine::getInstance().mostraConfig(core);
}

