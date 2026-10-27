// 0x0063fb40: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: int __thiscall FUN_0063fb40(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0063fb40 {

struct Owner_0063fb40 { int FUN_0063fb40(int param_2); };

int Owner_0063fb40::FUN_0063fb40(int param_2)
{
    int param_1 = (int)this;
    if (param_2 < *(int *)(param_1 + 0x10)) {
        return *(int *)(*(int *)(param_1 + 4) + param_2 * 4) + 1;
    }
    return 0;
}

}  // namespace seed_0063fb40
