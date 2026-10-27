// 0x006b9590: function not yet identified
//
// Owner: TeamClass, virtual slot 10 (vtable +0x28) (from RTTI/vtables).
// Body: 115 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void __thiscall FUN_006b9590(int param_1,int param_2,char param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006b9590 {

struct Owner_006b9590 { void FUN_006b9590(int param_2, char param_3); };

void Owner_006b9590::FUN_006b9590(int param_2, char param_3)
{
    int param_1 = (int)this;
    if (param_2 == *(int *)(param_1 + 0x70)) {
        *(undefined4 *)(param_1 + 0x70) = 0;
    }
    if ((param_2 == *(int *)(param_1 + 0x54)) && (param_3 != '\0')) {
        *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x4c8);
    }
    if (param_2 == *(int *)(param_1 + 0x2c)) {
        *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    if (param_2 == *(int *)(param_1 + 0x28)) {
        *(undefined4 *)(param_1 + 0x28) = 0;
    }
    if (*(int *)(param_1 + 0x40) == param_2) {
        *(undefined4 *)(param_1 + 0x40) = 0;
    }
    if (*(int *)(param_1 + 0x3c) == param_2) {
        *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    if (*(int *)(param_1 + 0x34) == param_2) {
        *(undefined4 *)(param_1 + 0x34) = 0;
    }
    if (*(int *)(param_1 + 0x24) == param_2) {
        *(undefined4 *)(param_1 + 0x24) = 0;
    }
    if (*(int *)(param_1 + 0x38) == param_2) {
        *(undefined4 *)(param_1 + 0x38) = 0;
    }
    if (*(int *)(param_1 + 0x44) == param_2) {
        *(undefined4 *)(param_1 + 0x44) = 0;
    }
    if (*(int *)(param_1 + 0x30) == param_2) {
        *(undefined4 *)(param_1 + 0x30) = 0;
    }
    return;
}

}  // namespace seed_006b9590
