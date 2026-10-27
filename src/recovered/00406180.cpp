// 0x00406180: function not yet identified
//
// Body: 25 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: undefined4 __fastcall FUN_00406180(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406180 {

extern "C" undefined4 DAT_00830fac;
extern "C" undefined4 DAT_00830fb8;

undefined4 __fastcall FUN_00406180(int param_1)
{
    if ((DAT_00830fb8 != 0) && (*(undefined4 **)(param_1 + 0xc) == &DAT_00830fac)) {
        return *(undefined4 *)(param_1 + 8);
    }
    return 0;
}

}  // namespace seed_00406180
