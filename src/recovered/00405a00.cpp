// 0x00405a00: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined4 __fastcall FUN_00405a00(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00405a00 {

undefined4 __fastcall FUN_00405a00(int param_1)
{
    *(undefined4 *)(*(int *)(param_1 + 0xc0) + 0x1c) = 4;
    return 0;
}

}  // namespace seed_00405a00
