// 0x005e5140: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005e5140(HWND param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005e5140 {

extern void __cdecl FUN_005e4780(void);
extern "C" __declspec(dllimport) undefined4 __stdcall EnumChildWindows(int, int, int);  // @ref __imp__EnumChildWindows@12=0079a4dc

void __fastcall FUN_005e5140(HWND param_1)
{
    EnumChildWindows((int)(param_1), (int)(FUN_005e4780), (int)(0));
    return;
}

}  // namespace seed_005e5140
