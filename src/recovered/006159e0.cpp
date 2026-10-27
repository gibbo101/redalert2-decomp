// 0x006159e0: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined1 __thiscall FUN_006159e0(int param_1,undefined4 param_2,char param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006159e0 {

struct Owner_006159e0 { undefined1 FUN_006159e0(undefined4 param_2, char param_3); };

undefined1 Owner_006159e0::FUN_006159e0(undefined4 param_2, char param_3)
{
    int param_1 = (int)this;
    if ((param_1 == 1) || (param_1 == 0xb)) {
        if (param_3 == '\v') {
            return 1;
        }
        if ((param_1 == 0xb) && (param_3 == '\0')) {
            return 1;
        }
    }
    return 0;
}

}  // namespace seed_006159e0
