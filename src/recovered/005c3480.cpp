// 0x005c3480: function not yet identified
//
// Body: 38 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005c3480(HWND param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c3480 {

extern "C" __declspec(dllimport) undefined4 __stdcall GetDlgItem(int, int);  // @ref __imp__GetDlgItem@8=0079a49c
extern "C" __declspec(dllimport) undefined4 __stdcall SendMessageA(int, int, int, int);  // @ref __imp__SendMessageA@16=0079a4a0
extern "C" undefined4 DAT_00a3d8dc;

void __fastcall FUN_005c3480(HWND param_1, int param_2)
{
    LPARAM lParam;
    HWND hWnd;

    lParam = (LPARAM)(*(LPARAM *)(DAT_00a3d8dc + param_2 * 4));
    hWnd = (HWND)(GetDlgItem((int)(param_1), (int)(0x5a8)));
                                        /* WARNING: Subroutine does not return */
    SendMessageA((int)(hWnd), (int)(0x4b2), (int)(0), (int)(lParam));
}

}  // namespace seed_005c3480
