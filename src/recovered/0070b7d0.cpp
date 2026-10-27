// 0x0070b7d0: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_0070b7d0(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0070b7d0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00ad0614;

void  FUN_0070b7d0(void)
{
    if (DAT_00ad0614 != 0) {
        FUN_00781d3b((undefined4)(DAT_00ad0614));
        DAT_00ad0614 = 0;
    }
    return;
}

}  // namespace seed_0070b7d0
