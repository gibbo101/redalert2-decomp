// 0x0078f9ad: function not yet identified
//
// Body: 55 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_0078f9ad(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078f9ad {

extern void __cdecl FUN_0078f9e4(void);
extern "C" __declspec(dllimport) undefined4 __stdcall EnumSystemLocalesA(int, int);  // @ref __imp__EnumSystemLocalesA@8=0079a308
extern "C" undefined4 __cdecl _strlen(...);  // @ref __strlen=00789830
extern "C" undefined4 DAT_00b2b25c;
extern "C" undefined4 DAT_00b2b26c;
extern "C" undefined4 DAT_00b2b270;

void  FUN_0078f9ad(void)
{
    size_t sVar1;

    sVar1 = (size_t)(_strlen(DAT_00b2b26c));
    DAT_00b2b25c = (uint)(sVar1 == 3);
    EnumSystemLocalesA((int)(FUN_0078f9e4), (int)(1));
    if ((DAT_00b2b270 & 4) == 0) {
        DAT_00b2b270 = 0;
    }
    return;
}

}  // namespace seed_0078f9ad
