// 0x0061ee00: function not yet identified
//
// Body: 35 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_0061ee00(int param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0061ee00 {

extern void  FUN_00781d3b(undefined4 param_1);

void __fastcall FUN_0061ee00(int param_1)
{
    if (*(char *)(param_1 + 0x58) != '\0') {
        FUN_00781d3b((undefined4)(*(undefined4 *)(param_1 + 0x54)));
        *(undefined1 *)(param_1 + 0x58) = 0;
    }
    *(undefined4 *)(param_1 + 0x54) = 0;
    return;
}

}  // namespace seed_0061ee00
