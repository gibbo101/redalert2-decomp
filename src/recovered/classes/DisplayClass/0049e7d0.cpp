// 0x0049e7d0: function not yet identified
//
// Owner: DisplayClass, virtual slot 34 (vtable +0x88) (from RTTI/vtables).
// Body: 27 bytes (frozen inventory bound).
// Referenced from 2 sites (data, unconditional call).
// Ghidra prototype: void FUN_0049e7d0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0049e7d0 {

extern "C" __declspec(dllimport) undefined4 __stdcall CloseWindow(int);  // @ref __imp__CloseWindow@4=0079a45c
extern "C" undefined4 DAT_00b263dc;

void  FUN_0049e7d0(void)
{
    if ((uint)(DAT_00b263dc) != (uint)((HWND)0x0)) {
        CloseWindow((int)(DAT_00b263dc));
        DAT_00b263dc = (unsigned int)((HWND)0x0);
    }
    return;
}

}  // namespace seed_0049e7d0
