// 0x00786d14: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 10 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_00786d14(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00786d14 {

undefined4  FUN_00786d14(int *param_1)
{
    *param_1 = *param_1 + 4;
    return *(undefined4 *)(*param_1 + -4);
}

}  // namespace seed_00786d14
