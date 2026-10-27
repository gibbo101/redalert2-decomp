// 0x005b6a10: function not yet identified
//
// Body: 9 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void FUN_005b6a10(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b6a10 {

extern "C" __declspec(dllimport) undefined4 __stdcall timeEndPeriod(int);  // @ref __imp__timeEndPeriod@4=0079a520

void  FUN_005b6a10(void)
{
    timeEndPeriod((int)(1));
    return;
}

}  // namespace seed_005b6a10
