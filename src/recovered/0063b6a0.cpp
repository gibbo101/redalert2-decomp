// 0x0063b6a0: function not yet identified
//
// Body: 12 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void __fastcall FUN_0063b6a0(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0063b6a0 {

struct Callee_00632620 { void FUN_00632620(int *param_2); };
extern "C" undefined4 DAT_008324e0;

void __fastcall FUN_0063b6a0(undefined4 param_1)
{
    ((Callee_00632620*)(&DAT_008324e0))->FUN_00632620((int *)(param_1));
    return;
}

}  // namespace seed_0063b6a0
