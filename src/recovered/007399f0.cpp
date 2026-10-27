// 0x007399f0: function not yet identified
//
// Body: 93 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void __thiscall FUN_007399f0(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007399f0 {

struct Owner_007399f0 { void FUN_007399f0(int param_2); };

void Owner_007399f0::FUN_007399f0(int param_2)
{
    int param_1 = (int)this;
    if (*(int *)(param_2 + 0x1c) != *(int *)(param_1 + 0x24)) {
        *(int *)(param_1 + 0x24) = *(int *)(param_2 + 0x1c);
        *(undefined1 *)(param_1 + 8) = 1;
    }
    if (*(int *)(param_2 + 0x10) != *(int *)(param_1 + 0x28)) {
        *(int *)(param_1 + 0x28) = *(int *)(param_2 + 0x10);
        *(undefined1 *)(param_1 + 8) = 1;
    }
    if (*(int *)(param_2 + 8) != *(int *)(param_1 + 0x2c)) {
        *(int *)(param_1 + 0x2c) = *(int *)(param_2 + 8);
        *(undefined1 *)(param_1 + 8) = 1;
    }
    if (*(int *)(param_2 + 0xc) != *(int *)(param_1 + 0x30)) {
        *(int *)(param_1 + 0x30) = *(int *)(param_2 + 0xc);
        *(undefined1 *)(param_1 + 8) = 1;
    }
    if (*(int *)(param_2 + 0x20) != *(int *)(param_1 + 0x34)) {
        *(int *)(param_1 + 0x34) = *(int *)(param_2 + 0x20);
        *(undefined1 *)(param_1 + 8) = 1;
    }
    return;
}

}  // namespace seed_007399f0
