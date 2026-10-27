// 0x00784fd3: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void FUN_00784fd3(undefined4 *param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784fd3 {

void  FUN_00784fd3(undefined4 *param_1, undefined4 *param_2)
{
    for (; param_1 < param_2; param_1 = param_1 + 1) {
        if ((code *)*param_1 != (code *)0x0) {
            (*(code *)*param_1)();
        }
    }
    return;
}

}  // namespace seed_00784fd3
