// 0x005c8680: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: bool __fastcall FUN_005c8680(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c8680 {

extern undefined4  FUN_007837d3(ushort *param_1, ushort *param_2);
extern "C" undefined4 DAT_00a3f618;
extern "C" undefined4 DAT_00a3fa80;

bool __fastcall FUN_005c8680(int param_1)
{
    int iVar1;

    iVar1 = (int)(FUN_007837d3((ushort *)(*(undefined4 *)(DAT_00a3fa80 + param_1 * 4)), (ushort *)(&DAT_00a3f618)));
    return iVar1 == 0;
}

}  // namespace seed_005c8680
