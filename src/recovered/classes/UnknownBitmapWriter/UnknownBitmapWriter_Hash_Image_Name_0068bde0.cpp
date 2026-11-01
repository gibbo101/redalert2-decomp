// static unsigned int __fastcall Hash_Image_Name_0068bde0(Wstring const &name) (0x0068BDE0)
// The dictionary's hash: the name's length, then each character plus its index, rotated left by 8 (the
// same rotating hash as Hash_Name_005c2ba0, a file-local copy).
#include "shared/pcx_cache.hpp"

static unsigned int __fastcall Hash_Image_Name_0068bde0(Wstring const &name)
{
    unsigned int hash = name.Length();
    for (unsigned int i = 0; i < name.Length(); i++) {
        hash += name.Get()[i] + i;
        hash = (hash << 8) ^ (hash >> 24);
    }
    return hash;
}
