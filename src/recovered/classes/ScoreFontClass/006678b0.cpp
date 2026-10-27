// 0x006678b0: function not yet identified
//
// Owner: ScoreFontClass, stores the ScoreFontClass vtable (constructor or destructor) (from RTTI/vtables).
// Body: 76 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_006678b0(undefined4 *param_1)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006678b0 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00ab6fa4;
extern "C" undefined4 DAT_00ab6fac;
extern "C" void* PTR_FUN_007a92a0;

void __fastcall FUN_006678b0(undefined4 *param_1)
{
    undefined1 *puVar1;

    *param_1 = (undefined4)(&PTR_FUN_007a92a0);
    if ((param_1[3] != 0) && (*(char *)(param_1 + 4) == '\x01')) {
        FUN_00781d3b((undefined4)(param_1[3]));
        param_1[3] = 0;
        *(undefined1 *)(param_1 + 4) = 0;
    }
    DAT_00ab6fa4 = DAT_00ab6fa4 + -1;
    if (DAT_00ab6fa4 == 0) {
        puVar1 = (undefined1 *)(&DAT_00ab6fac);
        do {
            *(undefined4 *)(puVar1 + -4) = 0;
            *puVar1 = 0;
            puVar1 = (undefined1 *)(puVar1 + 8);
        } while ((int)puVar1 < 0xab6fc4);
    }
    return;
}

}  // namespace seed_006678b0
