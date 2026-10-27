// 0x0078ac25: function not yet identified
//
// Body: 13 bytes (frozen inventory bound).
// Referenced from 10 sites (unconditional call).
// Ghidra prototype: undefined4 FUN_0078ac25(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078ac25 {

undefined4  FUN_0078ac25(int *param_1)
{
    *param_1 = *param_1 + 4;
    return *(undefined4 *)(*param_1 + -4);
}

}  // namespace seed_0078ac25
