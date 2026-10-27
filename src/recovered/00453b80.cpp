// 0x00453b80: function not yet identified
//
// Body: 15 bytes (frozen inventory bound).
// Referenced from 2 sites (data).
// Ghidra prototype: void FUN_00453b80(undefined4 *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00453b80 {

extern "C" undefined4 _DAT_0084ed10;

void __stdcall FUN_00453b80(undefined4 *param_1)
{
    *param_1 = _DAT_0084ed10;
    return;
}

}  // namespace seed_00453b80
