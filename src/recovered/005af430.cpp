// 0x005af430: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_005af430(int param_1,char param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005af430 {

struct Owner_005af430 { void FUN_005af430(char param_2); };

void Owner_005af430::FUN_005af430(char param_2)
{
    int param_1 = (int)this;
    if (param_2 != *(char *)(param_1 + 0x48)) {
        *(char *)(param_1 + 0x48) = param_2;
    }
    return;
}

}  // namespace seed_005af430
