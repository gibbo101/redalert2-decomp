// 0x007693b0: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_007693b0(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007693b0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00b2ad60;

void  FUN_007693b0(void)
{
    if (DAT_00b2ad60 != 0) {
        FUN_00781d3b((undefined4)(DAT_00b2ad60));
        DAT_00b2ad60 = 0;
    }
    return;
}

}  // namespace seed_007693b0
