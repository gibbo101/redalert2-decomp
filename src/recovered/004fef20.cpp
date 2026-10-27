// 0x004fef20: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 8 sites (unconditional call).
// Ghidra prototype: undefined4 __thiscall FUN_004fef20(short *param_1,short *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004fef20 {

struct Owner_004fef20 { undefined4 FUN_004fef20(short *param_2); };

undefined4 Owner_004fef20::FUN_004fef20(short *param_2)
{
    short * param_1 = (short *)this;
    if ((*param_1 == *param_2) && (param_1[1] == param_2[1])) {
        return 1;
    }
    return 0;
}

}  // namespace seed_004fef20
