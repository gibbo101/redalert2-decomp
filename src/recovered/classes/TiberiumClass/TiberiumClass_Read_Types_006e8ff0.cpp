// TiberiumClass::Read_Types (0x006E8FF0)
// Reads the [Tiberiums] list of the rules INI: each entry's value is a type ID,
// found or made at the position the entry's key number names, then read.
#include "shared/tiberium.hpp"
// @ref _atoi=00782dfd
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_09OIKJ@Tiberiums?$AA@=007f84fc
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0TiberiumClass@@QAE@PBD@Z=006e89a0

bool __fastcall TiberiumClass::Read_Types(CCINIClass &ini)
{
    int count = ini.Entry_Count("Tiberiums");
    for (int index = 0; index < count; index++) {
        char const *key = ini.Get_Entry("Tiberiums", index);
        char id[24];
        if (ini.Get_String("Tiberiums", key, "", id, sizeof(id)) > 0) {
            int number = atoi(key);
            TiberiumClass *type;
            if (number < unknown_TiberiumClass_list_00ac0b30.Count()) {
                type = unknown_TiberiumClass_list_00ac0b30[number];
            } else {
                type = new TiberiumClass(id);
            }
            type->Read_INI(ini);
        }
    }
    return true;
}
