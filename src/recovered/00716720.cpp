// 0x00716720: function not yet identified
//
// Body: 28 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: char * __fastcall FUN_00716720(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to
// match the original; edit freely, this file is no longer regenerated.
#include "shared/ghidra_types.hpp"

namespace seed_00716720 {

extern "C" undefined4 DAT_00ad0934;
extern "C" int DAT_00ad0940;
extern "C" char s__none__007cdecc[];

char * __fastcall FUN_00716720(int param_1)
{
    if ((param_1 != -1) && (param_1 < DAT_00ad0940)) {
        return *(char **)(DAT_00ad0934 + param_1 * 4);
    }
    return s__none__007cdecc;
}

}  // namespace seed_00716720
