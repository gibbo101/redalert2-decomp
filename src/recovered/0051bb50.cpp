// 0x0051bb50: function not yet identified
//
// Body: 25 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0051bb50(uint param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0051bb50 {

extern void  FUN_006f7650(void);
extern void  FUN_006f7670(void);

void __stdcall FUN_0051bb50(uint param_1)
{
    if ((param_1 & 0x800) != 0) {
        FUN_006f7670();
        return;
    }
    FUN_006f7650();
    return;
}

}  // namespace seed_0051bb50
