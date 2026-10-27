// 0x00470470: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_00470470(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00470470 {

extern "C" __declspec(dllimport) undefined4 __stdcall FindClose(int);  // @ref __imp__FindClose@4=0079a2f8
extern "C" undefined4 DAT_007d27d4;

void  FUN_00470470(void)
{
    if ((uint)(DAT_007d27d4) != (uint)((HANDLE)0xffffffff)) {
        FindClose((int)(DAT_007d27d4));
        DAT_007d27d4 = (unsigned int)((HANDLE)0xffffffff);
    }
    return;
}

}  // namespace seed_00470470
