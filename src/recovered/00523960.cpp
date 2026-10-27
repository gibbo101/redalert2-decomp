// 0x00523960: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 23 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_00523960(undefined2 *param_1,undefined2 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00523960 {

extern "C" undefined4 DAT_007ddc70;

struct Owner_00523960 { void FUN_00523960(undefined2 param_2); };

void Owner_00523960::FUN_00523960(undefined2 param_2)
{
    undefined2 * param_1 = (undefined2 *)this;
    if (DAT_007ddc70 == 2) {
        *param_1 = param_2;
    }
    return;
}

}  // namespace seed_00523960
