// int __fastcall unknown_color_scheme_index_663d90(char const *name, int kind) -- 0x00663D90
// Purpose: the index in ColorSchemes of the scheme named `name` (case
// insensitive) whose +0x310 field equals kind; -1 when there is none.
// Assumptions: names are hypotheses (Westwood's ColorScheme::From_Name
// family); kind's meaning is not identified.
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#include "shared/vector_class.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref __stricmp=00781f20

extern "C" int __cdecl _stricmp(char const *left, char const *right);

// As shared/ccini_extra.hpp's ColorScheme (name at +0x304, +0x310).
class ColorScheme {
public:
    unsigned char unknown_0x000[0x304];
    char const *Name;                   // +0x304
    unsigned char unknown_0x308[0x08];
    int unknown_0x310;                  // +0x310
};
extern DynamicVectorClass<ColorScheme *> ColorSchemes;      // 0x00AB6EF8

int __fastcall unknown_color_scheme_index_663d90(char const *name, int kind)
{
    for (int index = 0; index < ColorSchemes.Count(); index++) {
        if (_stricmp(name, ColorSchemes[index]->Name) == 0 && ColorSchemes[index]->unknown_0x310 == kind) {
            return index;
        }
    }
    return -1;
}
