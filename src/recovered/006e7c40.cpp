// 0x006e7c40: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: char * __thiscall FUN_006e7c40(int param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006e7c40 {

extern "C" char s_No_theme_007f8340[];

struct Owner_006e7c40 { char * FUN_006e7c40(uint param_2); };

char * Owner_006e7c40::FUN_006e7c40(uint param_2)
{
    int param_1 = (int)this;
    if (param_2 < *(uint *)(param_1 + 0x24)) {
        return *(char **)(*(int *)(param_1 + 0x18) + param_2 * 4);
    }
    return s_No_theme_007f8340;
}

}  // namespace seed_006e7c40
