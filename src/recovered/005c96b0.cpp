// 0x005c96b0: function not yet identified
//
// Body: 73 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: uint __fastcall FUN_005c96b0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_005c96b0 {

extern "C" undefined4 DAT_00a72d2c;
extern "C" undefined4 DAT_00a72d30;
extern "C" undefined4 DAT_00a72d34;
extern "C" undefined4 DAT_00a72d38;
extern "C" undefined4 DAT_00a72d3c;
extern "C" undefined4 DAT_00a72d44;

uint __fastcall FUN_005c96b0(int param_1)
{
    if (param_1 == 2) {
        return DAT_00a72d2c;
    }
    if (param_1 == 3) {
        return DAT_00a72d30;
    }
    if (param_1 == 4) {
        return DAT_00a72d34;
    }
    if (param_1 == 5) {
        return DAT_00a72d38;
    }
    if (param_1 == 6) {
        return DAT_00a72d3c;
    }
    return (param_1 != 7) - 1 & DAT_00a72d44;
}

}  // namespace seed_005c96b0
