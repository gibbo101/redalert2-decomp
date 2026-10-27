// 0x0073c040: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_0073c040(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0073c040 {

extern undefined4  FUN_00784130(uint *param_1, char param_2);

void __fastcall FUN_0073c040(undefined4 param_1)
{
    undefined1 *puVar1;

    for (puVar1 = (undefined1 *)FUN_00784130((uint *)(param_1), (char)(0x20)); puVar1 != (undefined1 *)0x0;
            puVar1 = (undefined1 *)FUN_00784130((uint *)(puVar1), (char)(0x20))) {
        *puVar1 = 0x5f;
    }
    return;
}

}  // namespace seed_0073c040
