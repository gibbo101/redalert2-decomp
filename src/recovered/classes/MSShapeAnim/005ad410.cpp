// 0x005ad410: function not yet identified
//
// Owner: MSShapeAnim, stores the MSShapeAnim vtable (constructor or destructor) (from RTTI/vtables).
// Body: 51 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_005ad410(undefined4 *param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005ad410 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" void* PTR_FUN_007a6d3c;
extern "C" void* PTR_FUN_007a6d64;

void __fastcall FUN_005ad410(undefined4 *param_1)
{
    *param_1 = (undefined4)(&PTR_FUN_007a6d64);
    if ((param_1[7] != 0) && (*(char *)(param_1 + 0xf) != '\0')) {
        FUN_00781d3b((undefined4)(param_1[7]));
        param_1[7] = 0;
        *(undefined1 *)(param_1 + 0xf) = 0;
    }
    *param_1 = (undefined4)(&PTR_FUN_007a6d3c);
    return;
}

}  // namespace seed_005ad410
