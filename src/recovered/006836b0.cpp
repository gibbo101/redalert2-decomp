// 0x006836b0: function not yet identified
//
// Body: 64 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_006836b0(HWND param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006836b0 {

extern "C" __declspec(dllimport) undefined4 __stdcall SendDlgItemMessageA(int, int, int, int, int);  // @ref __imp__SendDlgItemMessageA@20=0079a484

undefined4 __fastcall FUN_006836b0(HWND param_1, int param_2)
{
    WPARAM wParam;
    LRESULT LVar1;

    wParam = (WPARAM)(SendDlgItemMessageA((int)(param_1), (int)(param_2), (int)(0x147), (int)(0), (int)(0)));
    LVar1 = (LRESULT)(SendDlgItemMessageA((int)(param_1), (int)(param_2), (int)(0x150), (int)(wParam), (int)(0)));
    if (((LVar1 != 0) && (LVar1 != 1)) && (LVar1 != 2)) {
        return 0;
    }
    return 1;
}

}  // namespace seed_006836b0
