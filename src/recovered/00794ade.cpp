// 0x00794ade: function not yet identified
//
// Body: 33 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_00794ade(uint param_1,uint param_2,uint *param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00794ade {

undefined4  FUN_00794ade(uint param_1, uint param_2, uint *param_3)
{
    uint uVar1;
    undefined4 uVar2;

    uVar2 = (undefined4)(0);
    uVar1 = (uint)(param_1 + param_2);
    if ((uVar1 < param_1) || (uVar1 < param_2)) {
        uVar2 = (undefined4)(1);
    }
    *param_3 = uVar1;
    return uVar2;
}

}  // namespace seed_00794ade
