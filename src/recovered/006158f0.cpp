// 0x006158f0: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_006158f0(char param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006158f0 {

undefined4 __fastcall FUN_006158f0(char param_1)
{
    if (((param_1 != '\t') && (param_1 != '\x06')) && (param_1 != '\a')) {
        return 0;
    }
    return 1;
}

}  // namespace seed_006158f0
