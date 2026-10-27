// 0x0078fa6a: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_0078fa6a(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078fa6a {

extern "C" __declspec(dllimport) undefined4 __stdcall GetUserDefaultLCID(void);  // @ref __imp__GetUserDefaultLCID@0=0079a30c
extern "C" undefined4 DAT_00b2b258;
extern "C" undefined4 DAT_00b2b270;
extern "C" undefined4 DAT_00b2b274;

void  FUN_0078fa6a(void)
{
    (*(ushort*)((char*)&DAT_00b2b270 + 0)) = (ushort)DAT_00b2b270 | 0x104;
    DAT_00b2b274 = GetUserDefaultLCID();
    DAT_00b2b258 = DAT_00b2b274;
    return;
}

}  // namespace seed_0078fa6a
