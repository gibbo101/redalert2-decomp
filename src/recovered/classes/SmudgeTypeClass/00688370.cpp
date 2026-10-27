// 0x00688370: function not yet identified
//
// Owner: SmudgeTypeClass, virtual slot 6 (vtable +0x18) (from RTTI/vtables).
// Body: 29 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: int FUN_00688370(undefined4 param_1,undefined4 param_2,undefined4 param_3)
// Callees with accepted source:
//   FUN_005d7e60 -> src/recovered/classes/ObjectTypeClass/005d7e60.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00688370 {

extern undefined4 __stdcall FUN_005d7e60(undefined4 param_1, undefined4 param_2, undefined4 param_3);

int __stdcall FUN_00688370(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    int iVar1;

    iVar1 = (int)(FUN_005d7e60((undefined4)(param_1), (undefined4)(param_2), (undefined4)(param_3)));
    if (iVar1 >= 0) {
        iVar1 = (int)(0);
    }
    return iVar1;
}

}  // namespace seed_00688370
