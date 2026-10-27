// 0x0052e700: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: uint __thiscall FUN_0052e700(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0052e700 {

struct Owner_0052e700 { uint FUN_0052e700(int param_2); };

uint Owner_0052e700::FUN_0052e700(int param_2)
{
    int param_1 = (int)this;
    if (*(char *)(param_1 + 0xc) == '\0') {
        return 0;
    }
    return (uint)(param_2 - *(int *)(param_1 + 4)) >> 2;
}

}  // namespace seed_0052e700
