// 0x005b55f0: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_005b55f0(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b55f0 {

struct Owner_005b55f0 { void FUN_005b55f0(undefined4 param_2); };

void Owner_005b55f0::FUN_005b55f0(undefined4 param_2)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 0x19) != '\0') {
        *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x34) = param_2;
    }
    return;
}

}  // namespace seed_005b55f0
