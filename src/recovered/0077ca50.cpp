// 0x0077ca50: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_0077ca50(int param_1,uint *param_2,uint *param_3)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0077ca50 {

undefined4 __fastcall FUN_0077ca50(int param_1, uint *param_2, uint *param_3)
{
    *param_2 = (uint)*(ushort *)(param_1 + 0xfa);
    *param_3 = (uint)*(ushort *)(param_1 + 0xfc);
    return 0xffffffff;
}

}  // namespace seed_0077ca50
