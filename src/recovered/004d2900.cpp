// 0x004d2900: function not yet identified
//
// Body: 53 bytes (frozen inventory bound).
// Referenced from 8 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_004d2900(HWND param_1,int param_2,WPARAM param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d2900 {

extern "C" __declspec(dllimport) undefined4 __stdcall SendDlgItemMessageA(int, int, int, int, int);  // @ref __imp__SendDlgItemMessageA@20=0079a484

void __fastcall FUN_004d2900(HWND param_1, int param_2, WPARAM param_3)
{
    if (param_3 == 0xffffffff) {
        param_3 = (WPARAM)(SendDlgItemMessageA((int)(param_1), (int)(param_2), (int)(0x147), (int)(0), (int)(0)));
    }
    SendDlgItemMessageA((int)(param_1), (int)(param_2), (int)(0x150), (int)(param_3), (int)(0));
    return;
}

}  // namespace seed_004d2900
