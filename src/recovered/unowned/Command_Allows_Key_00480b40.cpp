#include "shared/command.hpp"
// @ref ?unknown_hotkeys_832380@@=00832380
// @ref ?search_compfunc@?$IndexClass@HPAVCommandClass@@@@=00480c00
// @ref ?x@?1???A?$IndexClass@HPAVCommandClass@@@@QBEABQAVCommandClass@@ABH@Z@4PAV2@A=00b2b63c
bool __fastcall Command_Allows_Key_00480b40(unsigned int key)
{
    unsigned int normalized = key & 0xfffff7ff; // remove the key-release flag
    CommandClass *command = unknown_hotkeys_832380[(int)(normalized & 0xffffe8ff)];
    if (command == 0) return true;
    return !command->unknown_slot5(normalized);
}
