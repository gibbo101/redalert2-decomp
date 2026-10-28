// bool UnknownIDSource::Read_Global_Variables(CCINIClass &ini) (0x006614D0)
// Reads the global variable names from [VariableNames] ("index=name", at most
// 50 entries). Always true.
// @ref ??_C@_0O@JLPK@VariableNames?$AA@=007f1ddc
#include "shared/id_source.hpp"
#include "shared/ccini_class.hpp"
#include "shared/crt_tokens.hpp"

// Westwood-style macro: each operand is evaluated where it appears.
#define Min(a, b) ((a) < (b) ? (a) : (b))

bool UnknownIDSource::Read_Global_Variables(CCINIClass &ini)
{
    int count = Min(ini.Entry_Count("VariableNames"), 50);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("VariableNames", index);
        int slot = atoi(entry);
        ini.Get_String("VariableNames", entry, 0, Variables[slot].unknown_00, 40);
    }
    return true;
}
