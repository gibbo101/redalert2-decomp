// 0x0041f0c0: function not yet identified
//
// Owner: AlphaShapeClass, virtual slot 6 (vtable +0x18) (from RTTI/vtables).
// Body: 33 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: uint FUN_0041f0c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0041f0c0 {

extern undefined4 __stdcall FUN_004100c0(int, int, int);

uint __stdcall FUN_0041f0c0(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    uint uVar1;

    uVar1 = (uint)(FUN_004100c0((int)(param_1), (int)(param_2), (int)(param_3)));
    return uVar1 & ((int)uVar1 >= 0) - 1;
}

}  // namespace seed_0041f0c0
