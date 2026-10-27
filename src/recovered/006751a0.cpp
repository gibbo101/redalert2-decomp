// 0x006751a0: function not yet identified
//
// Body: 42 bytes (frozen inventory bound).
// Referenced from 5 sites (unconditional call).
// Ghidra prototype: void __fastcall FUN_006751a0(int param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006751a0 {

extern void  FUN_00781d3b(undefined4 param_1);

void __fastcall FUN_006751a0(int param_1)
{
    if ((*(char *)(param_1 + 0x5c) != '\0') && (*(int *)(param_1 + 0x58) != 0)) {
        FUN_00781d3b((undefined4)(*(int *)(param_1 + 0x58)));
        *(undefined4 *)(param_1 + 0x58) = 0;
        *(undefined1 *)(param_1 + 0x5c) = 0;
        *(undefined4 *)(param_1 + 0x14) = 0;
        *(undefined4 *)(param_1 + 0x18) = 0;
    }
    return;
}

}  // namespace seed_006751a0
