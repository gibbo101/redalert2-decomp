// 0x0053b1b0: function not yet identified
//
// Body: 36 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_0053b1b0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0053b1b0 {

extern undefined4 __fastcall FUN_0053b770(void);
extern "C" undefined4 DAT_00a3d290;

struct Owner_0053b1b0 { void FUN_0053b1b0(int param_2); };

void Owner_0053b1b0::FUN_0053b1b0(int param_2)
{
    int param_1 = (int)this;
    *(undefined4 *)(param_1 + 4) = 2;
    if (param_2 == 0) {
        param_2 = (int)(DAT_00a3d290 + 0x940);
    }
    *(int *)(param_1 + 0xc) = param_2;
    FUN_0053b770();
    return;
}

}  // namespace seed_0053b1b0
