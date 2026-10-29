// void __fastcall Execute_Command_By_Name(char const *name) -- 0x00519480
// Executes (key 0) the first registered command whose name is name.
#include "shared/command.hpp"
// @ref ?unknown_commands_832358@@3V?$DynamicVectorClass@PBVCommandClass@@@@A=00832358

extern "C" int __cdecl strcmp(char const *left, char const *right);

void __fastcall Execute_Command_By_Name(char const *name)
{
    for (int index = 0; index < unknown_commands_832358.Count(); index++) {
        if (strcmp(unknown_commands_832358[index]->Get_Name(), name) == 0) {
            unknown_commands_832358[index]->Execute(0);
            return;
        }
    }
}
