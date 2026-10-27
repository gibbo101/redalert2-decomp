// 0x00406140: function not yet identified
//
// Body: 57 bytes (frozen inventory bound).
// Referenced from 9 sites (unconditional call).
// Ghidra prototype: int __fastcall FUN_00406140(int *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406140 {

extern "C" undefined4 DAT_00830fac;
extern "C" undefined4 DAT_00830fb8;

int __fastcall FUN_00406140(int *param_1)
{
    int iVar1;

    if ((DAT_00830fb8 != 0) && ((undefined4 *)param_1[3] == &DAT_00830fac)) {
        iVar1 = (int)(*param_1);
        if ((iVar1 != 0) &&
              ((param_1[2] != *(int *)(iVar1 + 0x24) || (param_1[1] != *(int *)(iVar1 + 0x138))))) {
            iVar1 = (int)(0);
            *param_1 = 0;
        }
        return iVar1;
    }
    return 0;
}

}  // namespace seed_00406140
