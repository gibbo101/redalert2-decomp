// 0x004026a0: function not yet identified
//
// Body: 9 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_004026a0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004026a0 {

void __fastcall FUN_004026a0(int param_1)
{
                                        /* WARNING: Could not recover jumptable at 0x004026a6. Too many branches */
                                        /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)(param_1 + 0xd4) + 0x28))();
    return;
}

}  // namespace seed_004026a0
