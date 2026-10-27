// 0x006633e0: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_006633e0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006633e0 {

extern "C" undefined4 DAT_00ab6e88;

struct Owner_006633e0 { void FUN_006633e0(int param_2); };

void Owner_006633e0::FUN_006633e0(int param_2)
{
    int param_1 = (int)this;
    *(undefined4 *)(param_1 + 0x632 + param_2 * 4) = DAT_00ab6e88;
    return;
}

}  // namespace seed_006633e0
