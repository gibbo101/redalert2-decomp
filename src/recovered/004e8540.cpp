// 0x004e8540: function not yet identified
//
// Body: 24 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: undefined4 __fastcall FUN_004e8540(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_004e8540 {

extern "C" undefined4 DAT_00a35cdc;

undefined4 __fastcall FUN_004e8540(int param_1)
{
    if (*(int *)(param_1 + 0x553c) != -1) {
        return *(undefined4 *)(DAT_00a35cdc + *(int *)(param_1 + 0x553c) * 4);
    }
    return 0;
}

}  // namespace seed_004e8540
