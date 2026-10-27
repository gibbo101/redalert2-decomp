// 0x00428ac0: function not yet identified
//
// Body: 18 bytes (frozen inventory bound).
// Referenced from 25 sites (unconditional call).
// Ghidra prototype: int FUN_00428ac0(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00428ac0 {

extern "C" undefined4 DAT_008325d0;
extern "C" undefined4 DAT_008325d4;

int  FUN_00428ac0(void)
{
    return (DAT_008325d4 + 4) * DAT_008325d0 * 2;
}

}  // namespace seed_00428ac0
