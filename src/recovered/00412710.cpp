// 0x00412710: function not yet identified
//
// Body: 8 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_00412710(undefined4 param_1)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00412710 {

extern void  FUN_004068f0(int);

void __fastcall FUN_00412710(undefined4 param_1)
{
    FUN_004068f0((int)(param_1));
    return;
}

}  // namespace seed_00412710
