// unsigned int __fastcall Hash_Name_005c2ba0(Wstring const &name) (0x005C2BA0)
// A rotating hash of a narrow name (its length, then each character plus its index, rotated left by 8);
// the WOL code passes its address to hash tables.
#include "shared/lobby.hpp"

unsigned int __fastcall Hash_Name_005c2ba0(Wstring const &name)
{
    unsigned int hash = name.Length();
    for (unsigned int i = 0; i < name.Length(); i++) {
        hash += name.Get()[i] + i;
        hash = (hash << 8) ^ (hash >> 24);
    }
    return hash;
}
