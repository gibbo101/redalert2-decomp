// 0x00791c5d: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 10 sites (unconditional call).
// Ghidra prototype: void FUN_00791c5d(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00791c5d {

extern "C" __declspec(dllimport) undefined4 __stdcall LeaveCriticalSection(int);  // @ref __imp__LeaveCriticalSection@4=0079a1e0
extern "C" undefined4 DAT_00b2b880;

void  FUN_00791c5d(uint param_1)
{
    LeaveCriticalSection((int)((LPCRITICAL_SECTION)
                          ((&DAT_00b2b880)[(int)param_1 >> 5] + 0xc + (param_1 & 0x1f) * 0x24)));
    return;
}

}  // namespace seed_00791c5d
