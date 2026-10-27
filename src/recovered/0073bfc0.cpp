// 0x0073bfc0: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0073bfc0(void)
// Callees with accepted source:
//   FUN_0073bff0 -> src/recovered/0073bff0.cpp
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0073bfc0 {

struct Callee_0069a430 { undefined4 FUN_0069a430(); };
extern void __cdecl FUN_0073bff0(void);
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00b292e8;
extern "C" undefined4 DAT_00b292ec;
extern "C" undefined4 DAT_00b292f0;

void  FUN_0073bfc0(void)
{
    DAT_00b292e8 = ((Callee_0069a430*)(&DAT_00b292ec))->FUN_0069a430();
    DAT_00b292f0 = 0;
    FUN_0078298a((undefined4)(FUN_0073bff0));
    return;
}

}  // namespace seed_0073bfc0
