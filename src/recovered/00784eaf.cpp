// 0x00784eaf: function not yet identified
//
// Body: 45 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_00784eaf(void)
// Callees with accepted source:
//   FUN_00784fd3 -> src/recovered/00784fd3.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00784eaf {

extern void  FUN_00784fd3(undefined4 *param_1, undefined4 *param_2);
extern "C" undefined4 DAT_007c9000;
extern "C" undefined4 DAT_007cc86c;
extern "C" undefined4 DAT_007cc870;
extern "C" undefined4 DAT_007cc884;
extern "C" void* PTR_FUN_0082ebf8;

void  FUN_00784eaf(void)
{
    if (PTR_FUN_0082ebf8 != (undefined *)0x0) {
        (*(code *)PTR_FUN_0082ebf8)();
    }
    FUN_00784fd3((undefined4 *)(&DAT_007cc870), (undefined4 *)(&DAT_007cc884));
    FUN_00784fd3((undefined4 *)(&DAT_007c9000), (undefined4 *)(&DAT_007cc86c));
    return;
}

}  // namespace seed_00784eaf
