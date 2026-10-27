// 0x0059e370: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_0059e370(int param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0059e370 {

extern "C" char DAT_00a70f0a;

struct Owner_0059e370 { void FUN_0059e370(undefined4 param_2); };

void Owner_0059e370::FUN_0059e370(undefined4 param_2)
{
    int param_1 = (int)this;
    if (DAT_00a70f0a != '\0') {
        *(undefined4 *)(param_1 + 10000) = param_2;
    }
    return;
}

}  // namespace seed_0059e370
