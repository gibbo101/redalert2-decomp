// void VeinholeMonsterClass::Delete_Dead() (0x00711E20)
// Deletes every placed monster (unknown_e8) whose node heap is empty, last
// first (expanded into All_AI 0x007101F0).
#include "shared/veinhole.hpp"

void __cdecl VeinholeMonsterClass::Delete_Dead()
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        UnknownVeinHeap *heap = Array[index]->unknown_9c;
        if (Array[index]->unknown_e8 && heap->Count == 0) {
            delete Array[index];
        }
    }
}
