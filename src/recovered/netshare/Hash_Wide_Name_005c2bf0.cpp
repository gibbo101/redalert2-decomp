// unsigned int __fastcall Hash_Wide_Name_005c2bf0(WideString const &name) (0x005C2BF0)
// The same hash over a wide name.
#include "shared/lobby.hpp"

unsigned int __fastcall Hash_Wide_Name_005c2bf0(WideString const &name)
{
    unsigned int hash = name.Length();
    for (unsigned int i = 0; i < name.Length(); i++) {
        hash += name.Get()[i] + i;
        hash = (hash << 8) ^ (hash >> 24);
    }
    return hash;
}
