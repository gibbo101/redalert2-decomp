// 0x004cda80: function not yet identified
//
// Body: 31 bytes (frozen inventory bound).
// Referenced from 4 sites (data).
// Ghidra prototype: void __fastcall FUN_004cda80(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004cda80 {

void __fastcall FUN_004cda80(int param_1)
{
    *(undefined4 *)(param_1 + 0x4b4) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x4b8) = 0;
    *(undefined4 *)(param_1 + 0x4bc) = 0;
    *(undefined1 *)(param_1 + 0x4c1) = 0;
    return;
}

}  // namespace seed_004cda80
