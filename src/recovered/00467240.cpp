// 0x00467240: function not yet identified
//
// Body: 67 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00467240(HWND param_1,int param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00467240 {

extern undefined4  FUN_00783764(int, int, int);
extern "C" __declspec(dllimport) undefined4 __stdcall GetDlgItem(int, int);  // @ref __imp__GetDlgItem@8=0079a49c
extern "C" __declspec(dllimport) undefined4 __stdcall SendMessageA(int, int, int, int);  // @ref __imp__SendMessageA@16=0079a4a0
extern "C" void* PTR_LAB_007d1598;

void __fastcall FUN_00467240(HWND param_1, int param_2, undefined4 param_3)
{
    HWND hWnd;
    undefined1 local_40 [64];

    FUN_00783764((int)(local_40), (int)(&PTR_LAB_007d1598), (int)(param_3));
    hWnd = (HWND)(GetDlgItem((int)(param_1), (int)(param_2)));
                                        /* WARNING: Subroutine does not return */
    SendMessageA((int)(hWnd), (int)(0x4b2), (int)(0), (int)((LPARAM)local_40));
}

}  // namespace seed_00467240
