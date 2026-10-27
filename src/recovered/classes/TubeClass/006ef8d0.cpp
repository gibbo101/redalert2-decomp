// 0x006ef8d0: function not yet identified
//
// Owner: TubeClass, virtual slot 3 (vtable +0xc) (from RTTI/vtables).
// Body: 56 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 FUN_006ef8d0(undefined4 param_1,undefined4 *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006ef8d0 {

extern "C" undefined4 DAT_007a1cc0;
extern "C" undefined4 DAT_007a1cc4;
extern "C" undefined4 DAT_007a1cc8;
extern "C" undefined4 DAT_007a1ccc;

undefined4 __stdcall FUN_006ef8d0(undefined4 param_1, undefined4 *param_2)
{
    if (param_2 == (undefined4 *)0x0) {
        return 0x80004003;
    }
    *param_2 = DAT_007a1cc0;
    param_2[1] = DAT_007a1cc4;
    param_2[2] = DAT_007a1cc8;
    param_2[3] = DAT_007a1ccc;
    return 0;
}

}  // namespace seed_006ef8d0
