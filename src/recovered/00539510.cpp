// 0x00539510: function not yet identified
//
// Body: 21 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_00539510(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00539510 {

extern "C" undefined4 DAT_00a40b2c;

struct Owner_00539510 { void FUN_00539510(int param_2); };

void Owner_00539510::FUN_00539510(int param_2)
{
    int param_1 = (int)this;
    if (DAT_00a40b2c == 0) {
        param_2 = (int)(param_2 << 1);
    }
    *(int *)(param_1 + 8) = param_2;
    return;
}

}  // namespace seed_00539510
