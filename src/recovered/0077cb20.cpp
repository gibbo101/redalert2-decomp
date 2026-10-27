// 0x0077cb20: function not yet identified
//
// Body: 56 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_0077cb20(int param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0077cb20 {

void __fastcall FUN_0077cb20(int param_1, int param_2)
{
    int iVar1;

    *(undefined4 *)(param_1 + 0x148) = 0;
    iVar1 = (int)((**(code **)(param_1 + 0x50))(param_1));
    *(uint *)(param_1 + 0x148) =
              (param_2 - (uint)(iVar1 * 0x3c) / *(uint *)(param_1 + 0x78)) - *(int *)(param_1 + 0x148);
    return;
}

}  // namespace seed_0077cb20
