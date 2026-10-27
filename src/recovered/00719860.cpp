// 0x00719860: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 13 sites (unconditional call).
// Ghidra prototype: int __thiscall FUN_00719860(int param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00719860 {

struct Owner_00719860 { int FUN_00719860(int param_2, int param_3); };

int Owner_00719860::FUN_00719860(int param_2, int param_3)
{
    int param_1 = (int)this;
    return *(int *)(param_1 + 0x14) +
                  (*(int *)(*(int *)(param_1 + 0x10) + param_2 * 0xc) + param_3) * 0xa4;
}

}  // namespace seed_00719860
