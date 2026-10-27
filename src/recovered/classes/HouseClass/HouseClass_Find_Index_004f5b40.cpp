// int __fastcall HouseClass::Find_Index(char const *name) (0x004F5B40)
// The index in Houses of the house whose INI name is name, or -1.
#include "shared/techno.hpp"

int __fastcall HouseClass::Find_Index(char const *name)
{
    for (int index = 0; index < Houses.Count(); index++) {
        char buffer[20];
        strcpy(buffer, Houses[index]->IniName);
        if (strcmp(buffer, name) == 0) {
            return index;
        }
    }
    return -1;
}
