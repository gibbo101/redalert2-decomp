// 0x005b6a00: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 6 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_005b6a00(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b6a00 {

extern "C" __declspec(dllimport) undefined4 __stdcall timeBeginPeriod(int);  // @ref __imp__timeBeginPeriod@4=0079a52c

undefined4 __fastcall FUN_005b6a00(undefined4 param_1)
{
    timeBeginPeriod((int)(1));
    return param_1;
}

}  // namespace seed_005b6a00
