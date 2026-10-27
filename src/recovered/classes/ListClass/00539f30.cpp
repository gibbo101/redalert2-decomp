// 0x00539f30: function not yet identified
//
// Owner: ListClass, virtual slot 25 (vtable +0x64) (from RTTI/vtables).
// Body: 136 bytes (frozen inventory bound).
// Referenced from 3 sites (data).
// Ghidra prototype: void __thiscall FUN_00539f30(int param_1,int param_2,int param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00539f30 {

struct Owner_00539f30 { void FUN_00539f30(int param_2, int param_3); };

void Owner_00539f30::FUN_00539f30(int param_2, int param_3)
{
    int param_1 = (int)this;
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;

    iVar1 = (int)(*(int *)(param_1 + 0x14));
    iVar2 = (int)(*(int *)(param_1 + 0x6c));
    iVar3 = (int)(*(int *)(param_1 + 0xcc));
    *(int *)(param_1 + 100) = (iVar1 - iVar2) + param_2;
    *(int *)(param_1 + 0x68) = param_3;
    *(int *)(param_1 + 0xc4) = (iVar1 - iVar3) + param_2;
    iVar4 = (int)(*(int *)(param_1 + 0x18) - *(int *)(param_1 + 0xd0));
    *(int *)(param_1 + 200) = param_3 + iVar4;
    iVar5 = (int)(iVar2);
    if (iVar2 <= iVar3) {
        iVar5 = (int)(iVar3);
    }
    *(int *)(param_1 + 0x124) = (iVar1 - iVar5) + param_2;
    *(int *)(param_1 + 0x128) = param_3 + *(int *)(param_1 + 0x70);
    *(int *)(param_1 + 0x130) = iVar4 - *(int *)(param_1 + 0x70);
    if (iVar2 > iVar3) {
        *(int *)(param_1 + 300) = iVar2;
        return;
    }
    *(int *)(param_1 + 300) = iVar3;
    return;
}

}  // namespace seed_00539f30
