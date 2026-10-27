// 0x00719850: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __thiscall FUN_00719850(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00719850 {

struct Owner_00719850 { int FUN_00719850(int param_2); };

int Owner_00719850::FUN_00719850(int param_2)
{
    int param_1 = (int)this;
    return *(int *)(param_1 + 0x10) + param_2 * 0xc;
}

}  // namespace seed_00719850
