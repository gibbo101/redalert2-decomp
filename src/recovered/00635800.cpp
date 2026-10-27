// 0x00635800: function not yet identified
//
// Body: 10 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_00635800(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00635800 {

struct Owner_00635800 { void FUN_00635800(int param_2); };

void Owner_00635800::FUN_00635800(int param_2)
{
    int param_1 = (int)this;
    *(double *)(param_1 + 0x10) = (double)param_2;
    return;
}

}  // namespace seed_00635800
