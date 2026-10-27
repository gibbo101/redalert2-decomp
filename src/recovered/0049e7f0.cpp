// 0x0049e7f0: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_0049e7f0(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0049e7f0 {

extern "C" __declspec(dllimport) undefined4 __stdcall DefWindowProcA(int, int, int, int);  // @ref __imp__DefWindowProcA@16=0079a388

void __stdcall FUN_0049e7f0(HWND param_1, UINT param_2, WPARAM param_3, LPARAM param_4)
{
    DefWindowProcA((int)(param_1), (int)(param_2), (int)(param_3), (int)(param_4));
    return;
}

}  // namespace seed_0049e7f0
