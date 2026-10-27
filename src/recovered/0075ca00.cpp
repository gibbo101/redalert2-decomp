// 0x0075ca00: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_0075ca00(void)
// Callees with accepted source:
//   FUN_00735b10 -> src/recovered/00735b10.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0075ca00 {

extern undefined4  FUN_00735b10(void);
extern "C" __declspec(dllimport) undefined4 __stdcall GetDlgItem(int, int);  // @ref __imp__GetDlgItem@8=0079a49c
extern "C" __declspec(dllimport) undefined4 __stdcall SendMessageA(int, int, int, int);  // @ref __imp__SendMessageA@16=0079a4a0

void  FUN_0075ca00(void)
{
    HWND pHVar1;

    pHVar1 = (HWND)FUN_00735b10();
    pHVar1 = (HWND)(GetDlgItem((int)(pHVar1), (int)(0x59f)));
                                        /* WARNING: Subroutine does not return */
    SendMessageA((int)(pHVar1), (int)(0x4dc), (int)(0), (int)(0));
}

}  // namespace seed_0075ca00
