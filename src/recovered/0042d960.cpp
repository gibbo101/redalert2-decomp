// 0x0042d960: function not yet identified
//
// Body: 40 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0042d960(void)
// Callees with accepted source:
//   FUN_0042d990 -> src/recovered/0042d990.cpp
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0042d960 {

extern void __cdecl FUN_0042d990(void);
extern undefined4  FUN_0078298a(undefined4 param_1);
extern "C" undefined4 DAT_0084e8d0;
extern "C" undefined4 DAT_0084e930;
extern "C" undefined4 DAT_0084e94c;

void  FUN_0042d960(void)
{
    int iVar1;
    undefined4 *puVar2;

    puVar2 = (undefined4 *)(&DAT_0084e8d0);
    for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = (undefined4 *)(puVar2 + 1);
    }
    DAT_0084e930 = 0;
    DAT_0084e94c = 0;
    FUN_0078298a((undefined4)(FUN_0042d990));
    return;
}

}  // namespace seed_0042d960
