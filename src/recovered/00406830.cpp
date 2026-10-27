// 0x00406830: function not yet identified
//
// Body: 73 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: bool __fastcall FUN_00406830(uint *param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406830 {

extern undefined4  FUN_00781f20(byte *param_1, byte *param_2);
extern "C" void* PTR_DAT_007ccb90;

bool __fastcall FUN_00406830(uint *param_1, undefined4 param_2)
{
    undefined *puVar1;
    int iVar2;
    undefined **ppuVar3;

    ppuVar3 = (undefined **)(&PTR_DAT_007ccb90);
    puVar1 = (undefined *)(PTR_DAT_007ccb90);
    while ((puVar1 != (undefined *)0x0 && (iVar2 = FUN_00781f20((byte *)(param_2), (byte *)(*ppuVar3)), iVar2 != 0))) {
        puVar1 = (undefined *)(ppuVar3[2]);
        ppuVar3 = (undefined **)(ppuVar3 + 2);
    }
    if (param_1 != (uint *)0x0) {
        *param_1 = *param_1 | (uint)ppuVar3[1];
    }
    return *ppuVar3 != (undefined *)0x0;
}

}  // namespace seed_00406830
