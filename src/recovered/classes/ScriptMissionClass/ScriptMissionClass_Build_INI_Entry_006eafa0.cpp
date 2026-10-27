// int ScriptMissionClass::Build_INI_Entry(char *buffer) const (0x006EAFA0):
// writes "action,argument" and returns its length (0 for no buffer).
#include "shared/script.hpp"
// @ref ??_C@_05BBIB@?$CFd?0?$CFd?$AA@=007d1f10
#include "shared/crt_tokens.hpp"

int ScriptMissionClass::Build_INI_Entry(char *buffer) const
{
    if (buffer != 0) {
        sprintf(buffer, "%d,%d", Mission, Data);
        return strlen(buffer);
    }
    return 0;
}
