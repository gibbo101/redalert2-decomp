// 0x005e9f00: function not yet identified
//
// Body: 54 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_005e9f00(HWND param_1,LPARAM param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_005e9f00 {

extern void __cdecl FUN_005e9bb0(void);
extern "C" __declspec(dllimport) undefined4 __stdcall EnumChildWindows(int, int, int);  // @ref __imp__EnumChildWindows@12=0079a4dc
extern "C" __declspec(dllimport) undefined4 __stdcall MoveWindow(int, int, int, int, int, int);  // @ref __imp__MoveWindow@24=0079a3e0
extern "C" undefined4 DAT_008523e0;
extern "C" undefined4 DAT_008523e4;
extern "C" undefined4 DAT_00a763cc;

void __fastcall FUN_005e9f00(HWND param_1, LPARAM param_2)
{
    MoveWindow((int)(param_1), (int)(0), (int)(0), (int)(DAT_008523e0), (int)(DAT_008523e4), (int)(0));
    DAT_00a763cc = (unsigned int)(param_1);
    EnumChildWindows((int)(param_1), (int)(FUN_005e9bb0), (int)(param_2));
    return;
}

}  // namespace seed_005e9f00
