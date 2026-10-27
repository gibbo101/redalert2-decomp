// 0x0070a240: function not yet identified
//
// Body: 27 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __fastcall FUN_0070a240(int param_1)
// Callees with accepted source:
//   FUN_006d8e80 -> src/recovered/006d8e80.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0070a240 {

extern undefined4 __fastcall FUN_006d8e80(void);

undefined4 __fastcall FUN_0070a240(int param_1)
{
    char cVar1;

    if (*(int *)(param_1 + 0x5c0) == -1) {
        cVar1 = (char)(FUN_006d8e80());
        if (cVar1 == '\0') {
            return 0;
        }
    }
    return 1;
}

}  // namespace seed_0070a240
