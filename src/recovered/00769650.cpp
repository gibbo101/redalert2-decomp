// 0x00769650: function not yet identified
//
// Body: 29 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00769650(undefined4 param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00769650 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00b2ad70;

void __fastcall FUN_00769650(undefined4 param_1)
{
    if (DAT_00b2ad70 != 0) {
        FUN_00781d3b((undefined4)(DAT_00b2ad70));
    }
    DAT_00b2ad70 = param_1;
    return;
}

}  // namespace seed_00769650
