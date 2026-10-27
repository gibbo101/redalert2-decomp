// 0x00713520: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 7 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_00713520(undefined4 *param_1,char param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00713520 {

struct Owner_00713520 { void FUN_00713520(char param_2); };

void Owner_00713520::FUN_00713520(char param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
    *param_1 = 0;
    if (param_2 != '\0') {
        param_1[1] = 0x3ff00000;
        return;
    }
    param_1[1] = 0;
    return;
}

}  // namespace seed_00713520
