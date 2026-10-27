// 0x00663420: function not yet identified
//
// Body: 25 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __thiscall FUN_00663420(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00663420 {

struct Callee_00548070 { undefined4 FUN_00548070(short *param_2); };
extern "C" undefined4 DAT_008324e0;

struct Owner_00663420 { void FUN_00663420(int param_2); };

void Owner_00663420::FUN_00663420(int param_2)
{
    int param_1 = (int)this;
    ((Callee_00548070*)(&DAT_008324e0))->FUN_00548070((short *)(param_1 + 0x632 + param_2 * 4));
    return;
}

}  // namespace seed_00663420
