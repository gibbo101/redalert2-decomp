// 0x00668430: function not yet identified
//
// Owner: ScoreFullFontClass, virtual slot 0 (vtable +0x0) (from RTTI/vtables).
// Body: 96 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 * __thiscall FUN_00668430(undefined4 *param_1,byte param_2)
// Callees with accepted source:
//   FUN_00781d3b -> src/recovered/00781d3b.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00668430 {

extern void  FUN_00781d3b(undefined4 param_1);
extern "C" undefined4 DAT_00ab6fa4;
extern "C" undefined4 DAT_00ab6fac;
extern "C" void* PTR_FUN_007a92a0;

struct Owner_00668430 { undefined4 * FUN_00668430(byte param_2); };

undefined4 * Owner_00668430::FUN_00668430(byte param_2)
{
    undefined4 * param_1 = (undefined4 *)this;
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
    if ((param_2 & 1) != 0) {
        FUN_00781d3b((undefined4)(param_1));
    }
    return param_1;
}

}  // namespace seed_00668430
