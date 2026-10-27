// 0x004d4890: function not yet identified
//
// Body: 36 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_004d4890(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d4890 {

extern void __cdecl FUN_004d48c0(void);
struct Callee_005cffc0 { void FUN_005cffc0(undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined2 param_5); };
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00a40a28;

void  FUN_004d4890(void)
{
    ((Callee_005cffc0*)(&DAT_00a40a28))->FUN_005cffc0((undefined4)(0x10), (undefined4)(0x10), (undefined4)(0xec), (undefined2)(0x1234));
    FUN_0078298a((undefined4)(FUN_004d48c0));
    return;
}

}  // namespace seed_004d4890
