// 0x005e7db0: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_005e7db0(HWND param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005e7db0 {

extern void __cdecl FUN_005e7d00(void);
extern "C" __declspec(dllimport) undefined4 __stdcall EnumChildWindows(int, int, int);  // @ref __imp__EnumChildWindows@12=0079a4dc
extern "C" undefined4 DAT_00a737e4;

undefined4 __fastcall FUN_005e7db0(HWND param_1)
{
    DAT_00a737e4 = 0;
    EnumChildWindows((int)(param_1), (int)(FUN_005e7d00), (int)(0));
    return DAT_00a737e4;
}

}  // namespace seed_005e7db0
