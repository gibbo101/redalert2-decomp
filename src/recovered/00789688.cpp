// 0x00789688: function not yet identified
//
// Body: 19 bytes (frozen inventory bound).
// Referenced from 2 sites (unconditional call).
// Ghidra prototype: void FUN_00789688(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_00789688 {

extern "C" undefined4 DAT_0082f808;

void  FUN_00789688(int param_1)
{
    *(undefined **)(param_1 + 0x50) = (unsigned char *)(&DAT_0082f808);
    *(undefined4 *)(param_1 + 0x14) = 1;
    return;
}

}  // namespace seed_00789688
