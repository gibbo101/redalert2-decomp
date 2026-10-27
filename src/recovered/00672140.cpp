// 0x00672140: function not yet identified
//
// Body: 26 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: bool __fastcall FUN_00672140(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00672140 {

extern undefined4  FUN_00781f20(byte *param_1, byte *param_2);
extern "C" char s_RandMap_Sed_007e16e8[];

bool __fastcall FUN_00672140(int param_1)
{
    int iVar1;

    iVar1 = (int)(FUN_00781f20((byte *)(param_1 + 0x658), (byte *)(s_RandMap_Sed_007e16e8)));
    return iVar1 == 0;
}

}  // namespace seed_00672140
