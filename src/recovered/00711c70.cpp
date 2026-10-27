// 0x00711c70: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_00711c70(void)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00711c70 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00ad07a0;

void  FUN_00711c70(void)
{
    if (DAT_00ad07a0 != 0) {
        FUN_00781d3b((undefined4)(DAT_00ad07a0));
        DAT_00ad07a0 = 0;
    }
    return;
}

}  // namespace seed_00711c70
