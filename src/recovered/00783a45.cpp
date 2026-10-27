// 0x00783a45: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 6 sites (unconditional call).
// Ghidra prototype: void FUN_00783a45(undefined4 param_1,undefined4 param_2)
// Callees with accepted source:
//   FUN_00783a14 -> src/recovered/00783a14.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00783a45 {

extern undefined4  FUN_00783a14(undefined4 param_1, undefined4 param_2, undefined4 param_3);

void  FUN_00783a45(undefined4 param_1, undefined4 param_2)
{
    FUN_00783a14((undefined4)(param_1), (undefined4)(param_2), (undefined4)(0x40));
    return;
}

}  // namespace seed_00783a45
