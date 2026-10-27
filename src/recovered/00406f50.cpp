// 0x00406f50: function not yet identified
//
// Body: 21 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: void FUN_00406f50(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406f50 {

extern void  FUN_0040a860(void);
extern "C" undefined4 DAT_00831440;

void  FUN_00406f50(void)
{
    if (DAT_00831440 == 0) {
        FUN_0040a860();
    }
    DAT_00831440 = DAT_00831440 + 1;
    return;
}

}  // namespace seed_00406f50
