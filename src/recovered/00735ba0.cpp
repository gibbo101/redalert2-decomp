// 0x00735ba0: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_00735ba0(HWND param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00735ba0 {

extern undefined4 __stdcall FUN_00735bc0(HWND param_1, int param_2);
extern "C" __declspec(dllimport) undefined4 __stdcall EnumChildWindows(int, int, int);  // @ref __imp__EnumChildWindows@12=0079a4dc

void __fastcall FUN_00735ba0(HWND param_1)
{
    EnumChildWindows((int)(param_1), (int)(FUN_00735bc0), (int)(1));
    FUN_00735bc0((HWND)(param_1), (int)(0));
    return;
}

}  // namespace seed_00735ba0
