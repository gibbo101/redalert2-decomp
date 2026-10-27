// void VeinholeMonsterClass::Clear_All() (0x00710B50)
// Deletes every monster and empties Array.
#include "shared/veinhole.hpp"

void __cdecl VeinholeMonsterClass::Clear_All()
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        delete Array[index];
    }
    Array.Clear();
}
