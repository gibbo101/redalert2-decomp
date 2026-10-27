// 0x004ff000: function not yet identified
//
// Body: 78 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: int __thiscall FUN_004ff000(byte *param_1,byte *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004ff000 {

struct Owner_004ff000 { int FUN_004ff000(byte *param_2); };

int Owner_004ff000::FUN_004ff000(byte *param_2)
{
    byte * param_1 = (byte *)this;
    int iVar1;
    int iVar2;
    int iVar3;

    iVar3 = (int)((uint)*param_1 - (uint)*param_2);
    if (iVar3 < 0) {
        iVar3 = (int)(-iVar3);
    }
    iVar2 = (int)((uint)param_1[1] - (uint)param_2[1]);
    if (iVar2 < 0) {
        iVar2 = (int)(-iVar2);
    }
    iVar1 = (int)((uint)param_1[2] - (uint)param_2[2]);
    if (iVar1 < 0) {
        iVar1 = (int)(-iVar1);
    }
    return iVar1 * iVar1 + iVar2 * iVar2 + iVar3 * iVar3;
}

}  // namespace seed_004ff000
