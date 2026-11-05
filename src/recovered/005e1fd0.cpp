// 0x005e1fd0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005e1fd0(HWND param_1,unsigned char param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005e1fd0 {

extern "C" __declspec(dllimport) undefined4 __stdcall SendMessageA(int, int, int, int);  // @ref __imp__SendMessageA@16=0079a4a0

void __fastcall FUN_005e1fd0(HWND param_1, unsigned char param_2)
{
                                        /* WARNING: Subroutine does not return */
    SendMessageA((int)(param_1), (int)(0x4e6), (int)(0), (int)(param_2 & 0xff));
}

}  // namespace seed_005e1fd0
