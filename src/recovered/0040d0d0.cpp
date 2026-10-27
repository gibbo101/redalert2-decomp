// 0x0040d0d0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0040d0d0(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040d0d0 {

extern void __cdecl FUN_0040d0f0(void);
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_008324b0;

void  FUN_0040d0d0(void)
{
    DAT_008324b0 = 0;
    FUN_0078298a((undefined4)(FUN_0040d0f0));
    return;
}

}  // namespace seed_0040d0d0
