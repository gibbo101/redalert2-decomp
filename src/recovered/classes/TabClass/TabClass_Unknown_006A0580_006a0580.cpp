// int __fastcall TabClass::Unknown_006A0580(char const *name) (0x006A0580)
// Index of name among the command names, else the no-command value.
#include "shared/tab.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_command_names_7f67f8@@3PAPBDA=007f67f8
// @ref ?unknown_no_command_7f67f4@@3HA=007f67f4

int __fastcall TabClass::Unknown_006A0580(char const *name)
{
    for (int index = 0; index < 11; index++) {
        if (strcmp(unknown_command_names_7f67f8[index], name) == 0) {
            return index;
        }
    }
    return unknown_no_command_7f67f4;
}
