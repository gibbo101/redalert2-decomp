// int __fastcall TriggerTypeClass::Persistence_From_Name(char const *name) (0x006EE3C0)
// The persistence named (0 when unknown).
#include "shared/object.hpp"

int __fastcall TriggerTypeClass::Persistence_From_Name(char const *name)
{
    for (int persistence = 0; persistence < 3; persistence++) {
        if (!_stricmp(name, PersistenceNames[persistence])) {
            return persistence;
        }
    }
    return 0;
}
