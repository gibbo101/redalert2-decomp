// 0x0040f070: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0040f070(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040f070 {

extern void __cdecl FUN_0040f090(void);
struct Callee_0069a1a0 { void FUN_0069a1a0(uint param_2); };
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00839aa0;

void  FUN_0040f070(void)
{
    ((Callee_0069a1a0*)(&DAT_00839aa0))->FUN_0069a1a0((uint)(4000000));
    FUN_0078298a((undefined4)(FUN_0040f090));
    return;
}

}  // namespace seed_0040f070
