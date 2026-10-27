// 0x007134e0: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_007134e0(undefined4 *param_1,char param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007134e0 {

struct Owner_007134e0 { void FUN_007134e0(char param_2); };

void Owner_007134e0::FUN_007134e0(char param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = 0;
    if (param_2 != '\0') {
        param_1[1] = 0xbfd00000;
        return;
    }
    param_1[1] = 0;
    return;
}

}  // namespace seed_007134e0
