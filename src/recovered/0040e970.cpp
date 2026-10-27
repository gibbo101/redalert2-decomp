// 0x0040e970: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0040e970(void)
// Callees with accepted source:
//   FUN_0040e9a0 -> src/recovered/0040e9a0.cpp
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040e970 {

extern void __cdecl FUN_0040e9a0(void);
struct Callee_0069a430 { undefined4 FUN_0069a430(); };
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00839990;
extern "C" undefined4 DAT_00839994;
extern "C" undefined4 DAT_00839998;

void  FUN_0040e970(void)
{
    DAT_00839990 = ((Callee_0069a430*)(&DAT_00839994))->FUN_0069a430();
    DAT_00839998 = 0;
    FUN_0078298a((undefined4)(FUN_0040e9a0));
    return;
}

}  // namespace seed_0040e970
