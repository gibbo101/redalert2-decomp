// 0x007924b6: function not yet identified
//
// Body: 46 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: void FUN_007924b6(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007924b6 {

extern void  FUN_00785c86(int param_1);
extern void  FUN_00785ce7(int param_1);
extern void  FUN_007924fa(void);
extern "C" undefined4 DAT_00b2b338;

void  FUN_007924b6(void)
{
    if (DAT_00b2b338 == 0) {
        FUN_00785c86((int)(0xb));
        if (DAT_00b2b338 == 0) {
            FUN_007924fa();
            DAT_00b2b338 = DAT_00b2b338 + 1;
        }
        FUN_00785ce7((int)(0xb));
    }
    return;
}

}  // namespace seed_007924b6
