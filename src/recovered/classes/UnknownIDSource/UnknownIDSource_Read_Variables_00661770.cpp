// bool UnknownIDSource::Read_Variables(CCINIClass &ini) (0x00661770)
// Clears the 50 local variable names, then reads [VariableNames] (at most
// 50 entries, "index=name,value"): the name and, when given, the value.
// Always true.
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_0O@JLPK@VariableNames?$AA@=007f1ddc
#include "shared/id_source.hpp"
#include "shared/ccini_class.hpp"
#include "shared/crt_tokens.hpp"

// Westwood-style macro: each operand is evaluated where it appears.
#define Min(a, b) ((a) < (b) ? (a) : (b))

bool UnknownIDSource::Read_Variables(CCINIClass &ini)
{
    for (int index = 0; index < 50; index++) {
        LocalVariables[index].unknown_00[0] = 0;
    }
    int count = Min(ini.Entry_Count("VariableNames"), 50);
    for (index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("VariableNames", index);
        int slot = atoi(entry);
        char buffer[128];
        ini.Get_String("VariableNames", entry, 0, buffer, sizeof(buffer));
        char const *name = strtok(buffer, ",");
        strcpy(LocalVariables[slot].unknown_00, name);
        char const *value = strtok(0, ",");
        if (value) {
            LocalVariables[slot].Value = atoi(value) != 0;
        }
    }
    return true;
}
