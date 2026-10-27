// 0x005b69b0: function not yet identified
//
// Body: 43 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 * __thiscall FUN_005b69b0(undefined4 *param_1,undefined4 param_2)
// Callees with accepted source:
//   FUN_00406f30 -> src/recovered/00406f30.cpp
//   FUN_0078d816 -> src/recovered/0078d816.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005b69b0 {

extern undefined4  FUN_00406f30(void);
extern undefined4  FUN_0078d816(char *param_1);

struct Owner_005b69b0 { undefined4 * FUN_005b69b0(undefined4 param_2, int unused_1); };

undefined4 * Owner_005b69b0::FUN_005b69b0(undefined4 param_2, int unused_1)
{
    undefined4 * param_1 = (undefined4 *)this;
    int iVar1;
    undefined4 uVar2;

    *param_1 = 0;
    param_1[1] = 0;
    *(undefined1 *)(param_1 + 2) = 0;
    iVar1 = (int)(FUN_00406f30());
    if (iVar1 != 0) {
        uVar2 = (undefined4)(FUN_0078d816((char *)(param_2)));
        *param_1 = uVar2;
    }
    return param_1;
}

}  // namespace seed_005b69b0
