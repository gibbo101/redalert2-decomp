// void VeinholeMonsterClass::All_AI() (0x007101F0)
// Runs every monster's AI, last first, then deletes the dead ones.
#include "shared/veinhole.hpp"

void __cdecl VeinholeMonsterClass::All_AI()
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        Array[index]->AI();
    }
    Delete_Dead();
}
