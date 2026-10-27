// 0x00786d21: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined8 FUN_00786d21(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00786d21 {

undefined8  FUN_00786d21(int *param_1)
{
    *param_1 = *param_1 + 8;
    return *(undefined8 *)(*param_1 + -8);
}

}  // namespace seed_00786d21
