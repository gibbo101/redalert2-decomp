// 0x005c8660: function not yet identified
//
// Body: 20 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: bool __fastcall FUN_005c8660(undefined4 param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c8660 {

extern undefined4  FUN_007837d3(ushort *param_1, ushort *param_2);
extern "C" undefined4 DAT_00a3f618;

bool __fastcall FUN_005c8660(undefined4 param_1)
{
    int iVar1;

    iVar1 = (int)(FUN_007837d3((ushort *)(param_1), (ushort *)(&DAT_00a3f618)));
    return iVar1 == 0;
}

}  // namespace seed_005c8660
