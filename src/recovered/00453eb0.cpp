// 0x00453eb0: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 17 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_00453eb0(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00453eb0 {

extern "C" undefined4 DAT_00a40d2c;

int __fastcall FUN_00453eb0(int *param_1)
{
    int iVar1;
    int iVar2;

    iVar1 = (int)(param_1[2]);
    if (*param_1 != -1) {
        iVar2 = (int)(DAT_00a40d2c - *param_1);
        if (iVar2 < iVar1) {
            return iVar1 - iVar2;
        }
        iVar1 = (int)(0);
    }
    return iVar1;
}

}  // namespace seed_00453eb0
