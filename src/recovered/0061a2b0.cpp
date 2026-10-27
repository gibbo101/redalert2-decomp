// 0x0061a2b0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_0061a2b0(int *param_1)
// Callees with accepted source:
//   FUN_006f6750 -> src/recovered/006f6750.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0061a2b0 {

extern undefined4  FUN_006f6750(void);

undefined4 __fastcall FUN_0061a2b0(int *param_1)
{
    int iVar1;
    undefined4 uVar2;

    iVar1 = (int)((**(code **)(*param_1 + 0x440))());
    if (iVar1 == 0x1d) {
        uVar2 = (undefined4)(FUN_006f6750());
        return uVar2;
    }
    return 0xffffffff;
}

}  // namespace seed_0061a2b0
