// 0x007863ca: function not yet identified
//
// Body: 83 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_007863ca(undefined4 param_1,int param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007863ca {

extern void  FUN_007862d9(int, int, int, int);
extern undefined4  FUN_0078d6e0(uint *param_1, uint *param_2);
extern "C" undefined4 DAT_007cf730;
extern "C" undefined4 DAT_007dbe44;

void  FUN_007863ca(undefined4 param_1, int param_2)
{
    FUN_0078d6e0((uint *)(param_1), (uint *)(param_2));
    if (*(char *)(param_2 + 0x40) != '\0') {
        FUN_007862d9((int)(param_1), (int)(2), (int)(&DAT_007cf730), (int)(param_2 + 0x40));
    }
    if (*(char *)(param_2 + 0x80) != '\0') {
        FUN_007862d9((int)(param_1), (int)(2), (int)(&DAT_007dbe44), (int)(param_2 + 0x80));
    }
    return;
}

}  // namespace seed_007863ca
