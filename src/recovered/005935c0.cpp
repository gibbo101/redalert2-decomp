// 0x005935c0: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __fastcall FUN_005935c0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005935c0 {

extern "C" __declspec(dllimport) undefined4 __stdcall timeEndPeriod(int);  // @ref __imp__timeEndPeriod@4=0079a520

void __fastcall FUN_005935c0(int *param_1)
{
    if ((*param_1 != 0) || (param_1[1] != 0x3ff00000)) {
        timeEndPeriod((int)(1));
    }
    return;
}

}  // namespace seed_005935c0
