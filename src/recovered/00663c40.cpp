// 0x00663c40: function not yet identified
//
// Body: 34 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __thiscall FUN_00663c40(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00663c40 {

extern undefined4  FUN_00781f20(byte *param_1, byte *param_2);

struct Owner_00663c40 { bool FUN_00663c40(int param_2); };

bool Owner_00663c40::FUN_00663c40(int param_2)
{
    int param_1 = (int)this;
    int iVar1;

    iVar1 = (int)(FUN_00781f20((byte *)(*(undefined4 *)(param_1 + 0x304)), (byte *)(*(undefined4 *)(param_2 + 0x304))));
    return iVar1 == 0;
}

}  // namespace seed_00663c40
