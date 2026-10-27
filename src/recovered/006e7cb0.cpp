// 0x006e7cb0: function not yet identified
//
// Body: 30 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: int __thiscall FUN_006e7cb0(int param_1,uint param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006e7cb0 {

struct Owner_006e7cb0 { int FUN_006e7cb0(uint param_2); };

int Owner_006e7cb0::FUN_006e7cb0(uint param_2)
{
    int param_1 = (int)this;
    if (param_2 < *(uint *)(param_1 + 0x24)) {
        return *(int *)(*(int *)(param_1 + 0x18) + param_2 * 4) + 0x200;
    }
    return 0;
}

}  // namespace seed_006e7cb0
