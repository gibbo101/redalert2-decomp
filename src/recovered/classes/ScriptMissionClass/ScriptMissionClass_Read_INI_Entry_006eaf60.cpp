// void ScriptMissionClass::Read_INI_Entry(char const *text) (0x006EAF60):
// reads "action,argument" (ScriptTypeClass::Read_INI); nothing for no text.
// Not a constructor: it does not return this (name hypothesis, the
// counterpart of Build_INI_Entry).
#include "shared/script.hpp"
// @ref ??_C@_05BBIB@?$CFd?0?$CFd?$AA@=007d1f10

void ScriptMissionClass::Read_INI_Entry(char const *text)
{
    if (text != 0) {
        int mission;
        int data;
        sscanf(text, "%d,%d", &mission, &data);
        Mission = mission;
        Data = data;
    }
}
