// 0x006232a0: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_006232a0(void)
// Callees with accepted source:
//   FUN_006232c0 -> src/recovered/006232c0.cpp
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006232a0 {

extern void __cdecl FUN_006232c0(void);
struct Callee_0069a430 { undefined4 FUN_0069a430(); };
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00a780c0;
extern "C" undefined4 DAT_00a780c4;

void  FUN_006232a0(void)
{
    DAT_00a780c0 = ((Callee_0069a430*)(&DAT_00a780c4))->FUN_0069a430();
    FUN_0078298a((undefined4)(FUN_006232c0));
    return;
}

}  // namespace seed_006232a0
