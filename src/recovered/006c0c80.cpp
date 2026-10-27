// 0x006c0c80: function not yet identified
//
// Body: 37 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_006c0c80(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006c0c80 {

struct Callee_0069a430 { undefined4 FUN_0069a430(); };
extern void __cdecl FUN_006c0cb0(void);
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_00ac016c;
extern "C" undefined4 _DAT_00ac0168;
extern "C" undefined4 _DAT_00ac0170;

void  FUN_006c0c80(void)
{
    _DAT_00ac0168 = ((Callee_0069a430*)(&DAT_00ac016c))->FUN_0069a430();
    _DAT_00ac0170 = 0;
    FUN_0078298a((undefined4)(FUN_006c0cb0));
    return;
}

}  // namespace seed_006c0c80
