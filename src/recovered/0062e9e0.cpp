// 0x0062e9e0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: int __fastcall FUN_0062e9e0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0062e9e0 {

int __fastcall FUN_0062e9e0(int *param_1)
{
    if (*param_1 != 0) {
        param_1[1] = param_1[1] + 1U & 0x7f;
        *param_1 = *param_1 + -1;
    }
    return *param_1;
}

}  // namespace seed_0062e9e0
