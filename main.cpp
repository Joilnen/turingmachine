#include "TuringMachine.h"
#include "Core.h"

int main(int, char **)
{
    TuringMachine::getInstance().init();
    TuringMachine::getInstance().run();
}

