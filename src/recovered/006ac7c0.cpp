// 0x006ac7c0: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_006ac7c0(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006ac7c0 {

extern "C" undefined4 DAT_00abe5f8;

undefined4 __stdcall FUN_006ac7c0(int param_1)
{
    return (&DAT_00abe5f8)[param_1 * 3];
}

}  // namespace seed_006ac7c0
