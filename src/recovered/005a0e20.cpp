// 0x005a0e20: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_005a0e20(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005a0e20 {

extern "C" undefined4 DAT_00a710ac;

void  FUN_005a0e20(void)
{
                                        /* WARNING: Could not recover jumptable at 0x005a0e2a. Too many branches */
                                        /* WARNING: Treating indirect jump as call */
    (**(code **)(**(int **)(DAT_00a710ac + 8) + 0x60))();
    return;
}

}  // namespace seed_005a0e20
