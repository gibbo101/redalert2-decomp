// 0x0040e9f0: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0040e9f0(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0040e9f0 {

struct Callee_0069a430 { undefined4 FUN_0069a430(); };
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00839980;
extern "C" undefined4 DAT_00839984;
extern "C" undefined4 DAT_00839988;

void  FUN_0040e9f0(void)
{
    DAT_00839980 = ((Callee_0069a430*)(&DAT_00839984))->FUN_0069a430();
    DAT_00839988 = 0;
    FUN_0078298a((undefined4)(0x40ea20));
    return;
}

}  // namespace seed_0040e9f0
