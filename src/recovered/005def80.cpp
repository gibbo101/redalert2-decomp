// 0x005def80: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_005def80(HWND param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_005def80 {

extern "C" __declspec(dllimport) undefined4 __stdcall GetNextDlgTabItem(int, int, int);  // @ref __imp__GetNextDlgTabItem@12=0079a4fc
extern "C" __declspec(dllimport) undefined4 __stdcall GetParent(int);  // @ref __imp__GetParent@4=0079a500
extern "C" __declspec(dllimport) undefined4 __stdcall SetFocus(int);  // @ref __imp__SetFocus@4=0079a38c

bool __fastcall FUN_005def80(HWND param_1, uint param_2)
{
    HWND pHVar1;

    pHVar1 = (HWND)(GetParent((int)(param_1)));
    pHVar1 = (HWND)(GetNextDlgTabItem((int)(pHVar1), (int)(param_1), (int)(param_2 & 0xff)));
    if (pHVar1 != param_1) {
        SetFocus((int)(pHVar1));
        return 1;
    }
    return 0;
}

}  // namespace seed_005def80
