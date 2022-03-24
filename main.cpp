#include "TuringMachine.h"
#include "Core.h"

/**
 * joilnen leite
 */

int main(int argc, char *argv[])
{
    auto core = Core::getInstance();
    if (argc > 1)
        TuringMachine::getInstance().init(argv[1]);
    else
        TuringMachine::getInstance().init();
    TuringMachine::getInstance().config(core);
    TuringMachine::getInstance().mostraConfig(core);
    TuringMachine::getInstance().roda(core);
}

