// 0x005ff400: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 FUN_005ff400(HWND param_1,RECT *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005ff400 {

extern "C" __declspec(dllimport) undefined4 __stdcall InvalidateRect(int, int, int);  // @ref __imp__InvalidateRect@12=0079a494
extern "C" __declspec(dllimport) undefined4 __stdcall UpdateWindow(int);  // @ref __imp__UpdateWindow@4=0079a46c

undefined4 __stdcall FUN_005ff400(HWND param_1, RECT *param_2)
{
    InvalidateRect((int)(param_1), (int)(param_2), (int)(0));
    UpdateWindow((int)(param_1));
    return 1;
}

}  // namespace seed_005ff400
