// 0x00770400: function not yet identified
//
// Body: 39 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined2 __thiscall FUN_00770400(int *param_1,uint param_2)
// Callees with accepted source:
//   FUN_00783605 -> src/recovered/00783605.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00770400 {

extern undefined4  FUN_00783605(short *param_1);

struct Owner_00770400 { undefined2 FUN_00770400(uint param_2); };

undefined2 Owner_00770400::FUN_00770400(uint param_2)
{
    int * param_1 = (int *)this;
    uint uVar1;

    uVar1 = (uint)(FUN_00783605((short *)(*param_1)));
    if (param_2 < uVar1) {
        return *(undefined2 *)(*param_1 + param_2 * 2);
    }
    return 0;
}

}  // namespace seed_00770400
