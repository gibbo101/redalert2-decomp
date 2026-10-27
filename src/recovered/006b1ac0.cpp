// 0x006b1ac0: function not yet identified
//
// Body: 22 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined1 FUN_006b1ac0(void)
// Callees with accepted source:
//   FUN_0051fbb0 -> src/recovered/0051fbb0.cpp
//   FUN_0051fc50 -> src/recovered/0051fc50.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006b1ac0 {

extern void  FUN_0051fbb0(void);
extern undefined4  FUN_0051fc50(void);

undefined1 __stdcall FUN_006b1ac0(int unused_0, int unused_1, int unused_2, int unused_3)
{
    char cVar1;

    cVar1 = (char)(FUN_0051fc50());
    if (cVar1 == '\0') {
        return 0;
    }
    FUN_0051fbb0();
    return 1;
}

}  // namespace seed_006b1ac0
