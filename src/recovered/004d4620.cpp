// 0x004d4620: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_004d4620(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004d4620 {

extern void __cdecl FUN_004d4640(void);
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 _DAT_00a40c80;
extern "C" undefined4 _DAT_00a40c84;

void  FUN_004d4620(void)
{
    _DAT_00a40c80 = 0;
    _DAT_00a40c84 = 0;
    FUN_0078298a((undefined4)(FUN_004d4640));
    return;
}

}  // namespace seed_004d4620
