// 0x004015c0: function not yet identified
//
// Body: 55 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: uint __fastcall FUN_004015c0(int *param_1,undefined4 param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004015c0 {

extern void __cdecl FUN_00781f20(void);
extern undefined4  FUN_00782025(undefined4 param_1, uint param_2, uint param_3, int param_4, code *param_5);

uint __fastcall FUN_004015c0(int *param_1, undefined4 param_2)
{
    int iVar1;

    iVar1 = (int)(FUN_00782025((undefined4)(param_2), (uint)(*param_1), (uint)(param_1[1]), (int)(0x24), (code *)(FUN_00781f20)));
    if (iVar1 != 0) {
        return (uint)(iVar1 - *param_1) / 0x24;
    }
    return 0xffffffff;
}

}  // namespace seed_004015c0
