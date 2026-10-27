// int __fastcall unknown_find_or_make_palette(char const *name, int arg2, int arg3, int arg4, int key) -- 0x00663CA0
// Purpose: the index in the list at 0x00AB6EF8 of the entry named `name`
// (case-insensitive, +0x304) with `key` (+0x310); when there is none a new
// 0x33C-byte entry is made (its constructor 0x006639F0 adds it) and the
// search repeats.
// Assumptions: the entry class (palette/convert entries, as AnimClass's
// unknown_bc uses them) is unidentified; arg2..arg4 are passed through.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_list_ab6ef8@@3V?$DynamicVectorClass@PAVUnknownEntry_00663ca0@@@@A=00ab6ef8
// @ref ??0UnknownEntry_00663ca0@@QAE@PBDHHHH_N@Z=006639f0
// @ref _stricmp=00781f20
// @ref ??2@YAPAXI@Z=00782017

extern "C" int __cdecl _stricmp(char const *left, char const *right);

class UnknownEntry_00663ca0 {
public:
    UnknownEntry_00663ca0(char const *name, int arg2, int arg3, int arg4, int key, bool arg6);  // 0x006639F0
    char unknown_000[0x304];
    char const *Name;                       // +0x304
    char unknown_308[0x310 - 0x308];
    int Key;                                // +0x310
    char unknown_314[0x33C - 0x314];
};
extern DynamicVectorClass<UnknownEntry_00663ca0 *> unknown_list_ab6ef8;

int __fastcall unknown_find_or_make_palette(char const *name, int arg2, int arg3, int arg4, int key)
{
    for (;;) {
        for (int index = 0; index < unknown_list_ab6ef8.Count(); index++) {
            if (_stricmp(name, unknown_list_ab6ef8[index]->Name) == 0 && unknown_list_ab6ef8[index]->Key == key) {
                return index;
            }
        }
        new UnknownEntry_00663ca0(name, arg2, arg3, arg4, key, true);
    }
}
