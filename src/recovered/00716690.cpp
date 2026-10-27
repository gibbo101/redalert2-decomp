// 0x00716690: function not yet identified
//
// Body: 33 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: bool __fastcall FUN_00716690(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00716690 {

extern "C" undefined4 DAT_00ad0934;
extern "C" int DAT_00ad0940;

bool __fastcall FUN_00716690(int param_1)
{
    if ((param_1 >= 0) && (param_1 < DAT_00ad0940)) {
        return *(int *)(*(int *)(DAT_00ad0934 + param_1 * 4) + 0x48) == 2;
    }
    return true;
}

}  // namespace seed_00716690
