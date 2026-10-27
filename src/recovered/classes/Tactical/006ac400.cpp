// 0x006ac400: function not yet identified
//
// Owner: Tactical, virtual slot 6 (vtable +0x18) (from RTTI/vtables).
// Body: 29 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int FUN_006ac400(undefined4 param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006ac400 {

extern undefined4 __stdcall FUN_004100c0(int, int, int);

int __stdcall FUN_006ac400(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    int iVar1;

    iVar1 = (int)(FUN_004100c0((int)(param_1), (int)(param_2), (int)(param_3)));
    if (iVar1 >= 0) {
        iVar1 = (int)(0);
    }
    return iVar1;
}

}  // namespace seed_006ac400
