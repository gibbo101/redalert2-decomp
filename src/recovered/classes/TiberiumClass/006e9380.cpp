// 0x006e9380: function not yet identified
//
// Owner: TiberiumClass, virtual slot 7 (vtable +0x1c) (from RTTI/vtables).
// Body: 47 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int FUN_006e9380(int param_1,int *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006e9380 {

extern undefined4 __stdcall FUN_00410180(int *param_1, int *param_2);

int __stdcall FUN_006e9380(int param_1, int *param_2)
{
    int iVar1;

    iVar1 = (int)(FUN_00410180((int *)(param_1), (int *)(param_2)));
    if (iVar1 >= 0) {
        *param_2 = *param_2 + *(int *)(param_1 + 0xd4) * 4 + 4;
        iVar1 = (int)(0);
    }
    return iVar1;
}

}  // namespace seed_006e9380
